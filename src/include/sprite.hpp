#pragma once

#include <array>

#include "common.hpp"

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
