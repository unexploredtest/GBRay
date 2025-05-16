#include <algorithm>

#include "ppu.hpp"


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