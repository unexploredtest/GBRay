#include "ppu.hpp"

void Ppu::BGFetch() {
    if(m_BGFetchData.currentFetchMode != FM_PUSH && !m_BGFetchData.shouldFetch) {
        m_BGFetchData.shouldFetch = true;
        return;
    }

    switch(m_BGFetchData.currentFetchMode) {
        case FM_TILE: {
            if(m_emu->getLcd()->isBGWindowEnabled()) {
                u8 scx = m_emu->getLcd()->getRegs().scx;
                u8 scy = m_emu->getLcd()->getRegs().scy;
                u8 ly = m_emu->getLcd()->getRegs().ly;

                u16 offset;
                if(m_emu->getLcd()->backgroundTileMapMode() == 1) {
                    offset = SECOND_MAP_OFFSET;
                } else {
                    offset = FIRST_MAP_OFFSET;
                }
                u8 index = m_emu->getBus()->read(offset + (((scx + m_BGFetchData.xPos) / 8) & 0x1F) + 32 * (((ly + scy) & 0xFF) / 8));
                m_BGFetchData.tileIndex = index;
            } else {
                m_BGFetchData.tileIndex = 0;
            }
            m_BGFetchData.xPos += 8;
            m_BGFetchData.currentFetchMode = FM_LOWDATA;
            break;
        }

        case FM_LOWDATA: {
            u8 scy = m_emu->getLcd()->getRegs().scy;
            u8 ly = m_emu->getLcd()->getRegs().ly;
            u8 lowByte;
            if(m_emu->getLcd()->tileDataMode() == 1) {
                lowByte = m_emu->getBus()->read(FIRST_TILE_OFFSET + m_BGFetchData.tileIndex * 16 + 2 * ((ly + scy) % 8));
            } else {
                if(m_BGFetchData.tileIndex <= 127) {
                    lowByte = m_emu->getBus()->read(THIRD_TILE_OFFSET + m_BGFetchData.tileIndex * 16 + 2 * ((ly + scy) % 8));
                } else {
                    lowByte = m_emu->getBus()->read(SECOND_TILE_OFFSET + (m_BGFetchData.tileIndex - 128) * 16 + 2 * ((ly + scy) % 8));
                }
            }
            m_BGFetchData.tileLow = lowByte;
            m_BGFetchData.currentFetchMode = FM_HIGHDATA;
            break;
        }
            
        case FM_HIGHDATA: {
            u8 scy = m_emu->getLcd()->getRegs().scy;
            u8 ly = m_emu->getLcd()->getRegs().ly;
            u8 highByte;
            if(m_emu->getLcd()->tileDataMode() == 1) {
                highByte = m_emu->getBus()->read(FIRST_TILE_OFFSET + 1 + m_BGFetchData.tileIndex * 16 + 2 * ((ly + scy) % 8));
            } else {
                if(m_BGFetchData.tileIndex <= 127) {
                    highByte = m_emu->getBus()->read(THIRD_TILE_OFFSET + 1 + m_BGFetchData.tileIndex * 16 + 2 * ((ly + scy) % 8));
                } else {
                    highByte = m_emu->getBus()->read(SECOND_TILE_OFFSET + 1 + (m_BGFetchData.tileIndex - 128) * 16 + 2 * ((ly + scy) % 8));
                }
            }
            m_BGFetchData.tileHigh = highByte;
            m_BGFetchData.currentFetchMode = FM_SLEEP;
            break;
        }
        case FM_SLEEP:
            m_BGFetchData.currentFetchMode = FM_PUSH;
            break;
        case FM_PUSH: {
            if(BGPush()) {
                m_BGFetchData.currentFetchMode = FM_TILE;
            } 
            break;
        }
            
    }

    m_BGFetchData.shouldFetch = false;
}

Pixel Ppu::checkSprite(Pixel pixel, u8 pixelIndex) {
    u8 ly = m_emu->getLcd()->getRegs().ly;
    Pixel backPixel = pixel;
    u8 currentX = (m_BGFetchData.xPos) - (pixelIndex + 1);

    for(int i = 0; i < m_spriteBuffer.getSize(); i++) {
        auto sprite = m_spriteBuffer.getArray()[i];
        u8 spriteX = sprite.xPos - 8;
        if(!(spriteX <= currentX && currentX < spriteX + 8)) {
            continue;
        }

        if(sprite.hasPriority() && backPixel.colorIndex != 0) {
            continue;
        }

        u8 xOffset = 7 - (currentX - spriteX);

        if(sprite.xFlip()) {
            xOffset = 7 - xOffset;
        }

        u8 yOffset = ly - (sprite.yPos - 16);

        if(sprite.yFlip()) {
            if(m_emu->getLcd()->getObjectSize() == 8) {
                yOffset = 7 - yOffset;
            } else {
                yOffset = 15 - yOffset;
            }
        }

        // if(m_emu->getLcd()->getObjectSize() == 16) {
        //     multiply = 32;
        // }
        u8 index = sprite.index;
        if(m_emu->getLcd()->getObjectSize() == 16) {
            index = index - (index & 0b1);
        }

        u8 lowByte = m_emu->getBus()->read(FIRST_TILE_OFFSET + index * 16 + 2 * yOffset);
        u8 highByte = m_emu->getBus()->read(FIRST_TILE_OFFSET + 1 + index * 16 + 2 * yOffset);

        u8 lowBit = (lowByte & (1 << xOffset)) >> xOffset;
        u8 highBit = (highByte & (1 << xOffset)) >> xOffset;
        int colorIndex = (highBit << 1) | lowBit;
        
        if(colorIndex == 0) {
            continue;
        }

        pixel.colorIndex = m_emu->getLcd()->getObjColorPallete(sprite.dmgPalette(), colorIndex);
    }

    return pixel;
}

bool Ppu::BGPush() {
    if(m_BGFetchData.fifo.getSize() > 8) {
        return false;
    }

    u8 lowByte = m_BGFetchData.tileLow;
    u8 highByte = m_BGFetchData.tileHigh;

    for(int pixelIndex = 7; pixelIndex >= 0; pixelIndex--) {
        Pixel pixel;
        u8 lowBit = (lowByte & (1 << pixelIndex)) >> pixelIndex;
        u8 highBit = (highByte & (1 << pixelIndex)) >> pixelIndex;
        
        int colorIndex = (highBit << 1) | lowBit;
        colorIndex =  m_emu->getLcd()->getBckColorPallete(colorIndex);
        pixel.colorIndex = colorIndex;

        if(!m_emu->getLcd()->isBGWindowEnabled()) {
            pixel.colorIndex = 0;
        }

        if(m_emu->getLcd()->isObjectEnabled()) {
            pixel = checkSprite(pixel, pixelIndex);
        }
        
        m_BGFetchData.fifo.push(pixel);
    }

    return true;
}

void Ppu::BGDraw() {
    
    if(m_BGFetchData.fifo.getSize() > 8) {
        u8 scy = m_emu->getLcd()->getRegs().scy;
        u8 ly = m_emu->getLcd()->getRegs().ly;
        Pixel pixel = m_BGFetchData.fifo.pop();
        m_video[m_BGFetchData.xPushPos + (ly)*WIDTH_SIZE] = pixel.colorIndex;
        m_BGFetchData.xPushPos++;
    }
}

void Ppu::runPipeline() {
    BGFetch();
    BGDraw();
}