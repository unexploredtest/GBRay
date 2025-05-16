#include "ppu.hpp"


Fifo::Fifo() {
    m_headIndex = 0;
    m_tailIndex = 0;
    m_size = 0;
}

void Fifo::push(Pixel data) {
    if(m_size == 0) {
        m_headIndex = 0;
        m_tailIndex = 0;
        m_buffer[0] = data;
    } else {
        m_tailIndex++;
        if(m_tailIndex >= BUFFER_SIZE) {
            m_tailIndex = 0;
        }
        m_buffer[m_tailIndex] = data;
    }

    m_size++;
}

Pixel Fifo::pop() {
    if(m_size == 0) {
        throw std::runtime_error("ERROR: Can't pop an empty Fifo!");
        return {0}; // Shouldn't happen
    } else {
        Pixel data = m_buffer[m_headIndex];
        m_headIndex++;
        if(m_headIndex >= BUFFER_SIZE) {
            m_headIndex = 0;
        }
        m_size--;

        return data;
    }
}

void Fifo::reset() {
    m_headIndex = 0;
    m_tailIndex = 0;
    m_size = 0;
}

u16 Fifo::getSize() {
    return m_size;
}
