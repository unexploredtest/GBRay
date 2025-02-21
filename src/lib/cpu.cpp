#include "cpu.hpp"

static const std::array<Instruction, 0xFF> INSTRUCTIONS = [] {
    std::array<Instruction, 0xFF> temp = {};
    temp.fill(Instruction{}); // Unassigned values get the default NONE instruction
    temp[0x00] = Instruction{IN_NOP};
    temp[0x06] = Instruction{IN_LD, AM_R_N8, R_B};
    temp[0x0E] = Instruction{IN_LD, AM_R_N8, R_C};
    temp[0x11] = Instruction{IN_LD, AM_R_N16, R_DE};
    temp[0x21] = Instruction{IN_LD, AM_R_N16, R_HL};
    temp[0x47] = Instruction{IN_LD, AM_R_R, R_B, R_A};
    temp[0x80] = Instruction{IN_ADD, AM_R_R, R_A, R_B};
    temp[0xAF] = Instruction{IN_XOR, AM_R_R, R_A, R_A};
    temp[0xC3] = Instruction{IN_JP, AM_R_N16, R_PC};
    temp[0xF3] = Instruction{IN_DI};

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
        case IN_LD:
            ld();
            break;
        case IN_ADD:
            add();
            break;
        case IN_XOR:
            XOR();
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

void Cpu::XOR() {
    u16 result = m_curInstData.param1 ^ m_curInstData.param2;
    Cpu::clearFlag(F_N);
    Cpu::clearFlag(F_C);
    Cpu::clearFlag(F_H);
    if(result == 0) {
        Cpu::clearFlag(F_Z);
    }
    putData(result);
}

void Cpu::jmp() {
    // putData(m_curInstData.param2);
    writeReg(R_PC, m_curInstData.param2);
    cycle(1);   
}

void Cpu::di() {
    m_intMasterEnabled = false;
}

void Cpu::ld() {
    putData(m_curInstData.param2);
}

void Cpu::fetchData() {
    switch (m_curInst.addrMode) {
        case AM_NONE:
            break;
        case AM_R_N8: {
            u16 result = m_emu->getBus()->read(m_regs.PC);
            m_regs.PC++;
            cycle(1);

            m_curInstData = InstructionData{0, result};
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
        case AM_R_R:
            m_curInstData = InstructionData{readReg(m_curInst.reg1), readReg(m_curInst.reg2)};
            break;
        default:
            throw std::runtime_error("ERROR: No such addressing mode");
    }
}

void Cpu::putData(u16 data) {
    switch (m_curInst.addrMode) {
        case AM_NONE:
            break;
        case AM_R_N8:
            writeReg(m_curInst.reg1, data);
            break;
        case AM_R_N16:
            writeReg(m_curInst.reg1, data);
            break;
        case AM_R_R:
            writeReg(m_curInst.reg1, data);
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