#pragma once

#include "common.hpp"


class Ram {
    public:
        Ram() {};
        Ram(Emu* emu);

        u8 readWRam(u16 address);
        void writeWRam(u16 address, u8 data);
        u8 readHRam(u16 address);
        void writeHRam(u16 address, u8 data);

    private:
        Emu* m_emu;
        static const u16 WRAM_SIZE = 0x2000;
        static const u16 HRAM_SIZE = 0x80;
        u8 m_wRam[WRAM_SIZE];
        u8 m_hRam[HRAM_SIZE];
};