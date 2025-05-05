#include "emu.hpp"

Emu::Emu() {
    m_cart = std::make_unique<Cart>(this);
    m_bus = std::make_unique<Bus>(this);
    m_cpu = std::make_unique<Cpu>(this);
    m_ppu = std::make_unique<Ppu>(this);
    m_ram = std::make_unique<Ram>(this);
    m_io = std::make_unique<IO>(this);
    m_timer = std::make_unique<Timer>(this);
    m_ui = std::make_unique<UI>(this);
    m_dma = std::make_unique<Dma>(this);
    m_lcd = std::make_unique<Lcd>(this);
}

void Emu::run(std::string filePath) {
    m_cart->loadROM(filePath);
    m_cart->printROMInfo();

    m_ppu->init();
    m_lcd->init();

    std::thread cpuThread = std::thread(&Emu::runCpu, this);

    m_ui->init(320, 240);
    m_ui->run();
    m_ui->deinit();

    m_running = false;
    
    cpuThread.join();
}

void Emu::runCpu() {
    m_cpu->init();

    m_running = true;
    // m_ticks = 0;
    while(m_running) {
        if(m_ui->isPaused()) {
            continue;
        }

        m_cpu->step();
        // m_ticks++;
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

std::unique_ptr<Ppu>& Emu::getPpu() {
    return m_ppu;
}

std::unique_ptr<IO>& Emu::getIO() {
    return m_io;
}

std::unique_ptr<Timer>& Emu::getTimer() {
    return m_timer;
}

std::unique_ptr<UI>& Emu::getUI() {
    return m_ui;
}

std::unique_ptr<Dma>& Emu::getDma() {
    return m_dma;
}

std::unique_ptr<Lcd>& Emu::getLcd() {
    return m_lcd;
}