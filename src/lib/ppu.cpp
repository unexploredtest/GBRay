#include "ppu.hpp"


Ppu::Ppu(Emu* emu) {
    m_emu = emu;
}

u8 Ppu::readVRam(u16 address) {
    return m_vRam[address];
}

void Ppu::writeVRam(u16 address, u8 value) {
    std::cout << address << std::endl;
    m_vRam[address] = value;
}

u8 Ppu::readOAM(u16 address) {
    return m_oam[address];
}

void Ppu::writeOAM(u16 address, u8 value) {
    m_oam[address] = value;
}

// void Ppu::incrementLine() {

// }

void Ppu::tick() {
    m_currentTick++;
    if(m_currentMode == PM_OAM) {

        if(m_currentTick > 80) {
            m_currentMode = PM_DRAW;
        }
    } else if(m_currentMode == PM_DRAW) {

        if(m_currentTick > 172 + 80) {
            m_currentMode = PM_HBLANK;
            m_emu->getLcd()->sendInterrupt(SI_MD0);
        }
    } else if(m_currentMode == PM_HBLANK) {

        if(m_currentTick > 456) {
            m_emu->getLcd()->incrementLy();
            m_currentTick = 0;

            if(m_currentLine > 143) {
                m_currentMode = PM_VBLANK;
                m_emu->getCpu()->requestInterrupt(IT_VBLANK);
                m_emu->getLcd()->sendInterrupt(SI_MD1);
            } else {
                m_currentMode = PM_OAM;
                m_emu->getLcd()->sendInterrupt(SI_MD2);
            }
        }
    } else if(m_currentMode == PM_VBLANK) {
        m_emu->getLcd()->incrementLy();

        if(m_currentTick > 456) {
            m_currentTick = 0;

            if(m_emu->getLcd()->getLy() == 0) {
                m_currentMode = PM_OAM;
                m_emu->getLcd()->sendInterrupt(SI_MD2);
            }
        }
    }
}
