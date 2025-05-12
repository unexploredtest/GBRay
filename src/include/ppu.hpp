#pragma once

#include "common.hpp"
#include "emu.hpp"


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
        FNode* m_head;
        FNode* m_tail;
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
};


class Ppu {
    public:
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
        u8* getVideo();

    private:
        Emu* m_emu;
        static const u16 VRAM_SIZE = 0x2000;
        static const u16 OAM_SIZE = 0xA0;
        u8 m_vRam[VRAM_SIZE];
        u8 m_oam[OAM_SIZE];
        u8 m_video[WIDTH_SIZE*HEIGHT_SIZE];
        u16 m_currentLine;
        u16 m_currentTick;
        PpuMode m_currentMode;

        bool m_lockFrameRate;
        std::chrono::time_point<std::chrono::system_clock> m_lastFrameTime;

        BGFetchData m_BGFetchData;

        // bool m_shouldFetch = false;
        // FetchMode m_currentFetchMode;

        // Pipeline methods
        void BGFetch();
        void BGDraw();
        bool BGPush();

};