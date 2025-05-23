#pragma once

#include "common.hpp"

class Bus {
    public:
        Bus() = default;
        Bus(Emu* emu);
        u8 read(u16 address);
        void write(u16 address, u8 value);
        u16 read16(u16 address);
        void write16(u16 address, u16 value);
        

    private:
        Emu* m_emu;
};
