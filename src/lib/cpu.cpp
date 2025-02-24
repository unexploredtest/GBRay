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
    temp[0x08] = Instruction{IN_LD, AM_MN16_R, R_SP};
    temp[0x0A] = Instruction{IN_LD, AM_R_MR, R_A, R_BC};
    temp[0x0B] = Instruction{IN_DEC, AM_R, R_BC};
    temp[0x0C] = Instruction{IN_INC, AM_R, R_C};
    temp[0x0D] = Instruction{IN_DEC, AM_R, R_C};
    temp[0x0E] = Instruction{IN_LD, AM_R_N8, R_C};
    // 0x10
    temp[0x11] = Instruction{IN_LD, AM_R_N16, R_DE};
    temp[0x12] = Instruction{IN_LD, AM_MR_R, R_DE, R_A};
    temp[0x13] = Instruction{IN_INC, AM_R, R_DE};
    temp[0x14] = Instruction{IN_INC, AM_R, R_D};
    temp[0x15] = Instruction{IN_DEC, AM_R, R_D};
    temp[0x16] = Instruction{IN_LD, AM_R_N8, R_D};
    temp[0x18] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_NONE};
    temp[0x1A] = Instruction{IN_LD, AM_R_MR, R_A, R_DE};
    temp[0x1B] = Instruction{IN_DEC, AM_R, R_DE};
    temp[0x1C] = Instruction{IN_INC, AM_R, R_E};
    temp[0x1D] = Instruction{IN_DEC, AM_R, R_E};
    temp[0x1E] = Instruction{IN_LD, AM_R_N8, R_E};
    // 0x20
    temp[0x20] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_NZ};
    temp[0x21] = Instruction{IN_LD, AM_R_N16, R_HL};
    temp[0x22] = Instruction{IN_LD, AM_HLI_R, R_HL, R_A};
    temp[0x23] = Instruction{IN_INC, AM_R, R_HL};
    temp[0x24] = Instruction{IN_INC, AM_R, R_H};
    temp[0x25] = Instruction{IN_DEC, AM_R, R_H};
    temp[0x26] = Instruction{IN_LD, AM_R_N8, R_H};
    temp[0x28] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_Z};
    temp[0x2A] = Instruction{IN_LD, AM_R_HLI, R_A, R_HL};
    temp[0x2B] = Instruction{IN_DEC, AM_R, R_HL};
    temp[0x2C] = Instruction{IN_INC, AM_R, R_L};
    temp[0x2D] = Instruction{IN_DEC, AM_R, R_L};
    temp[0x2E] = Instruction{IN_LD, AM_R_N8, R_L};
    // 0x30
    temp[0x30] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_NC};
    temp[0x31] = Instruction{IN_LD, AM_R_N16, R_SP};
    temp[0x32] = Instruction{IN_LD, AM_HLD_R, R_HL, R_A};
    temp[0x33] = Instruction{IN_INC, AM_R, R_SP};
    temp[0x34] = Instruction{IN_INC, AM_MR, R_HL};
    temp[0x35] = Instruction{IN_DEC, AM_MR, R_HL};
    temp[0x36] = Instruction{IN_LD, AM_MR_N8, R_HL};
    temp[0x38] = Instruction{IN_JR, AM_R_N8, R_PC, R_NONE, C_C};
    temp[0x3A] = Instruction{IN_LD, AM_R_HLD, R_A, R_HL};
    temp[0x3B] = Instruction{IN_DEC, AM_R, R_SP};
    temp[0x3C] = Instruction{IN_INC, AM_R, R_A};
    temp[0x3D] = Instruction{IN_DEC, AM_R, R_A};
    temp[0x3E] = Instruction{IN_LD, AM_R_N8, R_A};
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
    // temp[0x76] = Instruction{IN_LD, AM_R_MR, R_H, R_HL};
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

    // 0xC0
    temp[0xC0] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_NZ};
    temp[0xC1] = Instruction{IN_POP, AM_R, R_BC};
    temp[0xC2] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_NZ};
    temp[0xC3] = Instruction{IN_JP, AM_R_N16, R_PC};
    temp[0xC4] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_NZ};
    temp[0xC5] = Instruction{IN_PUSH, AM_R, R_BC};
    temp[0xC7] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x00};
    temp[0xC8] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_Z};
    temp[0xC9] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_NONE};
    temp[0xCA] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_Z};
    temp[0xCC] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_Z};
    temp[0xCD] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_NONE};
    temp[0xCF] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x08};

    // 0xD0
    temp[0xD0] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_NC};
    temp[0xD1] = Instruction{IN_POP, AM_R, R_DE};
    temp[0xD2] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_NC};
    temp[0xD4] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_NC};
    temp[0xD5] = Instruction{IN_PUSH, AM_R, R_DE};
    temp[0xD7] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x10};
    temp[0xD8] = Instruction{IN_RET, AM_R, R_PC, R_NONE, C_C};
    temp[0xD9] = Instruction{IN_RETI, AM_R, R_PC, R_NONE, C_NONE};
    temp[0xDA] = Instruction{IN_JP, AM_R_N16, R_PC, R_NONE, C_C};
    temp[0xDC] = Instruction{IN_CALL, AM_R_N16, R_PC, R_NONE, C_C};
    temp[0xDF] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x18};

    // 0xE0
    temp[0xE0] = Instruction{IN_LDH, AM_MN8_R, R_A};
    temp[0xE1] = Instruction{IN_POP, AM_R, R_HL};
    temp[0xE2] = Instruction{IN_LD, AM_MR_R, R_C, R_A};
    temp[0xE5] = Instruction{IN_PUSH, AM_R, R_HL};
    temp[0xE6] = Instruction{IN_AND, AM_R_N8, R_A};
    temp[0xE7] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x20};
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
    temp[0xF9] = Instruction{IN_LD, AM_R_R, R_SP, R_HL};
    temp[0xFA] = Instruction{IN_LD, AM_R_MN16, R_A};
    temp[0xFF] = Instruction{IN_RST, AM_R, R_PC, R_NONE, C_NONE, 0x38};

    return temp;
}();


