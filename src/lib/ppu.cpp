#include <chrono>
#include <thread>
#include <algorithm>

#include "ppu.hpp"


Ppu::Ppu(Emu* emu) {
    m_emu = emu;
}

// Sprite::Sprite(u8 data[4]) {
//     yPos = data[0];
//     xPos = data[1];
//     index = data[2];

//     attributes = data[3];
//     // hasPriority = (attributes & (1 << 7)) >> 7;
//     // yFlip = (attributes & (1 << 6)) >> 6; 
//     // xFlip = (attributes & (1 << 5)) >> 5; 
//     // dmgPalette = (attributes & (1 << 4)) >> 4; 
// }

bool Sprite::hasPriority() {
    return (attributes & (1 << 7)) >> 7;
}

bool Sprite::yFlip() {
    return (attributes & (1 << 6)) >> 6;
}

bool Sprite::xFlip() {
    return (attributes & (1 << 5)) >> 5;
}

u8 Sprite::dmgPalette() {
    return (attributes & (1 << 4)) >> 4;
}

bool Sprite::operator<(const Sprite& other) const {
    // You might ask why it's >= and not >, to which I say "I don't know!"
    return xPos >= other.xPos;
}

SpriteBuffer::SpriteBuffer() {
    m_size = 0;
}

void SpriteBuffer::add(Sprite sprite) {
    if(m_size < BUFFER_SIZE) {
        m_buffer[m_size] = sprite;
        m_size++;
    }
}

void SpriteBuffer::sort() {
    std::stable_sort(m_buffer.begin(), m_buffer.begin() + m_size);
}

u8 SpriteBuffer::getSize() {
    return m_size;
}

Sprite SpriteBuffer::getLast() {
    return m_buffer[m_size - 1];
}

void SpriteBuffer::removeLast() {
    m_size--;
}

std::array<Sprite, SpriteBuffer::BUFFER_SIZE>& SpriteBuffer::getArray() {
    return m_buffer;
}

void Ppu::init() {
    m_currentLine = 0;
    m_currentTick = 0;
    m_currentMode = PM_OAM;
    m_lockFrameRate = true;
    m_lastFrameTime = std::chrono::system_clock::now();
    m_winLine = 0;
}

u8 Ppu::readVRam(u16 address) {
    return m_vRam[address];
}

void Ppu::writeVRam(u16 address, u8 value) {
    m_vRam[address] = value;
}

u8 Ppu::readOAM(u16 address) {
    return m_oam[address];
}

void Ppu::writeOAM(u16 address, u8 value) {
    m_oam[address] = value;
}

void Ppu::incrementWinLine() {
    u8 wy = m_emu->getLcd()->getRegs().wy;
    u8 ly = m_emu->getLcd()->getLy();

    if(ly >= wy && ly < wy + HEIGHT_SIZE && isWindowEnabled()) {
        m_winLine++;
    }
}

void Ppu::runHBlank() {
    if(m_currentTick >= LINE_TCIKS) {
        m_emu->getLcd()->incrementLy();
        incrementWinLine();
        
        m_currentTick = 0;

        if(m_emu->getLcd()->getLy() >= PPU_LINES) {
            m_currentMode = PM_VBLANK;
            m_emu->getCpu()->requestInterrupt(IT_VBLANK);
            m_emu->getLcd()->sendInterrupt(SI_MD1);
        } else {
            m_currentMode = PM_OAM;
            m_emu->getLcd()->sendInterrupt(SI_MD2);
        }
    }
}

void Ppu::runVBlank() {
    if(m_currentTick >= LINE_TCIKS) {
        m_currentTick = 0;
        m_emu->getLcd()->incrementLy();

        if(m_emu->getLcd()->getLy() == 0) {
            m_currentMode = PM_OAM;
            m_winLine = 0;
            m_emu->getLcd()->sendInterrupt(SI_MD2);
            checkFrameTime();
        }
    }
}

void Ppu::runOAM() {
    if(m_currentTick == 1) {
        m_spriteBuffer = SpriteBuffer{};
        Sprite* spriteArray = (Sprite*)m_oam;
        u8 ly = m_emu->getLcd()->getLy();
        for(int i = 0; i < 40; i++) {
            u8 tileSize = m_emu->getLcd()->getObjectSize();
            if(spriteArray[i].xPos > 0 && spriteArray[i].yPos <= ly + 16 &&
                spriteArray[i].yPos + tileSize > ly + 16) {
                m_spriteBuffer.add(spriteArray[i]);
            }
        }

        m_spriteBuffer.sort();
    }

    if(m_currentTick >= OAM_TICKS) {
        m_currentMode = PM_DRAW;
        m_BGFetchData = BGFetchData{};
        m_BGFetchData.xPos = 0;
        m_BGFetchData.xPushPos = 0;
        m_WDFetchData = WDFetchData{};
    }
}

void Ppu::runDRAW() {
    runPipeline();

    // if(m_currentTick > 172 + OAM_TICKS) {
    if(m_BGFetchData.xPushPos >= 160) {
        m_BGFetchData.fifo.reset();
        m_currentMode = PM_HBLANK;
        m_emu->getLcd()->sendInterrupt(SI_MD0);
    }
}

static int lol = 0;

void Ppu::tick() {
    m_currentTick++;
    if(m_currentMode == PM_OAM) {
        runOAM();
    } else if(m_currentMode == PM_DRAW) {
        runDRAW();
    } else if(m_currentMode == PM_HBLANK) {
        runHBlank();
    } else if(m_currentMode == PM_VBLANK) {
        runVBlank();
    }
    m_emu->getLcd()->changePPUMode(m_currentMode);
}

void Ppu::checkFrameTime() {
    const auto currentTime = std::chrono::system_clock::now();
    const u32 amplifiedTime = FRAME_TIME / m_renderSpeed;
    const auto frameTime = std::chrono::microseconds(amplifiedTime);

    if(m_lockFrameRate && currentTime - m_lastFrameTime < frameTime) {
        std::this_thread::sleep_for(frameTime - (currentTime - m_lastFrameTime));
    }

    auto newLastFrameTime = std::chrono::system_clock::now();
    auto timeDifference = newLastFrameTime - m_lastFrameTime;
    m_speedRatio = (float)(FRAME_TIME * 1000) / timeDifference.count();

    m_lastFrameTime = newLastFrameTime;
}

u8* Ppu::getVideo() {
    return m_video;
}

bool Ppu::isFrameLocked() {
    return m_lockFrameRate;
}

void Ppu::toggleFrameLock() {
    m_lockFrameRate = !m_lockFrameRate;
}

void Ppu::changeFrameSpeed(float speed) {
    m_renderSpeed = speed;
}

float Ppu::getSpeedRatio() {
    return m_speedRatio;
}
