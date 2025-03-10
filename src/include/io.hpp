#pragma once

#include "common.hpp"
#include "emu.hpp"

class IO {
    public:
        IO(Emu* emu);
        u8 read(u16 address);
        void write(u16 address, u8 value);

    private:
        Emu* m_emu;
        char m_serialData[2] = {0};
    
};