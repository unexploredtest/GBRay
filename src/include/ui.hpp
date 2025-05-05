#pragma once

#include "common.hpp"
#include "emu.hpp"

// static const u8 WIDTH_SIZE = 160;
// static const u8 HEIGHT_SIZE = 144;

class UI {
    public:
        UI();
        UI(Emu* emu);
        void init(int screenWidth, int screenHeight);
        void input();
        void run();
        void deinit();
        void drawTiles();
        void drawLCD();
        bool isPaused();
    
    private:
        Emu* m_emu;
        bool m_showTiles;
        bool m_paused = false;
        static const int SCALE = 3;
        static const int TILE_HIZ = 24;
        static const int TILE_VER = 16;
        static constexpr Color COLORS[] = {
            Color{0x9B, 0xBC, 0x0F, 0xFF},
            Color{0x8b, 0xac, 0x0f, 0xFF},
            Color{0x30, 0x62, 0x30, 0xFF},
            Color{0x0f, 0x38, 0x0f, 0xFF}
        };
};