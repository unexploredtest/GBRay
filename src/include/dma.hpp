#pragma once

#include "common.hpp"
#include "emu.hpp"

class Dma {
    public:
        Dma(Emu* emu);
        void start(u8 highByte);
        void tick();
        bool isTransferring();

    private:
        Emu* m_emu;
        bool m_isTrans;
        u8 m_curTick;
        u8 m_curHighByte;

    
};