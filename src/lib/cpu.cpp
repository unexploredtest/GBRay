#include "cpu.hpp"

static const std::array<Instruction, 0xFF> INSTRUCTIONS = [] {
    std::array<Instruction, 0xFF> temp = {};
    temp.fill(Instruction{}); // Unassigned values get the default NONE instruction
    temp[0x00] = Instruction{IN_NOP};
    temp[0x01] = Instruction{IN_LD, AM_R_N16, R_BC};
    temp[0x02] = Instruction{IN_LD, AM_MR_R, R_BC, R_A};
    temp[0x03] = Instruction{IN_INC, AM_R, R_BC};
    temp[0x04] = Instruction{IN_INC, AM_R, R_B};
    temp[0x05] = Instruction{IN_DEC, AM_R, R_B};
    temp[0x06] = Instruction{IN_LD, AM_R_N8, R_B};
    temp[0x07] = Instruction{IN_RLCA};
    temp[0x08] = Instruction{IN_LD, AM_MN16_R, R_SP};
    temp[0x09] = Instruction{IN_ADD, AM_R_R, R_HL, R_BC};
    temp[0x0A] = Instruction{IN_LD, AM_R_MR, R_A, R_BC};
    temp[0x0B] = Instruction{IN_DEC, AM_R, R_BC};
    temp[0x0C] = Instruction{IN_INC, AM_R, R_C};
    temp[0x0D] = Instruction{IN_DEC, AM_R, R_C};
    temp[0x0E] = Instruction{IN_LD, AM_R_N8, R_C};
    temp[0x0F] = Instruction{IN_RRCA};
    // 0x10
    temp[0x11] = Instruction{IN_LD, AM_R_N16, R_DE};
    temp[0x12] = Instruction{IN_LD, AM_MR_R, R_DE, R_A};
    temp[0x13] = Instruction{IN_INC, AM_R, R_DE};
    temp[0x14] = Instruction{IN_INC, AM_R, R_D};
    temp[0x15] = Instruction{IN_DEC, AM_R, R_D};
    temp[0x16] = Instruction{IN_LD, AM_R_N8, R_D};
    temp[0x17] = Instruction{IN_RLA};
    temp[0x18] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_NONE};
    temp[0x19] = Instruction{IN_ADD, AM_R_R, R_HL, R_DE};
    temp[0x1A] = Instruction{IN_LD, AM_R_MR, R_A, R_DE};
    temp[0x1B] = Instruction{IN_DEC, AM_R, R_DE};
    temp[0x1C] = Instruction{IN_INC, AM_R, R_E};
    temp[0x1D] = Instruction{IN_DEC, AM_R, R_E};
    temp[0x1E] = Instruction{IN_LD, AM_R_N8, R_E};
    temp[0x1F] = Instruction{IN_RRA};
    // 0x20
    temp[0x20] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_NZ};
    temp[0x21] = Instruction{IN_LD, AM_R_N16, R_HL};
    temp[0x22] = Instruction{IN_LD, AM_HLI_R, R_HL, R_A};
    temp[0x23] = Instruction{IN_INC, AM_R, R_HL};
    temp[0x24] = Instruction{IN_INC, AM_R, R_H};
    temp[0x25] = Instruction{IN_DEC, AM_R, R_H};
    temp[0x26] = Instruction{IN_LD, AM_R_N8, R_H};
    temp[0x27] = Instruction{IN_DAA};
    temp[0x28] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_Z};
    temp[0x29] = Instruction{IN_ADD, AM_R_R, R_HL, R_HL};
    temp[0x2A] = Instruction{IN_LD, AM_R_HLI, R_A, R_HL};
    temp[0x2B] = Instruction{IN_DEC, AM_R, R_HL};
    temp[0x2C] = Instruction{IN_INC, AM_R, R_L};
    temp[0x2D] = Instruction{IN_DEC, AM_R, R_L};
    temp[0x2E] = Instruction{IN_LD, AM_R_N8, R_L};
    temp[0x2F] = Instruction{IN_CPL};
    // 0x30
    temp[0x30] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_NC};
    temp[0x31] = Instruction{IN_LD, AM_R_N16, R_SP};
    temp[0x32] = Instruction{IN_LD, AM_HLD_R, R_HL, R_A};
    temp[0x33] = Instruction{IN_INC, AM_R, R_SP};
    temp[0x34] = Instruction{IN_INC, AM_MR, R_HL};
    temp[0x35] = Instruction{IN_DEC, AM_MR, R_HL};
    temp[0x36] = Instruction{IN_LD, AM_MR_N8, R_HL};
    temp[0x37] = Instruction{IN_SCF};
    temp[0x38] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_C};
    temp[0x39] = Instruction{IN_ADD, AM_R_R, R_HL, R_SP};
    temp[0x3A] = Instruction{IN_LD, AM_R_HLD, R_A, R_HL};
    temp[0x3B] = Instruction{IN_DEC, AM_R, R_SP};
    temp[0x3C] = Instruction{IN_INC, AM_R, R_A};
    temp[0x3D] = Instruction{IN_DEC, AM_R, R_A};
    temp[0x3E] = Instruction{IN_LD, AM_R_N8, R_A};
    temp[0x3F] = Instruction{IN_CCF};
    // 0x40
    temp[0x40] = Instruction{IN_LD, AM_R_R, R_B, R_B};
    temp[0x41] = Instruction{IN_LD, AM_R_R, R_B, R_C};
    temp[0x42] = Instruction{IN_LD, AM_R_R, R_B, R_D};
    temp[0x43] = Instruction{IN_LD, AM_R_R, R_B, R_E};
    temp[0x44] = Instruction{IN_LD, AM_R_R, R_B, R_H};
    temp[0x45] = Instruction{IN_LD, AM_R_R, R_B, R_L};
    temp[0x46] = Instruction{IN_LD, AM_R_MR, R_B, R_HL};
    temp[0x47] = Instruction{IN_LD, AM_R_R, R_B, R_A};
    temp[0x48] = Instruction{IN_LD, AM_R_R, R_C, R_B};
    temp[0x49] = Instruction{IN_LD, AM_R_R, R_C, R_C};
    temp[0x4A] = Instruction{IN_LD, AM_R_R, R_C, R_D};
    temp[0x4B] = Instruction{IN_LD, AM_R_R, R_C, R_E};
    temp[0x4C] = Instruction{IN_LD, AM_R_R, R_C, R_H};
    temp[0x4D] = Instruction{IN_LD, AM_R_R, R_C, R_L};
    temp[0x4E] = Instruction{IN_LD, AM_R_MR, R_C, R_HL};
    temp[0x4F] = Instruction{IN_LD, AM_R_R, R_C, R_A};
    // 0x50
    temp[0x50] = Instruction{IN_LD, AM_R_R, R_D, R_B};
    temp[0x51] = Instruction{IN_LD, AM_R_R, R_D, R_C};
    temp[0x52] = Instruction{IN_LD, AM_R_R, R_D, R_D};
    temp[0x53] = Instruction{IN_LD, AM_R_R, R_D, R_E};
    temp[0x54] = Instruction{IN_LD, AM_R_R, R_D, R_H};
    temp[0x55] = Instruction{IN_LD, AM_R_R, R_D, R_L};
    temp[0x56] = Instruction{IN_LD, AM_R_MR, R_D, R_HL};
    temp[0x57] = Instruction{IN_LD, AM_R_R, R_D, R_A};
    temp[0x58] = Instruction{IN_LD, AM_R_R, R_E, R_B};
    temp[0x59] = Instruction{IN_LD, AM_R_R, R_E, R_C};
    temp[0x5A] = Instruction{IN_LD, AM_R_R, R_E, R_D};
    temp[0x5B] = Instruction{IN_LD, AM_R_R, R_E, R_E};
    temp[0x5C] = Instruction{IN_LD, AM_R_R, R_E, R_H};
    temp[0x5D] = Instruction{IN_LD, AM_R_R, R_E, R_L};
    temp[0x5E] = Instruction{IN_LD, AM_R_MR, R_E, R_HL};
    temp[0x5F] = Instruction{IN_LD, AM_R_R, R_E, R_A};
    // 0x60
    temp[0x60] = Instruction{IN_LD, AM_R_R, R_H, R_B};
    temp[0x61] = Instruction{IN_LD, AM_R_R, R_H, R_C};
    temp[0x62] = Instruction{IN_LD, AM_R_R, R_H, R_D};
    temp[0x63] = Instruction{IN_LD, AM_R_R, R_H, R_E};
    temp[0x64] = Instruction{IN_LD, AM_R_R, R_H, R_H};
    temp[0x65] = Instruction{IN_LD, AM_R_R, R_H, R_L};
    temp[0x66] = Instruction{IN_LD, AM_R_MR, R_H, R_HL};
    temp[0x67] = Instruction{IN_LD, AM_R_R, R_H, R_A};
    temp[0x68] = Instruction{IN_LD, AM_R_R, R_L, R_B};
    temp[0x69] = Instruction{IN_LD, AM_R_R, R_L, R_C};
    temp[0x6A] = Instruction{IN_LD, AM_R_R, R_L, R_D};
    temp[0x6B] = Instruction{IN_LD, AM_R_R, R_L, R_E};
    temp[0x6C] = Instruction{IN_LD, AM_R_R, R_L, R_H};
    temp[0x6D] = Instruction{IN_LD, AM_R_R, R_L, R_L};
    temp[0x6E] = Instruction{IN_LD, AM_R_MR, R_L, R_HL};
    temp[0x6F] = Instruction{IN_LD, AM_R_R, R_L, R_A};
    // 0X70
    temp[0x70] = Instruction{IN_LD, AM_MR_R, R_HL, R_B};
    temp[0x71] = Instruction{IN_LD, AM_MR_R, R_HL, R_C};
    temp[0x72] = Instruction{IN_LD, AM_MR_R, R_HL, R_D};
    temp[0x73] = Instruction{IN_LD, AM_MR_R, R_HL, R_E};
    temp[0x74] = Instruction{IN_LD, AM_MR_R, R_HL, R_H};
    temp[0x75] = Instruction{IN_LD, AM_MR_R, R_HL, R_L};
    temp[0x76] = Instruction{IN_HALT};
    temp[0x77] = Instruction{IN_LD, AM_MR_R, R_HL, R_A};
    temp[0x78] = Instruction{IN_LD, AM_R_R, R_A, R_B};
    temp[0x79] = Instruction{IN_LD, AM_R_R, R_A, R_C};
    temp[0x7A] = Instruction{IN_LD, AM_R_R, R_A, R_D};
    temp[0x7B] = Instruction{IN_LD, AM_R_R, R_A, R_E};
    temp[0x7C] = Instruction{IN_LD, AM_R_R, R_A, R_H};
    temp[0x7D] = Instruction{IN_LD, AM_R_R, R_A, R_L};
    temp[0x7E] = Instruction{IN_LD, AM_R_MR, R_A, R_HL};
    temp[0x7F] = Instruction{IN_LD, AM_R_R, R_A, R_A};
    // 0x80
    temp[0x80] = Instruction{IN_ADD, AM_R_R, R_A, R_B};
    temp[0x81] = Instruction{IN_ADD, AM_R_R, R_A, R_C};
    temp[0x82] = Instruction{IN_ADD, AM_R_R, R_A, R_D};
    temp[0x83] = Instruction{IN_ADD, AM_R_R, R_A, R_E};
    temp[0x84] = Instruction{IN_ADD, AM_R_R, R_A, R_H};
    temp[0x85] = Instruction{IN_ADD, AM_R_R, R_A, R_L};
    temp[0x86] = Instruction{IN_ADD, AM_R_MR, R_A, R_HL};
    temp[0x87] = Instruction{IN_ADD, AM_R_R, R_A, R_A};
    temp[0x88] = Instruction{IN_ADC, AM_R_R, R_A, R_B};
    temp[0x89] = Instruction{IN_ADC, AM_R_R, R_A, R_C};
    temp[0x8A] = Instruction{IN_ADC, AM_R_R, R_A, R_D};
    temp[0x8B] = Instruction{IN_ADC, AM_R_R, R_A, R_E};
    temp[0x8C] = Instruction{IN_ADC, AM_R_R, R_A, R_H};
    temp[0x8D] = Instruction{IN_ADC, AM_R_R, R_A, R_L};
    temp[0x8E] = Instruction{IN_ADC, AM_R_MR, R_A, R_HL};
    temp[0x8F] = Instruction{IN_ADC, AM_R_R, R_A, R_A};
    // 0x90
    temp[0x90] = Instruction{IN_SUB, AM_R_R, R_A, R_B};
    temp[0x91] = Instruction{IN_SUB, AM_R_R, R_A, R_C};
    temp[0x92] = Instruction{IN_SUB, AM_R_R, R_A, R_D};
    temp[0x93] = Instruction{IN_SUB, AM_R_R, R_A, R_E};
    temp[0x94] = Instruction{IN_SUB, AM_R_R, R_A, R_H};
    temp[0x95] = Instruction{IN_SUB, AM_R_R, R_A, R_L};
    temp[0x96] = Instruction{IN_SUB, AM_R_MR, R_A, R_HL};
    temp[0x97] = Instruction{IN_SUB, AM_R_R, R_A, R_A};
    temp[0x98] = Instruction{IN_SBC, AM_R_R, R_A, R_B};
    temp[0x99] = Instruction{IN_SBC, AM_R_R, R_A, R_C};
    temp[0x9A] = Instruction{IN_SBC, AM_R_R, R_A, R_D};
    temp[0x9B] = Instruction{IN_SBC, AM_R_R, R_A, R_E};
    temp[0x9C] = Instruction{IN_SBC, AM_R_R, R_A, R_H};
    temp[0x9D] = Instruction{IN_SBC, AM_R_R, R_A, R_L};
    temp[0x9E] = Instruction{IN_SBC, AM_R_MR, R_A, R_HL};
    temp[0x9F] = Instruction{IN_SBC, AM_R_R, R_A, R_A};
    // 0xA0
    temp[0xA0] = Instruction{IN_AND, AM_R_R, R_A, R_B};
    temp[0xA1] = Instruction{IN_AND, AM_R_R, R_A, R_C};
    temp[0xA2] = Instruction{IN_AND, AM_R_R, R_A, R_D};
    temp[0xA3] = Instruction{IN_AND, AM_R_R, R_A, R_E};
    temp[0xA4] = Instruction{IN_AND, AM_R_R, R_A, R_H};
    temp[0xA5] = Instruction{IN_AND, AM_R_R, R_A, R_L};
    temp[0xA6] = Instruction{IN_AND, AM_R_MR, R_A, R_HL};
    temp[0xA7] = Instruction{IN_AND, AM_R_R, R_A, R_A};
    temp[0xA8] = Instruction{IN_XOR, AM_R_R, R_A, R_B};
    temp[0xA9] = Instruction{IN_XOR, AM_R_R, R_A, R_C};
    temp[0xAA] = Instruction{IN_XOR, AM_R_R, R_A, R_D};
    temp[0xAB] = Instruction{IN_XOR, AM_R_R, R_A, R_E};
    temp[0xAC] = Instruction{IN_XOR, AM_R_R, R_A, R_H};
    temp[0xAD] = Instruction{IN_XOR, AM_R_R, R_A, R_L};
    temp[0xAE] = Instruction{IN_XOR, AM_R_MR, R_A, R_HL};
    temp[0xAF] = Instruction{IN_XOR, AM_R_R, R_A, R_A};
    
    // 0xB0
    temp[0xB0] = Instruction{IN_OR, AM_R_R, R_A, R_B};
    temp[0xB1] = Instruction{IN_OR, AM_R_R, R_A, R_C};
    temp[0xB2] = Instruction{IN_OR, AM_R_R, R_A, R_D};
    temp[0xB3] = Instruction{IN_OR, AM_R_R, R_A, R_E};
    temp[0xB4] = Instruction{IN_OR, AM_R_R, R_A, R_H};
    temp[0xB5] = Instruction{IN_OR, AM_R_R, R_A, R_L};
    temp[0xB6] = Instruction{IN_OR, AM_R_MR, R_A, R_HL};
    temp[0xB7] = Instruction{IN_OR, AM_R_R, R_A, R_A};
    temp[0xB8] = Instruction{IN_CP, AM_R_R, R_A, R_B};
    temp[0xB9] = Instruction{IN_CP, AM_R_R, R_A, R_C};
    temp[0xBA] = Instruction{IN_CP, AM_R_R, R_A, R_D};
    temp[0xBB] = Instruction{IN_CP, AM_R_R, R_A, R_E};
    temp[0xBC] = Instruction{IN_CP, AM_R_R, R_A, R_H};
    temp[0xBD] = Instruction{IN_CP, AM_R_R, R_A, R_L};
    temp[0xBE] = Instruction{IN_CP, AM_R_MR, R_A, R_HL};
    temp[0xBF] = Instruction{IN_CP, AM_R_R, R_A, R_A};

    // 0xC0
    temp[0xC0] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_NZ};
    temp[0xC1] = Instruction{IN_POP, AM_R, R_BC};
    temp[0xC2] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_NZ};
    temp[0xC3] = Instruction{IN_JP, AM_R_N16, R_PC};
    temp[0xC4] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_NZ};
    temp[0xC5] = Instruction{IN_PUSH, AM_R, R_BC};
    temp[0xC6] = Instruction{IN_ADD, AM_R_N8, R_A};
    temp[0xC7] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x00};
    temp[0xC8] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_Z};
    temp[0xC9] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_NONE};
    temp[0xCA] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_Z};
    temp[0xCB] = Instruction{IN_CB, AM_R_N8};
    temp[0xCC] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_Z};
    temp[0xCD] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_NONE};
    temp[0xCE] = Instruction{IN_ADC, AM_R_N8, R_A};
    temp[0xCF] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x08};

    // 0xD0
    temp[0xD0] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_NC};
    temp[0xD1] = Instruction{IN_POP, AM_R, R_DE};
    temp[0xD2] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_NC};
    temp[0xD4] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_NC};
    temp[0xD5] = Instruction{IN_PUSH, AM_R, R_DE};
    temp[0xD6] = Instruction{IN_SUB, AM_R_N8, R_A};
    temp[0xD7] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x10};
    temp[0xD8] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_C};
    temp[0xD9] = Instruction{IN_RETI, AM_R, R_PC, R_NONE, C_NONE};
    temp[0xDA] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_C};
    temp[0xDC] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_C};
    temp[0xDE] = Instruction{IN_SBC, AM_R_N8, R_A};
    temp[0xDF] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x18};

    // 0xE0
    temp[0xE0] = Instruction{IN_LDH, AM_MN8_R, R_A};
    temp[0xE1] = Instruction{IN_POP, AM_R, R_HL};
    temp[0xE2] = Instruction{IN_LD, AM_MR_R, R_C, R_A};
    temp[0xE5] = Instruction{IN_PUSH, AM_R, R_HL};
    temp[0xE6] = Instruction{IN_AND, AM_R_N8, R_A};
    temp[0xE7] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x20};
    temp[0xE8] = Instruction{IN_ADD, AM_R_N8, R_SP};
    temp[0xE9] = Instruction{IN_JP, AM_R_R, R_PC, R_HL};
    temp[0xEA] = Instruction{IN_LD, AM_MN16_R, R_A};
    temp[0xEE] = Instruction{IN_XOR, AM_R_N8, R_A};
    temp[0xEF] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x28};
    // 0xF0
    temp[0xF0] = Instruction{IN_LDH, AM_R_MN8, R_A};
    temp[0xF1] = Instruction{IN_POP, AM_R, R_AF};
    temp[0xF2] = Instruction{IN_LD, AM_R_MR, R_A, R_C};
    temp[0xF3] = Instruction{IN_DI};
    temp[0xF5] = Instruction{IN_PUSH, AM_R, R_AF};
    temp[0xF6] = Instruction{IN_OR, AM_R_N8, R_A};
    temp[0xF7] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x30};
    temp[0xF8] = Instruction{IN_LD, AM_R_R, R_HL, R_SP};
    temp[0xF9] = Instruction{IN_LD, AM_R_R, R_SP, R_HL};
    temp[0xFA] = Instruction{IN_LD, AM_R_MN16, R_A};
    temp[0xFB] = Instruction{IN_EI};
    temp[0xFE] = Instruction{IN_CP, AM_R_N8, R_A};
    temp[0xFF] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x38};

    return temp;
}();


