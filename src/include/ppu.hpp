#pragma once

#include <chrono>
#include <array>

#include "common.hpp"


static const u16 FIRST_TILE_OFFSET = 0x8000;
static const u16 SECOND_TILE_OFFSET = 0x8800;
static const u16 THIRD_TILE_OFFSET = 0x9000;

static const u16 FIRST_MAP_OFFSET = 0x9800;
static const u16 SECOND_MAP_OFFSET = 0x9C00;


static const u8 WIDTH_SIZE = 160;
static const u8 HEIGHT_SIZE = 144;

static const u8 OAM_TICKS = 80;
static const u16 LINE_TCIKS = 456;
static const u8 PPU_LINES = 144;

// In microseconds
static const u32 FRAME_TIME = 16740;

static constexpr Color COLORS[] = {
    Color{0x9B, 0xBC, 0x0F, 0xFF},
    Color{0x8b, 0xac, 0x0f, 0xFF},
    Color{0x30, 0x62, 0x30, 0xFF},
    Color{0x0f, 0x38, 0x0f, 0xFF}
};

enum PpuMode {
    PM_HBLANK,
    PM_VBLANK,
    PM_OAM,
    PM_DRAW
};

enum FetchMode {
    FM_TILE,
    FM_LOWDATA,
    FM_HIGHDATA,
    FM_SLEEP,
    FM_PUSH
};

struct Pixel {
    u8 colorIndex;
    u8 palette;
    u8 sprPrio; 
    u8 backPrio; 
};

struct FNode {
    FNode* nextNode;
    Pixel data;
};

class Fifo {
    public:
        Fifo();
        void push(Pixel data);
        Pixel pop();
        void reset();
        u16 getSize();

    private:
        // FNode* m_head;
        // FNode* m_tail;
        static const u8 BUFFER_SIZE = 32;
        std::array<Pixel, BUFFER_SIZE> m_buffer;
        u8 m_headIndex;
        u8 m_tailIndex;
        u16 m_size;

};

struct BGFetchData {
    FetchMode currentFetchMode;
    Fifo fifo;
    bool shouldFetch = false;
    u8 xPos;
    u8 xPushPos;
    u8 tileIndex;
    u8 tileLow;
    u8 tileHigh;
    u8 lineX;
};

struct WDFetchData {
    u8 xPos;
    u8 tileIndex;
    u8 tileLow;
    u8 tileHigh;
};

struct Sprite {
    u8 yPos;
    u8 xPos;
    u8 index;
    u8 attributes;

    bool hasPriority();
    bool yFlip();
    bool xFlip();
    u8 dmgPalette();

    bool operator<(const Sprite& other) const;
};

class SpriteBuffer {
    private:
        static const u8 BUFFER_SIZE = 10;
        std::array<Sprite, BUFFER_SIZE> m_buffer;
        u8 m_size;      

    public:
        SpriteBuffer();
        void add(Sprite sprite);
        Sprite getLast();
        void removeLast();
        void sort();
        u8 getSize();
        std::array<Sprite, BUFFER_SIZE>& getArray();
};


class Ppu {
    public:
        Ppu() = default;
        Ppu(Emu* emu);
        void init();
        void tick();
        u8 readVRam(u16 address);
        void writeVRam(u16 address, u8 value);
        u8 readOAM(u16 address);
        void writeOAM(u16 address, u8 value);
        void runHBlank();
        void runVBlank();
        void runOAM();
        void runDRAW();
        void runPipeline();
        void checkFrameTime();
        bool isFrameLocked();
        void toggleFrameLock();
        void changeFrameSpeed(float speed);
        float getSpeedRatio();

        static const u32 VIDEO_SIZE = WIDTH_SIZE*HEIGHT_SIZE;
        std::array<u8, VIDEO_SIZE>& getVideo();

    private:
        Emu* m_emu;
        static const u16 VRAM_SIZE = 0x2000;
        static const u16 OAM_SIZE = 0xA0;
        
        std::array<u8, VRAM_SIZE> m_vRam;
        std::array<u8, OAM_SIZE> m_oam;
        std::array<u8, VIDEO_SIZE> m_video;
        u16 m_currentLine;
        u16 m_currentTick;
        PpuMode m_currentMode;

        float m_renderSpeed = 1.0f;
        bool m_lockFrameRate;
        float m_speedRatio;
        std::chrono::time_point<std::chrono::system_clock> m_lastFrameTime;

        BGFetchData m_BGFetchData;
        WDFetchData m_WDFetchData;


        // bool m_shouldFetch = false;
        // FetchMode m_currentFetchMode;

        SpriteBuffer m_spriteBuffer;
        u8 m_winLine;
        void incrementWinLine();
        bool isWindowEnabled();
        // Pipeline methods
        void BGFetch();
        void WDFetch();
        void BGDraw();
        bool BGPush();
        Pixel checkSprite(Pixel pixel, u8 pixelIndex);
};