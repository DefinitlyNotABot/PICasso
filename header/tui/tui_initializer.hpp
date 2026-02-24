#pragma once


class TUIInitializer {
    private:
        void initializeColors();

        bool gHasColors = false;

    public:
        TUIInitializer();
        ~TUIInitializer();

        void initialize();        
};