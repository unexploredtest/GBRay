#pragma once

#include "common.hpp"

struct TimerRegs {
    u16 div;
    u8 tima;
    u8 tma;
    u8 tac;
};

enum TimerRegsType {
    TT_DIV, TT_TIMA, TT_TMA, TT_TAC
};

class Timer {
    public:
        Timer() {};
        Timer(Emu* emu);
        void tick();
        void write(TimerRegsType regType, u8 value);
        u8 read(TimerRegsType regType);

    private:
        Emu* m_emu;
        TimerRegs m_regs;
};