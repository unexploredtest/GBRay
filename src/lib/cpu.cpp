#include "cpu.hpp"

Cpu::Cpu(Emu* emu) {
    m_emu = emu;
}
void Cpu::init() {
    m_regs = {0};
    m_regs.PC = 0x100;
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
            return 1 ? m_regs.C & 0x10 : 0;
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