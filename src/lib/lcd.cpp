#include "lcd.hpp"

Lcd::Lcd(Emu* emu) {
    m_emu = emu;
}

bool Lcd::isEnabled() {
    return (m_regs.lcdc & (1 << 7));
}

u8 Lcd::windowsTileMapMode() {
    return (m_regs.lcdc & (1 << 6)) >> 6;
}

bool Lcd::isWindowEnabled() {
    return (m_regs.lcdc & (1 << 5));
}

u8 Lcd::tileDataMode() {
    return (m_regs.lcdc & (1 << 4)) >> 4;
}

u8 Lcd::backgroundTileMapMode() {
    return (m_regs.lcdc & (1 << 3)) >> 3;
}

u8 Lcd::getObjectSize() {
    if(m_regs.lcdc & (1 << 2)) {
        return 16;
    } else {
        return 8;
    }
}

bool Lcd::isObjectEnabled() {
    return (m_regs.lcdc & (1 << 1));
}

bool Lcd::isBGWindowEnabled() {
    return (m_regs.lcdc & (1 << 0));
}

u8 Lcd::read(u16 address) {
    switch (address) {
        case 0x0:
            return m_regs.lcdc; 
        case 0x1:
            return m_regs.stat;
        case 0x2:
            return m_regs.scy;
        case 0x3:
            return m_regs.scx;
        case 0x4:
            return m_regs.ly;
        case 0x5:
            return m_regs.lyc;
        case 0x7:
            return m_regs.bgp;
        case 0x8:
            return m_regs.obp0;
        case 0x9:
            return m_regs.obp1;
        case 0xA:
            return m_regs.wy;
        case 0xB:
            return m_regs.wx;
        default:
            std::cout << "WARNING: LCD read address 0x" << std::hex <<
            (int)address + 0xFF40 << " not supported!" << std::endl;
            return 0;
    }
}

void Lcd::write(u16 address, u8 value) {
    switch (address) {
        case 0x0:
            m_regs.lcdc = value; 
        case 0x1:
            m_regs.stat = value;
        case 0x2:
            m_regs.scy = value;
        case 0x3:
            m_regs.scx = value;
        case 0x4:
            m_regs.ly = value;
        case 0x5:
            m_regs.lyc = value;
        case 0x7:
            m_regs.bgp = value;
        case 0x8:
            m_regs.obp0 = value;
        case 0x9:
            m_regs.obp1 = value;
        case 0xA:
            m_regs.wy = value;
        case 0xB:
            m_regs.wx = value;
        default:
            std::cout << "WARNING: LCD write address 0x" << std::hex <<
            (int)address + 0xFF40 << " not supported!" << std::endl;
    }
}

