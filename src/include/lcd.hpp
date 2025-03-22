#pragma once

#include "common.hpp"
#include "emu.hpp"

struct LcdRegs {
    u8 lcdc;
    u8 ly;
    u8 lyc;
    u8 stat;
    u8 scy;
    u8 scx;
    u8 wx;
    u8 wy;
    u8 bgp;
    u8 obp0;
    u8 obp1;
};

class Lcd {
    public:
        Lcd(Emu* emu);
        u8 read(u16 address);
        void write(u16 address, u8 value);
        bool isEnabled();
        u8 windowsTileMapMode();
        bool isWindowEnabled();
        u8 tileDataMode();
        u8 backgroundTileMapMode();
        u8 getObjectSize();
        bool isObjectEnabled();
        bool isBGWindowEnabled();
        bool isStatIntEnabled();



    private:
        Emu* m_emu;
        LcdRegs m_regs;
};