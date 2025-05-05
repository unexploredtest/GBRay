#include "ppu.hpp"


Fifo::Fifo() {
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

void Fifo::push(Pixel data) {
    FNode* newNode = new FNode{nullptr, data};

    if(m_size == 0) {
        m_head = newNode;
        m_tail = newNode;
    } else {
        m_tail->nextNode = newNode;
        m_tail = newNode;
    }

    m_size++;
}

Pixel Fifo::pop() {
    if(m_size == 0) {
        throw std::runtime_error("ERROR: Can't pop an empty Fifo!");
        return {0}; // Shouldn't happen
    } else {
        FNode* curNode = m_head;
        Pixel data = curNode->data;
        m_head = m_head->nextNode;
        
        m_size--;
        delete curNode;

        return data;
    }
}

void Fifo::reset() {
    while(m_size) {
        pop();
    }
}

u16 Fifo::getSize() {
    return m_size;
}
