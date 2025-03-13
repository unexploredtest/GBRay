#pragma once

#include "common.hpp"
#include "emu.hpp"

class Ppu {
    public:
        Ppu(Emu* emu);
        u8 readVRam(u16 address);
        void writeVRam(u16 address, u8 value);
        u8 readOAM(u16 address);
        void writeOAM(u16 address, u8 value);

    private:
        Emu* m_emu;
        static const u16 VRAM_SIZE = 0x2000;
        static const u16 OAM_SIZE = 0xA0;
        u8 m_vRam[VRAM_SIZE];
        u8 m_oam[OAM_SIZE];
    
};