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

enum AddrMode {
    AM_NONE,
    AM_R_R,
    AM_R_N8,
    AM_R_N16,
    AM_MR_R,
    AM_R_MR,
    AM_HLI_R,
    AM_R_HLI,
    AM_HLD_R,
    AM_R_HLD,
    AM_MR_N8,
    AM_R_MN16,
    AM_MN16_R,
    // AM_R_MHLI,
};

enum InsType {
    IN_NONE,
    IN_NOP,
    IN_LD,
    IN_INC,
    IN_DEC,
    IN_RLCA,
    IN_ADD,
    IN_RRCA,
    IN_STOP,
    IN_RLA,
    IN_JR,
    IN_RRA,
    IN_DAA,
    IN_CPL,
    IN_SCF,
    IN_CCF,
    IN_HALT,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_XOR,
    IN_OR,
    IN_CP,
    IN_POP,
    IN_JP,
    IN_PUSH,
    IN_RET,
    IN_CB,
    IN_CALL,
    IN_RETI,
    IN_LDH,
    IN_JPHL,
    IN_DI,
    IN_EI,
    IN_RST,
    IN_ERR,
    //CB instructions...
    IN_RLC, 
    IN_RRC,
    IN_RL, 
    IN_RR,
    IN_SLA, 
    IN_SRA,
    IN_SWAP, 
    IN_SRL,
    IN_BIT, 
    IN_RES, 
    IN_SET
};

enum CondType {
    C_NONE, C_NZ, C_Z, C_NC, C_C
};

struct Instruction {
    InsType insType;
    AddrMode addrMode;
    RegType reg1;
    RegType reg2;
    CondType cond;
    u8 param;
};

struct InstructionData {
    u16 param1;
    u16 param2;
};

class Cpu {
    public:
        Cpu();
        Cpu(Emu* emu);
        void init();
        void step();
        void fetchData();
        bool checkCond();
        void putData(u16 data);
        void cycle(int ticks);
        void fetchInstuction(u8 opcode);
        void runInstruction();
        void printCPUInfo();
        u16 readReg(RegType regType);
        void writeReg(RegType regType, u16 data);
        u8 getFlag(FlagType flagType);
        void setFlag(FlagType flagType);
        void clearFlag(FlagType flagType);
        void toggleFlag(FlagType flagType);
        u8 readIERegister();
        void writeIERegister(u8 data);

    private:
        Emu* m_emu;
        Regs m_regs;

        bool m_intMasterEnabled = false;
        u8 m_IERegister;

        // instructions
        Instruction m_curInst;
        InstructionData m_curInstData;
        void add();
        void XOR();
        void jmp();
        void ld();
        void ldh();
        void di();
};