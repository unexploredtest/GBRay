#pragma once

#include "common.hpp"


class UI {
    public:
        UI();
        UI(Emu* emu);
        void init(int screenWidth, int screenHeight);
        void run();
        void deinit();
    
    private:
        Emu* m_emu;
};