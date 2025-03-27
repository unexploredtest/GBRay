#pragma once

#include "common.hpp"
#include "emu.hpp"

enum PpuMode {
    PM_HBLANK,
    PM_VBLANK,
    PM_OAM,
    PM_DRAW
};

class Ppu {
    public:
        Ppu(Emu* emu);
        void tick();
        u8 readVRam(u16 address);
        void writeVRam(u16 address, u8 value);
        u8 readOAM(u16 address);
        void writeOAM(u16 address, u8 value);
        void runHBlank();
        void runVBlank();
        void runOAM();
        void runDRAW();

    private:
        Emu* m_emu;
        static const u16 VRAM_SIZE = 0x2000;
        static const u16 OAM_SIZE = 0xA0;
        u8 m_vRam[VRAM_SIZE];
        u8 m_oam[OAM_SIZE];
        u16 m_currentLine;
        u16 m_currentTick;
        PpuMode m_currentMode;

};