#include "timer.hpp"

Timer::Timer(Emu* emu) {
    m_emu = emu;
    m_regs = {0};
    m_regs.div = 0xAC00;
}

void Timer::tick() {
    u16 prevDiv = m_regs.div;
    m_regs.div++;

    bool shouldUpdate = false;

    if((m_regs.tac & 0b11) == 0b00) {
        shouldUpdate = (prevDiv & (1 << 9)) && (!(m_regs.div & (1 << 9)));
    } else if((m_regs.tac & 0b11) == 0b01) {
        shouldUpdate = (prevDiv & (1 << 3)) && (!(m_regs.div & (1 << 3)));
    } else if((m_regs.tac & 0b11) == 0b10) {
        shouldUpdate = (prevDiv & (1 << 5)) && (!(m_regs.div & (1 << 5)));
    } else if((m_regs.tac & 0b11) == 0b11) {
        shouldUpdate = (prevDiv & (1 << 7)) && (!(m_regs.div & (1 << 7)));
    } else {
        // ???
    }

    if(shouldUpdate && (m_regs.tac & (0b100))) {
        m_regs.tima++;

        if(m_regs.tima == 0xFF) {
            m_regs.tima = m_regs.tma;

            m_emu->getCpu()->requestInterrupt(IT_TIMER);
        }
    }
}

void Timer::write(TimerRegsType regType, u8 value) {
    switch(regType) {
        case TT_DIV:
            m_regs.div = 0;
            break;
        case TT_TAC:
            m_regs.tac = value;
            break;
        case TT_TIMA:
            m_regs.tima = value;
            break;
        case TT_TMA:
            m_regs.tma = value;
            break;
        default:
            throw std::runtime_error("ERROR: No such timer register type to write");
    }
}

u8 Timer::read(TimerRegsType regType) {
    return 0;
    switch(regType) {
        case TT_DIV:
            return m_regs.div >> 8;
        case TT_TAC:
            return m_regs.tac;
        case TT_TIMA:
            return m_regs.tima;
        case TT_TMA:
            return m_regs.tma;
        default:
            throw std::runtime_error("ERROR: No such timer register type to read");

    }
}

