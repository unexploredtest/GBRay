#include "emu.hpp"

Emu::Emu() {
    m_cart = std::make_unique<Cart>(this);
}

void Emu::run(std::string filePath) {
    m_cart->loadROM(filePath);
    m_cart->printROMInfo();
    // romFile.
}