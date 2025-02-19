#include "bus.hpp"

Bus::Bus(Emu* emu) {
    m_emu = emu;
}

u8 Bus::read(u16 address) {
    if(address < 0x8000) {
        return m_emu->getCart()->read(address);
    }
}

void Bus::write(u16 address, u8 value) {
    if(address < 0x8000) {
        return m_emu->getCart()->write(address, value);
    }
}