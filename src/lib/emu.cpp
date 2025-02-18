#include "emu.hpp"

Emu::Emu() {
    m_cart = std::shared_ptr<Cart>(new Cart(this));
}

void Emu::run(std::string filePath) {
    m_cart->loadROM(filePath);
    m_cart->printROMInfo();
    // romFile.
}