Cpu::Cpu(Emu* emu) {
    m_emu = emu;
}

void Cpu::init() {
    m_regs = {0};
    m_regs.PC = 0x100;
    m_regs.SP = 0xFFFE;
    m_regs.A = 0x01;
    m_regs.F = 0xB0;
    m_regs.B = 0x00;
    m_regs.C = 0x13;
    m_regs.D = 0x00;
    m_regs.E = 0xD8;
    m_regs.H = 0x01;
    m_regs.L = 0x4D;

    m_IERegister = 0;
    m_intFlags = 0;
    m_intMasterEnabled = false;
    m_enablingIME = false;
}

void Cpu::step() {
    if(!m_halted) {
        printCPUInfo();
        u8 opcode = m_emu->getBus()->read(m_regs.PC);
        m_regs.PC++;
        cycle(1);
        try {
            fetchInstuction(opcode);
            fetchData();
            runInstruction();
        } catch (std::string error) {
            
        }
    } else {
        cycle(1);

        if(m_intFlags) {
            m_halted = false;
        }
    }

    if(m_intMasterEnabled) {
        handleInterrupts();
        m_enablingIME = false;
    }

    if(m_enablingIME) {
        m_intMasterEnabled = true;
    }

    dbgUpate();
    dbgPrint();
    writeCpuInfo();
    // std::cin.get();
}

