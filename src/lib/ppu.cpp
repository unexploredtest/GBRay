#include "ppu.hpp"


Ppu::Ppu(Emu* emu) {
    m_emu = emu;
}

u8 Ppu::readVRam(u16 address) {
    return m_vRam[address];
}

void Ppu::writeVRam(u16 address, u8 value) {
    m_vRam[address] = value;
}

