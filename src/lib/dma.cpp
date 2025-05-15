#include "dma.hpp"
#include "emu.hpp"

Dma::Dma(Emu* emu) {
    m_emu = emu;
    m_isTrans = false;
}

void Dma::start(u8 highByte) {
    if(m_isTrans) {
        return;
    } 

    m_isTrans = true;
    m_curHighByte = highByte;
    m_curTick = 0;
}

void Dma::tick() {
    if(!m_isTrans) {
        return;
    } 

    const u16 baseSrc = m_curHighByte * 0x100;
    const u16 baseDst = 0xFE00;
    if(m_curTick >= 160) {
        for(int lowerAdr = 0; lowerAdr < 0xA0; lowerAdr++) {
            u8 value = m_emu->getBus().read(baseSrc + lowerAdr);
            m_emu->getBus().write(baseDst + lowerAdr, value);
        }
    
        m_isTrans = false;
    } else {
        m_curTick++;
    }
}

bool Dma::isTransferring() {
    return m_isTrans;
}
