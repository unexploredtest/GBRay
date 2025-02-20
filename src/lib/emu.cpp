#include "emu.hpp"

Emu::Emu() {
    m_cart = std::make_unique<Cart>(this);
    m_bus = std::make_unique<Bus>(this);
    m_cpu = std::make_unique<Cpu>(this);
}

void Emu::run(std::string filePath) {
    m_cart->loadROM(filePath);
    m_cart->printROMInfo();
    m_cpu->init();
}

std::unique_ptr<Cart>& Emu::getCart() {
    return m_cart;
}