Cpu::Cpu(Emu* emu) {
    m_emu = emu;
}

void Cpu::init() {
    m_regs = {0};
    m_regs.PC = 0x100;
}

void Cpu::step() {

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
    std::cin.get();
}

void Cpu::cycle(int ticks) {

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
        case IN_XOR:
            XOR();
            break;
        case IN_AND:
            AND();
            break;
        case IN_OR:
            OR();
            break;
        case IN_DI:
            di();
            break;
        default:
            throw std::runtime_error("ERROR: Unsupported instruction!");
    }
}

void Cpu::add() {
    u16 result = m_curInstData.param1 + m_curInstData.param2;
    Cpu::clearFlag(F_N);
    if(result == 0) {
        Cpu::clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::inc() {
    u16 result = m_curInstData.param1 + 1;
    
    if(m_curInst.addrMode == AM_MR || (m_curInst.addrMode == AM_R &&
        !(m_curInst.reg1 == R_BC || m_curInst.reg1 == R_DE || m_curInst.reg1 == R_HL || m_curInst.reg1 == R_SP))) {
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
        clearFlag(F_N);
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
    Cpu::clearFlag(F_N);
    Cpu::clearFlag(F_C);
    Cpu::clearFlag(F_H);
    if(result == 0) {
        Cpu::setFlag(F_Z);
    } else {
        Cpu::clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::AND() {
    u16 result = m_curInstData.param1 & m_curInstData.param2;
    Cpu::clearFlag(F_N);
    Cpu::clearFlag(F_C);
    Cpu::setFlag(F_H);
    if(result == 0) {
        Cpu::setFlag(F_Z);
    } else {
        Cpu::clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::OR() {
    u16 result = m_curInstData.param1 | m_curInstData.param2;
    Cpu::clearFlag(F_N);
    Cpu::clearFlag(F_C);
    Cpu::clearFlag(F_H);
    if(result == 0) {
        Cpu::setFlag(F_Z);
    } else {
        Cpu::clearFlag(F_Z);
    }
    putData(result);
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

void Cpu::ld() {
    if(m_curInst.addrMode == AM_MR_R && m_curInst.reg1 == R_C) {
        m_curInstData.param1 += 0xFF00;
    }
    putData(m_curInstData.param2);
    
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
            m_emu->getBus()->write(m_curInst.reg1, data);
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
            m_emu->getBus()->write(m_curInst.reg1, data);
            break;
        case AM_HLI_R:
            // writeReg(m_curInst.reg1, data);
            m_emu->getBus()->write(m_curInst.reg1, data);
            writeReg(R_HL, readReg(R_HL) + 1);
            break;
        case AM_R_HLI:
            writeReg(m_curInst.reg1, data);
            writeReg(R_HL, readReg(R_HL) + 1);
            break;
        case AM_HLD_R:
            // writeReg(m_curInst.reg1, data);
            m_emu->getBus()->write(m_curInst.reg1, data);
            writeReg(R_HL, readReg(R_HL) - 1);
            break;
        case AM_R_HLD:
            writeReg(m_curInst.reg1, data);
            writeReg(R_HL, readReg(R_HL) - 1);
            break;
        case AM_MR_N8:
            m_emu->getBus()->write(m_curInst.reg1, data);
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
            return 1 ? m_regs.F & 0x80 : 0;
        case F_N:
            return 1 ? m_regs.F & 0x40 : 0;
        case F_H:
            return 1 ? m_regs.F & 0x20 : 0;
        case F_C:
            return 1 ? m_regs.F & 0x10 : 0;
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

void Cpu::pushStack(u8 data) {
    m_regs.SP--;
    m_emu->getBus()->write(m_regs.SP, data);
}

u8 Cpu::popStack() {
    u8 data = m_emu->getBus()->read(m_regs.SP);
    m_regs.SP++;
    return data;
}

void Cpu::jumpToAddress(u16 address, bool shouldJump, bool pushPC) {
    if(shouldJump) {
        if(pushPC) {
            cycle(2);
            u8 high = (m_regs.PC >> 8) & 0xFF;
            pushStack(high);
                  
            u8 low = m_regs.PC & 0xFF;
            pushStack(low);
            
        }

        writeReg(R_PC, address);
        cycle(1);
    }
    
}