void Cpu::cycle(int ticks) {
    for(int i = 0; i < ticks; i++) {
        for(int j = 0; j < 4; j++) {
            m_ticks++;
            m_emu->getTimer()->tick();
            m_emu->getPpu()->tick();
        }
        m_emu->getDma()->tick();
    }
}

void Cpu::fetchInstuction(u8 opcode) {
    std::cout << "INFO: Running instruction " << std::hex << (int)opcode << std::endl;
    if(INSTRUCTIONS[opcode].insType == IN_NONE) {
        throw std::runtime_error("ERROR: Unsupported opcode!");
    }
    m_curInst = INSTRUCTIONS[opcode];
}

void Cpu::runInstruction() {
    switch (m_curInst.insType) {
        case IN_NOP:
            break;
        case IN_JP:
            jmp();
            break;
        case IN_JR:
            jr();
            break;
        case IN_LD:
            ld();
            break;
        case IN_LDH:
            ldh();
            break;
        case IN_PUSH:
            push();
            break;
        case IN_POP:
            pop();
            break;
        case IN_CALL:
            call();
            break;
        case IN_RET:
            ret();
            break;
        case IN_RETI:
            reti();
            break;
        case IN_RST:
            rst();
            break;
        case IN_INC:
            inc();
            break;
        case IN_DEC:
            dec();
            break;
        case IN_ADD:
            add();
            break;
        case IN_ADC:
            adc();
            break;
        case IN_SUB:
            sub();
            break;
        case IN_SBC:
            sbc();
            break;
        case IN_XOR:
            XOR();
            break;
        case IN_AND:
            AND();
            break;
        case IN_OR:
            OR();
            break;
        case IN_CP:
            CP();
            break;
        case IN_DI: 
            di();
            break;
        case IN_EI: 
            ei();
            break;
        case IN_HALT: 
            halt();
            break;
        case IN_CB: 
            cb();
            break;
        case IN_RLCA:
            rlca();
            break;
        case IN_RLA:
            rla();
            break;
        case IN_RRCA:
            rrca();
            break;
        case IN_RRA:
            rra();
            break;
        case IN_DAA:
            daa();
            break;
        case IN_SCF:
            scf();
            break;
        case IN_CPL:
            cpl();
            break;
        case IN_CCF:
            ccf();
            break;
        default:
            throw std::runtime_error("ERROR: Unsupported instruction!");
    }
}

