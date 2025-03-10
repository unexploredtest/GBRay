#include "emu.hpp"

Emu::Emu() {
    m_cart = std::make_unique<Cart>(this);
    m_bus = std::make_unique<Bus>(this);
    m_cpu = std::make_unique<Cpu>(this);
    m_ram = std::make_unique<Ram>(this);
    m_io = std::make_unique<IO>(this);
    m_timer = std::make_unique<Timer>(this);
}

void Emu::run(std::string filePath) {
    m_cart->loadROM(filePath);
    m_cart->printROMInfo();
    std::thread cpuThread = std::thread(&Emu::runCpu, this);
    // runCpu();
    
    while(!m_die) {
        continue;
    }
}

void Emu::runCpu() {
    m_cpu->init();

    m_running = true;
    m_paused = false;
    // m_ticks = 0;
    while(m_running) {
        std::cout << "Step number: " << std::hex << (int)m_ticks << ":" << std::endl;
        if(m_paused) {
            continue;
        }

        m_cpu->step();
    }
}

std::unique_ptr<Cart>& Emu::getCart() {
    return m_cart;
}

std::unique_ptr<Bus>& Emu::getBus() {
    return m_bus;
}

std::unique_ptr<Ram>& Emu::getRam() {
    return m_ram;
}

std::unique_ptr<Cpu>& Emu::getCpu() {
    return m_cpu;
}

std::unique_ptr<IO>& Emu::getIO() {
    return m_io;
}

std::unique_ptr<Timer>& Emu::getTimer() {
    return m_timer;
}