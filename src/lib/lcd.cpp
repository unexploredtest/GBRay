#include "lcd.hpp"

Lcd::Lcd(Emu* emu) {
    m_emu = emu;
}

void Lcd::init() {
    m_regs = {0};
    m_regs.lcdc = 0x91;
    m_regs.bgp = 0xFC;
    m_regs.obp0 = 0xFF;
    m_regs.obp1 = 0xFF;
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

void Lcd::sendInterrupt(StatInt interrupt) {
    if(m_regs.stat & interrupt) {
        m_emu->getCpu()->requestInterrupt(IT_LCD_STAT);
    }
}

void Lcd::checkLCY() {
    if(m_regs.ly == m_regs.lyc) {
        m_regs.stat = m_regs.stat | 0b100; 
        sendInterrupt(SI_LY);
    } else {
        m_regs.stat = m_regs.stat & 0b1111011;
    }
}

u8 Lcd::getLy() {
    return m_regs.ly;
}

void Lcd::incrementLy() {
    m_regs.ly++;
    checkLCY();
    if(m_regs.ly >= MAX_LINES) {
        m_regs.ly = 0;
    }
    
}

u8 Lcd::getBckColorPallete(u8 index) {
    // TODO: Handle none 0/1 obj numbers I suppose
    return (m_regs.bgp & (0b11 << (index * 2))) >> (index * 2);
}

u8 Lcd::getObjColorPallete(u8 objNumber, u8 index) {
    // TODO: Handle none 0/1 obj numbers I suppose
    u8 objPalette;
    if(objNumber == 0) {
        objPalette = m_regs.obp0;
    } else {
        objPalette = m_regs.obp1;
    }

    return (objPalette & (0b11 << (index * 2))) >> (index * 2);
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
            break;
        case 0x1:
            m_regs.stat = (m_regs.stat & 0b111) | (value & 0b1111000);
            break;
        case 0x2:
            m_regs.scy = value;
            break;
        case 0x3:
            m_regs.scx = value;
            break;
        case 0x4:
            break;
        case 0x5:
            m_regs.lyc = value;
            break;
        case 0x7:
            m_regs.bgp = value;
            break;
        case 0x8:
            m_regs.obp0 = value & 0b11111100;
            break;
        case 0x9:
            m_regs.obp1 = value & 0b11111100;
            break;
        case 0xA:
            m_regs.wy = value;
            break;
        case 0xB:
            m_regs.wx = value;
            break;
        default:
            std::cout << "WARNING: LCD write address 0x" << std::hex <<
            (int)address + 0xFF40 << " not supported!" << std::endl;
    }
}

void Lcd::changePPUMode(u8 mode) {
    m_regs.stat &= 0b11111100;
    m_regs.stat |= (mode & 0b11);
}

LcdRegs Lcd::getRegs() {
    return m_regs;
}