void Cpu::add() {
    u16 result = m_curInstData.param1 + m_curInstData.param2;
    
    clearFlag(F_N);
    clearFlag(F_H);
    clearFlag(F_C);

    if(m_curInst.reg1 != R_HL) {
        result = result & 0xFF;
        clearFlag(F_Z);
        if(result == 0) {
            setFlag(F_Z);
        }

        if(((m_curInstData.param1 & 0xF) + (m_curInstData.param2 & 0xF)) >= 0x10) {
            setFlag(F_H);
        }

        if(((m_curInstData.param1 & 0xFF) + (m_curInstData.param2 & 0xFF)) >= 0x100) {
            setFlag(F_C);
        }
    } else {
        u32 param1 = m_curInstData.param1;
        u32 param2 = m_curInstData.param2;
        if(((param1 & 0xFFF) + (param2 & 0xFFF)) >= 0x1000) {
            setFlag(F_H);
        }

        if(((param1 & 0xFFFF) + (param2 & 0xFFFF)) >= 0x10000) {
            setFlag(F_C);
        }
    }

    if(m_curInst.reg1 == R_SP) {
        i8 value = m_curInstData.param2;
        result = m_curInstData.param1 + value;
        if((m_curInstData.param1 & 0xF + m_curInstData.param2 & 0xF) >= 0x10) {
            setFlag(F_H);
        }

        if((m_curInstData.param1 & 0xFF + m_curInstData.param2 & 0xFF) >= 0x100) {
            setFlag(F_C);
        }

        clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::adc() {
    u8 carry = getFlag(F_C);
    u16 result = m_curInstData.param1 + m_curInstData.param2 + carry;
    result = result & 0xFF;
    clearFlag(F_N);
    clearFlag(F_H);
    clearFlag(F_C);
    clearFlag(F_Z);


    if(result == 0) {
        setFlag(F_Z);
    }

    if(((m_curInstData.param1 & 0xF) + (m_curInstData.param2 & 0xF)) + carry >= 0x10) {
        setFlag(F_H);
    }

    if(((m_curInstData.param1 & 0xFF) + (m_curInstData.param2 & 0xFF)) + carry >= 0x100) {
        setFlag(F_C);
    }
    
    putData(result);
}

void Cpu::sub() {
    // u8 carry = getFlag(F_C);
    u16 result = m_curInstData.param1 - m_curInstData.param2;
    result = result & 0xFF;
    setFlag(F_N);
    clearFlag(F_H);
    clearFlag(F_C);
    clearFlag(F_Z);


    if(result == 0) {
        setFlag(F_Z);
    }

    if((m_curInstData.param1 & 0xF) < (m_curInstData.param2 & 0xF)) {
        setFlag(F_H);
    }

    if(m_curInstData.param1 < m_curInstData.param2) {
        setFlag(F_C);
    }
    
    putData(result);
}

void Cpu::sbc() {
    u8 carry = getFlag(F_C);
    u16 result = m_curInstData.param1 - (m_curInstData.param2 + carry);
    result = result & 0xFF;
    setFlag(F_N);
    clearFlag(F_H);
    clearFlag(F_C);
    clearFlag(F_Z);


    if(result == 0) {
        setFlag(F_Z);
    }

    if((m_curInstData.param1 & 0xF) < (m_curInstData.param2 & 0xF) + carry) {
        setFlag(F_H);
    }

    if(m_curInstData.param1 < m_curInstData.param2 + carry) {
        setFlag(F_C);
    }
    
    putData(result);
}

void Cpu::inc() {
    u16 result = m_curInstData.param1 + 1;
    
    if(m_curInst.addrMode == AM_MR || (m_curInst.addrMode == AM_R &&
        !(m_curInst.reg1 == R_BC || m_curInst.reg1 == R_DE || m_curInst.reg1 == R_HL || m_curInst.reg1 == R_SP))) {
        result = result & 0xFF;
        clearFlag(F_N);
        if(result == 0) {
            setFlag(F_Z);
        } else {
            clearFlag(F_Z);
        }
        if((m_curInstData.param1 & 0b1111) == 0b1111) {
            setFlag(F_H);
        } else {
            clearFlag(F_H);
        }
    }


    putData(result);
}

void Cpu::dec() {
    u16 result = m_curInstData.param1 - 1;
    
    if(m_curInst.addrMode == AM_MR || (m_curInst.addrMode == AM_R &&
        !(m_curInst.reg1 == R_BC || m_curInst.reg1 == R_DE || m_curInst.reg1 == R_HL || m_curInst.reg1 == R_SP))) {
        result = result & 0xFF;
        setFlag(F_N);
        if(result == 0) {
            setFlag(F_Z);
        } else {
            clearFlag(F_Z);
        }

        if((m_curInstData.param1 & 0b1111) == 0b0000) {
            setFlag(F_H);
        } else {
            clearFlag(F_H);
        }
    }


    putData(result);
}

void Cpu::XOR() {
    u16 result = m_curInstData.param1 ^ m_curInstData.param2;
    clearFlag(F_N);
    clearFlag(F_C);
    clearFlag(F_H);
    if(result == 0) {
        setFlag(F_Z);
    } else {
        clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::AND() {
    u16 result = m_curInstData.param1 & m_curInstData.param2;
    clearFlag(F_N);
    clearFlag(F_C);
    setFlag(F_H);
    if(result == 0) {
        setFlag(F_Z);
    } else {
        clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::OR() {
    u16 result = m_curInstData.param1 | m_curInstData.param2;
    clearFlag(F_N);
    clearFlag(F_C);
    clearFlag(F_H);
    if(result == 0) {
        setFlag(F_Z);
    } else {
        clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::CP() {
    clearFlag(F_Z);
    setFlag(F_N);
    clearFlag(F_C);
    clearFlag(F_H);
    if(m_curInstData.param1 == m_curInstData.param2) {
        setFlag(F_Z);
    }

    if(m_curInstData.param1 < m_curInstData.param2) {
        setFlag(F_C);
    }

    if((m_curInstData.param1 & 0b1111) < (m_curInstData.param2 & 0b1111)) {
        setFlag(F_H);
    }
}

void Cpu::jmp() {
    // putData(m_curInstData.param2);
    // if(checkCond()) {
    //     writeReg(R_PC, m_curInstData.param2);
    // }
    // cycle(1);   
    jumpToAddress(m_curInstData.param2, checkCond(), false);
}

void Cpu::jr() {
    i8 offset = (m_curInstData.param2 & 0xFF);
    u16 address = m_regs.PC + offset;
    jumpToAddress(address, checkCond(), false);
}

void Cpu::call() {
    jumpToAddress(m_curInstData.param2, checkCond(), true);
}

void Cpu::ret() {
    if(m_curInst.cond != C_NONE) {
        cycle(1);
    }

    if(checkCond()) {
        u16 low = popStack();
        cycle(1);
        u16 high = popStack();
        cycle(1);
    
        u16 address = low | (high << 8);
        jumpToAddress(address, true, false);
    }
}

void Cpu::reti() {
    m_intMasterEnabled = true;
    ret();
}

void Cpu::rst() {
    jumpToAddress(m_curInst.param, checkCond(), true);
}

void Cpu::di() {
    m_intMasterEnabled = false;
}

void Cpu::ei() {
    m_enablingIME = true;
}

void Cpu::cb() {
    u8 inst = m_curInstData.param2;
    RegType reg = getCBReg(inst & 0b111);
    u8 operation = (inst & 0b11111000) >> 3;
    u8 bitOp = operation & 0b111; // For OPs set, res and bit
    if(operation >= 0x08) {
        operation = 0x07 + ((operation & (0xFF - 0b111)) >> 3);
    }
    

    switch (operation) {
        case CB_RLC: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            u8 overflow = 0;
            if(value & 0x80) {
                setFlag(F_C);
                overflow = 1;
            }

            value = ((value << 1) & 0xFF) + overflow;
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        case CB_RRC: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            u8 overflow = 0;
            if(value & 0b1) {
                setFlag(F_C);
                overflow = 1;
            }

            value = ((value >> 1) & 0xFF) + (overflow << 7);
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }
           
        case CB_RL: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            u8 carry = getFlag(F_C);

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            if(value & 0x80) {
                setFlag(F_C);
            }

            value = ((value << 1) & 0xFF) + carry;
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        case CB_RR: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            u8 carry = getFlag(F_C);

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            if(value & 0b1) {
                setFlag(F_C);
            }

            value = ((value >> 1) & 0xFF) + (carry << 7);
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }
        
        case CB_SLA: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            if(value & 0x80) {
                setFlag(F_C);
            }

            value = ((value << 1) & 0xFF);
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        case CB_SRA: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            if(value & 0b1) {
                setFlag(F_C);
            }

            u8 lastBit = (value & 0x80);
            value = ((value >> 1) & 0xFF) | lastBit;
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        case CB_SWAP: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            value = ((value & 0xF) << 4) | ((value & 0xF0) >> 4);
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        case CB_SRL: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            clearFlag(F_Z);
            clearFlag(F_N);
            clearFlag(F_C);
            clearFlag(F_H);

            if(value & 0b1) {
                setFlag(F_C);
            }

            value = ((value >> 1) & 0xFF);
            if(value == 0) {
                setFlag(F_Z);
            }

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        case CB_BIT: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            setFlag(F_Z);
            clearFlag(F_N);
            setFlag(F_H);

            if(value & (1 << bitOp)) {
                clearFlag(F_Z);
            }
            break;
        }

        case CB_RES: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            value = value & (0xFF - (1 << bitOp));

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        case CB_SET: {
            u16 value = readReg(reg);
            if(reg == R_HL) {
                value = m_emu->getBus()->read(value);
            }

            value = value | (1 << bitOp);

            if(reg == R_HL) {
                m_emu->getBus()->write(readReg(reg), value);
            } else {
                writeReg(reg, value);
            }
            break;
        }

        default:
            throw std::runtime_error("ERROR: No such CB operation!");
    }
}

void Cpu::rlca() {
    u16 value = readReg(R_A);
    clearFlag(F_Z);
    clearFlag(F_N);
    clearFlag(F_C);
    clearFlag(F_H);

    u8 overflow = 0;
    if(value & 0x80) {
        setFlag(F_C);
        overflow = 1;
    }

    value = ((value << 1) & 0xFF) + overflow;
    writeReg(R_A, value);

}

void Cpu::rla() {
    u16 value = readReg(R_A);
    u8 carry = getFlag(F_C);

    clearFlag(F_Z);
    clearFlag(F_N);
    clearFlag(F_C);
    clearFlag(F_H);

    if(value & 0x80) {
        setFlag(F_C);
    }

    value = ((value << 1) & 0xFF) + carry;
    writeReg(R_A, value);
}


void Cpu::rrca() {
    u16 value = readReg(R_A);

    clearFlag(F_Z);
    clearFlag(F_N);
    clearFlag(F_C);
    clearFlag(F_H);

    u8 overflow = 0;
    if(value & 0b1) {
        setFlag(F_C);
        overflow = 1;
    }

    value = ((value >> 1) & 0xFF) + (overflow << 7);
    writeReg(R_A, value);
}

void Cpu::rra() {
    u16 value = readReg(R_A);
    u8 carry = getFlag(F_C);

    clearFlag(F_Z);
    clearFlag(F_N);
    clearFlag(F_C);
    clearFlag(F_H);

    if(value & 0b1) {
        setFlag(F_C);
    }

    value = ((value >> 1) & 0xFF) + (carry << 7);
    writeReg(R_A, value);
}

// 84DC82AA
void Cpu::daa() {
    u8 value = readReg(R_A);
    u8 adjustment = 0x0;
    clearFlag(F_Z);
    if(getFlag(F_N)) {
        if(getFlag(F_H)) {
            adjustment += 0x6;
        }

        if(getFlag(F_C)) {
            adjustment += 0x60;
        }
        value -= adjustment;
        // uncomenting the following line fixed the issue...
        // TODO: Investigate why this is unnecessary
        // clearFlag(F_C); 
    } else {
        if(getFlag(F_H) || ((value & 0xF) > 0x9)) {
            adjustment += 0x6;
        }

        if(getFlag(F_C) || (value > 0x99)) {
            adjustment += 0x60;
            setFlag(F_C);
        } else {
            clearFlag(F_C);
        }
        value += adjustment;
    }

    clearFlag(F_H);
    if(value == 0) {
        setFlag(F_Z);
    }

    writeReg(R_A, value);
}

void Cpu::cpl() {
    u8 value = readReg(R_A);

    setFlag(F_N);
    setFlag(F_H);
    writeReg(R_A, ~value);  
}

void Cpu::ccf() {
    if(getFlag(F_C)) {
        clearFlag(F_C);
    } else {
        setFlag(F_C);
    }
    clearFlag(F_N);
    clearFlag(F_H);
}

void Cpu::scf() {
    setFlag(F_C);
    clearFlag(F_N);
    clearFlag(F_H);
}

void Cpu::halt() {
    m_halted = true;
}

void Cpu::ld() {
    // if(m_curInst.addrMode == AM_MR_R && m_curInst.reg1 == R_C) {
    //     m_curInstData.param1 += 0xFF00;
    // }

    if(m_curInst.reg2 == R_SP) {
        // Because this is a unique addressing mode (2 regs and e8) we just
        // read the value here instead of complicating the code and creating
        // another addressing mode just for this
        u8 value = m_emu->getBus()->read(m_regs.PC);
        m_regs.PC++;
        cycle(1);

        u16 result = m_curInstData.param2 + (i8)value;

        clearFlag(F_Z);
        clearFlag(F_N);
        clearFlag(F_H);
        clearFlag(F_C);
        
        if((m_curInstData.param2 & 0xF) + (value & 0xF) >= 0x10) {
            setFlag(F_H);
        }
        if((m_curInstData.param2 & 0xFF) + (value & 0xFF) >= 0x100) {
            setFlag(F_C);
        }
        putData(result);
    } else if(m_curInst.reg1 == R_SP && m_curInst.addrMode == AM_MN16_R) {
        // We require special handling here, can't just use the method putData
        u16 address = m_curInstData.param1;
        m_emu->getBus()->write(address, m_curInstData.param2 & 0xFF);
        m_emu->getBus()->write(address + 1, m_curInstData.param2 >> 8);

    } else {
        putData(m_curInstData.param2);
    }
    
    
    cycle(1);
}

void Cpu::ldh() {
    putData(m_curInstData.param2);
    cycle(1);
}

void Cpu::push() {
    u8 high = (m_curInstData.param1 >> 8) & 0xFF;
    cycle(1);
    pushStack(high);
    

    u8 low = m_curInstData.param1 & 0xFF;
    cycle(1);
    pushStack(low);
    
    cycle(1);
}

void Cpu::pop() {
    u16 low = popStack();
    cycle(1);
    u16 high = popStack();
    cycle(1);

    u16 result = low | (high << 8);
    if(m_curInst.reg1 == R_AF) {
        result = result & 0xFFF0;
    }

    putData(result);
}

void Cpu::fetchData() {
    switch (m_curInst.addrMode) {
        case AM_NONE:
            break;
        case AM_R:
            m_curInstData = InstructionData{readReg(m_curInst.reg1), 0};
            break;
        case AM_MR:
            m_curInstData = InstructionData{m_emu->getBus()->read(readReg(m_curInst.reg1)), 0};
            break;
        case AM_MR_N8:
        case AM_R_N8: {
            u16 result = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            m_curInstData = InstructionData{readReg(m_curInst.reg1), result};
            break;
        }
        case AM_R_N16: {
            u16 low = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            u16 high = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            u16 result = (high << 8) + low;
            m_curInstData = InstructionData{0, result};
            break;
        }
        case AM_HLI_R:
        case AM_HLD_R:
        case AM_MR_R:
        case AM_R_R:
            m_curInstData = InstructionData{readReg(m_curInst.reg1), readReg(m_curInst.reg2)};
            break;
        case AM_R_HLI:
        case AM_R_HLD:
        case AM_R_MR:
            if(m_curInst.reg2 == R_C) {
                m_curInstData = InstructionData{readReg(m_curInst.reg1),
                    m_emu->getBus()->read(readReg(m_curInst.reg2) + 0xFF00)};
            } else {
                m_curInstData = InstructionData{readReg(m_curInst.reg1),
                    m_emu->getBus()->read(readReg(m_curInst.reg2))};
            }
            
            break;
        case AM_R_MN16: {
            u16 low = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            u16 high = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            u16 result = (high << 8) + low;
            m_curInstData = InstructionData{0, m_emu->getBus()->read(result)};
            break;
        }
        case AM_MN16_R: {
            u16 low = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            u16 high = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            u16 result = (high << 8) + low;
            m_curInstData = InstructionData{result, readReg(m_curInst.reg1)};
            break;
        }
        case AM_R_MN8: {
            u16 result = m_emu->getBus()->read(m_regs.PC) + 0xFF00;
            m_regs.PC++;
            cycle(1);

            m_curInstData = InstructionData{0, m_emu->getBus()->read(result)};
            break;
        }
        case AM_MN8_R: {
            u16 result = m_emu->getBus()->read(m_regs.PC) + 0xFF00;
            m_regs.PC++;
            cycle(1);

            m_curInstData = InstructionData{result, readReg(m_curInst.reg1)};
            break;
        }
        // case AM_HLI_R:
        //     m_curInstData = InstructionData{readReg(m_curInst.reg1), readReg(m_curInst.reg2)};
        //     break;
        // case AM_R_HLI:
        //     m_curInstData = InstructionData{readReg(m_curInst.reg1), readReg(m_curInst.reg2)};
        //     break;
        default:
            throw std::runtime_error("ERROR: No such addressing mode");
    }
}

bool Cpu::checkCond() {
    switch (m_curInst.cond) {
        case C_NONE:
            return true;
        case C_Z:
            return getFlag(F_Z) == 1;
        case C_NZ:
            return getFlag(F_Z) == 0;
        case C_C:
            return getFlag(F_C) == 1;
        case C_NC:
            return getFlag(F_C) == 0;
        default:
            throw std::runtime_error("ERROR: No such condition!");
    }
}

void Cpu::putData(u16 data) {
    switch (m_curInst.addrMode) {
        case AM_NONE:
            break;
        case AM_R:
            writeReg(m_curInst.reg1, data);
            break;
        case AM_MR:
            m_emu->getBus()->write(readReg(m_curInst.reg1), data);
            break;
        case AM_R_N8:
            writeReg(m_curInst.reg1, data);
            break;
        case AM_R_N16:
            writeReg(m_curInst.reg1, data);
            break;
        case AM_R_MN8:
        case AM_R_MN16:
        case AM_R_MR:
        case AM_R_R:
            writeReg(m_curInst.reg1, data);
            break;
        case AM_MR_R:
            // writeReg(m_curInst.reg1, data);
            if(m_curInst.reg1 == R_C) {
                m_emu->getBus()->write(readReg(m_curInst.reg1) + 0xFF00, data);
            } else {
                m_emu->getBus()->write(readReg(m_curInst.reg1), data);
            }
            break;
        case AM_HLI_R:
            // writeReg(m_curInst.reg1, data);
            m_emu->getBus()->write(readReg(m_curInst.reg1), data);
            writeReg(R_HL, readReg(R_HL) + 1);
            break;
        case AM_R_HLI:
            writeReg(m_curInst.reg1, data);
            writeReg(R_HL, readReg(R_HL) + 1);
            break;
        case AM_HLD_R:
            // writeReg(m_curInst.reg1, data);
            m_emu->getBus()->write(readReg(m_curInst.reg1), data);
            writeReg(R_HL, readReg(R_HL) - 1);
            break;
        case AM_R_HLD:
            writeReg(m_curInst.reg1, data);
            writeReg(R_HL, readReg(R_HL) - 1);
            break;
        case AM_MR_N8:
            m_emu->getBus()->write(readReg(m_curInst.reg1), data);
            break;
        case AM_MN8_R:
        case AM_MN16_R:
            m_emu->getBus()->write(m_curInstData.param1, data);
            break;
        default:
            throw std::runtime_error("ERROR: No such addressing mode");
    }
}

void Cpu::printCPUInfo() {
    std::cout << "Tick " << std::hex << (int)m_ticks << ":" << std::endl;
    std::cout << "PC: 0x" << std::hex << (int)m_regs.PC;
    std::cout << " (" << std::hex << (int)m_emu->getBus()->read(m_regs.PC );
    std::cout << " " << std::hex << (int)m_emu->getBus()->read(m_regs.PC + 1);
    std::cout << " " << std::hex << (int)m_emu->getBus()->read(m_regs.PC + 2);
    std::cout << ")";
    std::cout << " SP: 0x" << std::hex << (int)m_regs.SP;
    std::cout << " A: 0x" << std::hex << (int)m_regs.A;
    std::cout << " F: 0x" << std::hex << (int)m_regs.F;
    std::cout << " AF: 0x" << std::hex << (int)readReg(R_AF);
    std::cout << " B: 0x" << std::hex << (int)m_regs.B;
    std::cout << " C: 0x" << std::hex << (int)m_regs.C;
    std::cout << " BC: 0x" << std::hex << (int)readReg(R_BC);
    std::cout << " D: 0x" << std::hex << (int)m_regs.D;
    std::cout << " E: 0x" << std::hex << (int)m_regs.E;
    std::cout << " DE: 0x" << std::hex << (int)readReg(R_DE);
    std::cout << " H: 0x" << std::hex << (int)m_regs.H;
    std::cout << " L: 0x" << std::hex << (int)m_regs.L;
    std::cout << " HL: 0x" << std::hex << (int)readReg(R_HL);
    std::cout << " Flags: ";
    if(getFlag(F_Z)) {
        std::cout << 'Z';
    } else {
        std::cout << '-';
    }
    if(getFlag(F_N)) {
        std::cout << 'N';
    } else {
        std::cout << '-';
    }
    if(getFlag(F_H)) {
        std::cout << 'H';
    } else {
        std::cout << '-';
    }
    if(getFlag(F_C)) {
        std::cout << 'C';
    } else {
        std::cout << '-';
    }
    std::cout << std::endl;
}

u16 Cpu::readReg(RegType regType) {
    switch (regType) {
        case R_NONE:
            return 0;
        case R_A:
            return m_regs.A;
        case R_F:
            return m_regs.F;
        case R_B:
            return m_regs.B;
        case R_C:
            return m_regs.C;
        case R_D:
            return m_regs.D;
        case R_E:
            return m_regs.E;
        case R_H:
            return m_regs.H;
        case R_L:
            return m_regs.L;
        case R_SP:
            return m_regs.SP;
        case R_PC:
            return m_regs.PC;
        case R_AF:
            return reverse2Bytes(*reinterpret_cast<u16*>(&m_regs.A));
        case R_BC:
            return reverse2Bytes(*reinterpret_cast<u16*>(&m_regs.B));
        case R_DE:
            return reverse2Bytes(*reinterpret_cast<u16*>(&m_regs.D));
        case R_HL:
            return reverse2Bytes(*reinterpret_cast<u16*>(&m_regs.H));
        default:
            return 0;
    }
}

void Cpu::writeReg(RegType regType, u16 data) {
    switch (regType) {
        case R_NONE:
            break;
        case R_A:
            m_regs.A = static_cast<u8>(data);
            break;
        case R_F:
            m_regs.F = static_cast<u8>(data);
            break;
        case R_B:
            m_regs.B = static_cast<u8>(data);
            break;
        case R_C:
            m_regs.C = static_cast<u8>(data);
            break;
        case R_D:
            m_regs.D = static_cast<u8>(data);
            break;
        case R_E:
            m_regs.E = static_cast<u8>(data);
            break;
        case R_H:
            m_regs.H = static_cast<u8>(data);
            break;
        case R_L:
            m_regs.L = static_cast<u8>(data);
            break;
        case R_SP:
            m_regs.SP = data;
            break;
        case R_PC:
            m_regs.PC = data;
            break;
        case R_AF:
            *reinterpret_cast<u16*>(&m_regs.A) = reverse2Bytes(data);
            break;
        case R_BC:
            *reinterpret_cast<u16*>(&m_regs.B) = reverse2Bytes(data);
            break;
        case R_DE:
            *reinterpret_cast<u16*>(&m_regs.D) = reverse2Bytes(data);
            break;
        case R_HL:
            *reinterpret_cast<u16*>(&m_regs.H) = reverse2Bytes(data);
            break;
        default:
            break;

    }
}

u8 Cpu::getFlag(FlagType flagType) {
    switch (flagType) {
        case F_NONE:
            return 0;
        case F_Z:
            return m_regs.F & 0x80 ? 1 : 0;
        case F_N:
            return m_regs.F & 0x40 ? 1 : 0;
        case F_H:
            return m_regs.F & 0x20 ? 1 : 0;
        case F_C:
            return m_regs.F & 0x10 ? 1 : 0;
        default:
            return 0;
    }
}

void Cpu::setFlag(FlagType flagType) {
    switch (flagType) {
        case F_NONE:
            break;
        case F_Z:
            m_regs.F = m_regs.F | 0x80;
            break;
        case F_N:
            m_regs.F = m_regs.F | 0x40;
            break;
        case F_H:
            m_regs.F = m_regs.F | 0x20;
            break;
        case F_C:
            m_regs.F = m_regs.F | 0x10;
            break;
        default:
            break;
    }
}

void Cpu::clearFlag(FlagType flagType) {
    switch (flagType) {
        case F_NONE:
            break;
        case F_Z:
            m_regs.F = m_regs.F & (0xFF - 0x80);
            break;
        case F_N:
            m_regs.F = m_regs.F & (0xFF - 0x40);
            break;
        case F_H:
            m_regs.F = m_regs.F & (0xFF - 0x20);
            break;
        case F_C:
            m_regs.F = m_regs.F & (0xFF - 0x10);
            break;
        default:
            break;
    }
}

void Cpu::toggleFlag(FlagType flagType) {
    switch (flagType) {
        case F_NONE:
            break;
        case F_Z:
            m_regs.F = m_regs.F ^ 0x80;
            break;
        case F_N:
            m_regs.F = m_regs.F ^ 0x40;
            break;
        case F_H:
            m_regs.F = m_regs.F ^ 0x20;
            break;
        case F_C:
            m_regs.F = m_regs.F ^ 0x10;
            break;
        default:
            break;
    }
}

u8 Cpu::readIERegister() {
    return m_IERegister;
}

void Cpu::writeIERegister(u8 data) {
    m_IERegister = data;
}

u8 Cpu::readIntFlags() {
    return m_intFlags;
}

void Cpu::writeIntFlags(u8 data) {
    m_intFlags = data;
}

void Cpu::pushStack(u8 data) {
    m_regs.SP--;
    m_emu->getBus()->write(m_regs.SP, data);
}

u8 Cpu::popStack() {
    u8 data = m_emu->getBus()->read(m_regs.SP);
    m_regs.SP++;
    return data;
}

void Cpu::jumpToAddress(u16 address, bool shouldJump, bool pushPC, bool countCycle) {
    if(shouldJump) {
        if(pushPC) {
            if(countCycle) {
                cycle(2);
            }
            
            u8 high = (m_regs.PC >> 8) & 0xFF;
            pushStack(high);
                  
            u8 low = m_regs.PC & 0xFF;
            pushStack(low);
            
        }

        writeReg(R_PC, address);
        if(countCycle) {
            cycle(1);
        }
    }
    
}

RegType Cpu::getCBReg(u8 CBCode) {
    switch (CBCode) {
        case 0:
            return R_B;
        case 1:
            return R_C;
        case 2:
            return R_D;
        case 3:
            return R_E;
        case 4:
            return R_H;
        case 5:
            return R_L;
        case 6:
            return R_HL;
        case 7:
            return R_A;
        default:
            throw std::runtime_error("ERROR: No such CB register!");
            break;
    }
}

void Cpu::requestInterrupt(InterruptType inter) {
    m_intFlags = m_intFlags | inter;
}

bool Cpu::checkInt(u16 address, InterruptType inter) {
    if((m_intFlags & inter) && (m_IERegister & inter)) {
       
        handleInt(address);
        m_intFlags = m_intFlags & (~inter);
        m_halted = false;
        m_intMasterEnabled = false;

        return true;
    }
    return false;
}

void Cpu::handleInt(u16 address) {
    jumpToAddress(address, true, true, false);
}


void Cpu::handleInterrupts() {
    if (checkInt(0x40, IT_VBLANK)) {

    } else if (checkInt(0x48, IT_LCD_STAT)) {

    } else if (checkInt(0x50, IT_TIMER)) {

    }  else if (checkInt(0x58, IT_SERIAL)) {

    }  else if (checkInt(0x60, IT_JOYPAD)) {

    } 
}

void Cpu::dbgUpate() {
    if(m_emu->getBus()->read(0xFF02) == 0x81) {
        
        char msg = m_emu->getBus()->read(0xFF01);
        m_dbgMessage[m_msgSize] = msg;
        m_msgSize++;
        m_emu->getBus()->write(0xFF02, 0);
    }
}

#include <string.h>

void Cpu::dbgPrint() {
    if(m_dbgMessage[0]) {
        std::cout << "DBG: " << m_dbgMessage << std::endl;
    }
}

