#include "ram.hpp"


Ram::Ram(Emu* emu) {
    m_emu = emu;
}

u8 Ram::readWRam(u16 address) {
    if(address < WRAM_SIZE) {
        return m_wRam[address];
    } else {
        throw std::runtime_error("ERROR: Address out of bounds!");
    }
}

void Ram::writeWRam(u16 address, u8 data) {
    if(address < WRAM_SIZE) {
        m_wRam[address] = data;
    } else {
        throw std::runtime_error("ERROR: Address out of bounds!");
    }
}

u8 Ram::readHRam(u16 address) {
    if(address < HRAM_SIZE) {
        return m_wRam[address];
    } else {
        throw std::runtime_error("ERROR: Address out of bounds!");
    }
}
void Ram::writeHRam(u16 address, u8 data) {
    if(address < HRAM_SIZE) {
        m_wRam[address] = data;
    } else {
        throw std::runtime_error("ERROR: Address out of bounds!");
    }
}