#include "TerminalGUI.hpp"

/**
 * @brief Aktiviert oder deaktiviert den Raw-Mode des Terminals.
 *
 * Im Raw-Mode werden Eingaben nicht gepuffert und nicht echo'd, was für direkten
 * Zugriff auf Tastatur- und Mauseingaben notwendig ist. Zusätzlich werden Mausereignisse
 * aktiviert und der Bildschirm gelöscht.
 *
 * @param enable true zum Aktivieren des Raw-Mode, false zum Wiederherstellen der Normal-Einstellungen
 */
void TerminalGUI::setRawMode(bool enable)
{
    if (enable)
    {
        // Ursprüngliche Terminal-Einstellungen speichern
        tcgetattr(STDIN_FILENO, &orig_termios);
        termios raw = orig_termios;
        // ICANON (canonical mode) und ECHO deaktivieren
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        // Mausereignisse aktivieren und Bildschirm löschen
        std::cout << "\033[?1000h\033[?1006h" << "\033[2J" << std::flush; // Maus an + Screen clear
    }
    else
    {
        // Ursprüngliche Einstellungen wiederherstellen
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
        // Mausereignisse deaktivieren und Farben zurücksetzen
        std::cout << "\033[?1006l\033[?1000l" << "\033[0m" << std::endl; // Maus aus + Farbe Reset
    }
}

/**
 * @brief Parst eine ANSI-Maussequenz und verarbeitet Mausklicks.
 *
 * Liest eine Maussequenz vom Terminal und extrahiert die Koordinaten.
 * Bei einem Mausklick (state 'M') wird checkClicks aufgerufen.
 */
void TerminalGUI::parseMouse()
{
    char seq[64];
    int i = 0;
    // Erstes Zeichen der Sequenz lesen
    if (read(STDIN_FILENO, &seq[0], 1) && seq[0] == '[')
    {
        // Zweites Zeichen lesen
        if (read(STDIN_FILENO, &seq[1], 1) && seq[1] == '<')
        {
            i = 2;
            // Rest der Sequenz lesen bis 'm' oder 'M'
            while (i < 63)
            {
                read(STDIN_FILENO, &seq[i], 1);
                if (seq[i] == 'm' || seq[i] == 'M')
                {
                    char state = seq[i];
                    seq[i] = '\0';
                    int btn, mx, my;
                    // Koordinaten aus der Sequenz extrahieren
                    if (sscanf(seq + 2, "%d;%d;%d", &btn, &mx, &my) == 3 && state == 'M')
                    {
                        // Bei Mausklick die Klicks prüfen
                        checkClicks(mx, my);
                    }
                    break;
                }
                i++;
            }
        }
    }
}

/**
 * @brief Prüft, ob ein Mausklick auf einen Button erfolgt ist und führt den Callback aus.
 *
 * Iteriert durch alle Buttons und prüft, ob die Klick-Koordinaten innerhalb eines Buttons liegen.
 * Falls ja, wird der entsprechende Callback ausgeführt.
 *
 * @param mx X-Koordinate des Mausklicks
 * @param my Y-Koordinate des Mausklicks
 */
void TerminalGUI::checkClicks(int mx, int my)
{
    for (const auto &btn : buttons)
    {
        if (btn.isHit(mx, my))
        {
            btn.onClick();
        }
    }
}

/**
 * @brief Konstruktor: Initialisiert die GUI und aktiviert Raw-Mode.
 */
TerminalGUI::TerminalGUI()
{
    setRawMode(true);
    last_time = std::chrono::steady_clock::now();


    // Button hinzufügen, der das Programm beendet
    addButton(5, 7, " Beenden ", [this]()
              { this->stop(); });

    ramArray.updateData();
}

/**
 * @brief Destruktor: Stellt die ursprünglichen Terminal-Einstellungen wieder her.
 */
TerminalGUI::~TerminalGUI() { setRawMode(false); }

/**
 * @brief Fügt einen neuen Button zur GUI hinzu.
 *
 * Erstellt einen neuen Button mit den gegebenen Parametern und fügt ihn zur Liste hinzu.
 * Die Breite wird automatisch basierend auf der Länge des Labels berechnet.
 *
 * @param x X-Koordinate der oberen linken Ecke
 * @param y Y-Koordinate der oberen linken Ecke
 * @param label Der Text des Buttons
 * @param callback Funktion, die bei Klick ausgeführt wird
 */
void TerminalGUI::addButton(int x, int y, std::string label, std::function<void()> callback)
{
    buttons.push_back({x, y, (int)label.length() + 2, 1, label, callback});
}

/**
 * @brief Stoppt die GUI-Schleife.
 *
 * Setzt das running-Flag auf false, wodurch die loop()-Methode beendet wird.
 */
void TerminalGUI::stop() { running = false; }

/**
 * @brief Gibt zurück, ob die GUI noch läuft.
 *
 * @return true, wenn die GUI läuft, sonst false
 */
bool TerminalGUI::isRunning() const { return running; }

/**
 * @brief Startet die Haupt-GUI-Schleife.
 *
 * Diese Schleife läuft kontinuierlich, zeichnet die UI neu, wartet auf Eingaben
 * und verarbeitet Tastatur- und Mauseingaben. Die Schleife endet, wenn stop() aufgerufen wird.
 */
void TerminalGUI::loop()
{
    // Poll-Struktur für nicht-blockierendes Warten auf Eingaben
    struct pollfd fds[1] = {{STDIN_FILENO, POLLIN, 0}};

    while (running)
    {
        ramArray.updateData();
        draw();

        // Auf Eingaben warten (Timeout 100ms)
        if (poll(fds, 1, 100) > 0)
        {
            char c;
            if (read(STDIN_FILENO, &c, 1) > 0)
            {
                if (c == 'q')
                    stop(); // 'q' beendet die Schleife
                else if (c == '\033')
                    parseMouse(); // Escape-Sequenz für Maus
            }
        }
    }
}

void TerminalGUI::draw()
{
    // FPS berechnen
    frame_count++;
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();
    if (duration >= 1000)
    {
        fps = frame_count * 1000.0 / duration;
        frame_count = 0;
        last_time = now;
    }

    // UI neu zeichnen
    std::cout << "\033[H"; // Cursor nach oben links bewegen
    for (const auto &btn : buttons)
        btn.draw();
    // RAMArray anzeigen
    ramArray.draw();
    // FPS anzeigen
    std::cout << "\033[1;1H FPS: " << fps;
    std::cout << std::flush;
}