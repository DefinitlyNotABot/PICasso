#ifndef TERMINAL_GUI_HPP
#define TERMINAL_GUI_HPP

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <chrono>
#include "memoryInterface.hpp"

/**
 * @brief Struktur für eine klickbare Region im Terminal.
 *
 * Diese Struktur repräsentiert einen Button, der an einer bestimmten Position
 * im Terminal gezeichnet wird und auf Mausklicks reagieren kann.
 */
struct Button
{
    int x, y;                      ///< X- und Y-Koordinaten der oberen linken Ecke
    int w, h;                      ///< Breite und Höhe des Buttons
    std::string label;             ///< Der Text, der auf dem Button angezeigt wird
    std::function<void()> onClick; ///< Callback-Funktion, die bei Klick ausgeführt wird

    /**
     * @brief Prüft, ob die gegebenen Koordinaten innerhalb des Buttons liegen.
     * @param mx X-Koordinate der Maus
     * @param my Y-Koordinate der Maus
     * @return true, wenn die Koordinaten innerhalb des Buttons sind, sonst false
     */
    bool isHit(int mx, int my) const
    {
        return (mx >= x && mx < x + w && my >= y && my < y + h);
    }

    /**
     * @brief Zeichnet den Button im Terminal.
     *
     * Verwendet ANSI-Escape-Codes, um den Cursor zu positionieren und den Button-Text auszugeben.
     */
    void draw() const
    {
        // ANSI-Code um Cursor zu bewegen: \033[y;xH
        std::cout << "\033[" << y << ";" << x << "H[" << label << "]";
    }
};

struct RAMArray
{
    int x, y;       // Startposition im Terminal
    int cols, rows; // Anzahl der Spalten und Zeilen
    uint8_t data[20][8] = {{0}};

    // Die updateData Methode bleibt im Kern gleich,
    // nutzt aber jetzt die dynamischen 'cols' und 'rows'
    void updateData()
    {
        auto ram = MemoryInterface().readRAM();
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int index = i * cols + j;
                if (index < (int)ram.size())
                    data[i][j] = ram[index];
                else
                    data[i][j] = 0;
            }
        }
    }

    void draw() const
    {
        // Titel anzeigen
        std::cout << "\033[" << y << ";" << x << "H\033[1;34m RAM Speicher (Hex) \033[0m";

        for (int i = 0; i < rows; ++i)
        {
            // Positioniert den Cursor für jede Zeile neu (y + Zeilenindex + 1)
            std::cout << "\033[" << (y + i + 1) << ";" << x << "H";

            // Optional: Zeilen-Adresse anzeigen (z.B. 0x00, 0x08, ...)
            printf("\033[90m%02X: \033[0m", i * cols);

            for (int j = 0; j < cols; ++j)
            {
                // Hebe Werte ungleich Null hervor (optional für bessere Lesbarkeit)
                if (data[i][j] != 0)
                    printf("\033[1;37m%02X \033[0m", data[i][j]);
                else
                    printf("00 ");
            }
        }
    }
};

/**
 * @brief Klasse für eine einfache Terminal-GUI mit Maussupport.
 *
 * Diese Klasse ermöglicht es, eine einfache grafische Benutzeroberfläche im Terminal
 * zu erstellen, die Buttons enthält, die mit der Maus geklickt werden können.
 * Sie verwendet Raw-Mode für direkten Zugriff auf Tastatur- und Mauseingaben.
 */
class TerminalGUI
{
private:
    termios orig_termios;                            ///< Speichert die ursprünglichen Terminal-Einstellungen
    std::vector<Button> buttons;                     ///< Liste aller Buttons in der GUI
    bool running = true;                             ///< Flag, das angibt, ob die GUI-Schleife läuft
    std::chrono::steady_clock::time_point last_time; ///< Zeitpunkt des letzten FPS-Updates
    int frame_count = 0;                             ///< Anzahl der Frames seit dem letzten Update
    double fps = 0.0;                                ///< Aktuelle FPS
    RAMArray ramArray = {30, 2, 8, 20};              ///< RAM-Array für Anzeige

    void setRawMode(bool enable);
    void parseMouse();
    void checkClicks(int mx, int my);

public:
    TerminalGUI();
    ~TerminalGUI();
    void addButton(int x, int y, std::string label, std::function<void()> callback);
    void stop();
    bool isRunning() const;
    void loop();
    void draw();
};

#endif // TERMINAL_GUI_HPP