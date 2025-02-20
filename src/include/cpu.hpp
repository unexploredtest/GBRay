#pragma once

#include "common.hpp"
#include "emu.hpp"
#include "miscellaneous.hpp"


struct Regs {
    u16 SP;
    u16 PC;
    u8 B;
    u8 C;
    u8 D;
    u8 E;
    u8 H;
    u8 L;
    u8 A;
    u8 F;
    // flags
    // u8 z: 1;
    // u8 n: 1;
    // u8 h: 1;
    // u8 c: 1;
    // u8 e: 4; // dummy data, to fill reg F
};

enum RegType {
    R_NONE,
    R_A,
    R_F,
    R_AF,
    R_B,
    R_C,
    R_BC,
    R_D,
    R_E,
    R_DE,
    R_H,
    R_L,
    R_HL,
    R_SP,
    R_PC,
};

enum FlagType {
    F_NONE, F_Z, F_N, F_H, F_C
};

class Cpu {
    public:
        Cpu();
        Cpu(Emu* emu);
        void init();
        u16 readReg(RegType regType);
        void writeReg(RegType regType, u16 data);
        u8 getFlag(FlagType flagType);
        void setFlag(FlagType flagType);
        void clearFlag(FlagType flagType);
        void toggleFlag(FlagType flagType);

    private:
        Emu* m_emu;
        Regs m_regs;
};