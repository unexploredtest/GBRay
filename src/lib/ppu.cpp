#include <chrono>
#include <thread>

#include "ppu.hpp"


Ppu::Ppu(Emu* emu) {
    m_emu = emu;
}

void Ppu::init() {
    m_currentLine = 0;
    m_currentTick = 0;
    m_currentMode = PM_OAM;
    m_lockFrameRate = true;
    m_lastFrameTime = std::chrono::system_clock::now();
}

u8 Ppu::readVRam(u16 address) {
    return m_vRam[address];
}

void Ppu::writeVRam(u16 address, u8 value) {
    // std::cout << address << std::endl;
    m_vRam[address] = value;
}

u8 Ppu::readOAM(u16 address) {
    return m_oam[address];
}

void Ppu::writeOAM(u16 address, u8 value) {
    m_oam[address] = value;
}

void Ppu::runHBlank() {
    if(m_currentTick >= LINE_TCIKS) {
        m_emu->getLcd()->incrementLy();
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
            m_emu->getLcd()->sendInterrupt(SI_MD2);
            checkFrameTime();
        }
    }
}

void Ppu::runOAM() {
    if(m_currentTick >= OAM_TICKS) {
        m_currentMode = PM_DRAW;
        m_BGFetchData = BGFetchData{};
        m_BGFetchData.xPos = 0;
        m_BGFetchData.xPushPos = 0;
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
    const auto frameTime = std::chrono::microseconds(FRAME_TIME);

    if(m_lockFrameRate && currentTime - m_lastFrameTime < frameTime) {
        std::this_thread::sleep_for(frameTime - (currentTime - m_lastFrameTime));
    }

    m_lastFrameTime = std::chrono::system_clock::now();
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