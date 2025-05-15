#include "emu.hpp"

Emu::Emu() {
    m_cart = Cart(this);
    m_bus = Bus(this);
    m_cpu = Cpu(this);
    m_ppu = Ppu(this);
    m_ram = Ram(this);
    m_io = IO(this);
    m_timer = Timer(this);
    m_ui = UI(this);
    m_dma = Dma(this);
    m_lcd = Lcd(this);
    m_gamepad = Gamepad(this);
}

void Emu::run(std::string filePath) {
    m_cart.loadROM(filePath);
    m_cart.printROMInfo();

    m_ppu.init();
    m_lcd.init();

    std::thread cpuThread = std::thread(&Emu::runCpu, this);

    m_ui.init(320, 240);
    m_ui.run();
    m_ui.deinit();

    m_running = false;
    
    cpuThread.join();
}

void Emu::runCpu() {
    m_cpu.init();

    m_running = true;
    // m_ticks = 0;
    while(m_running) {
        if(m_ui.isPaused()) {
            continue;
        }

        m_cpu.step();
        // m_ticks++;
    }
}

Cart& Emu::getCart() {
    return m_cart;
}

Bus& Emu::getBus() {
    return m_bus;
}

Ram& Emu::getRam() {
    return m_ram;
}

Cpu& Emu::getCpu() {
    return m_cpu;
}

Ppu& Emu::getPpu() {
    return m_ppu;
}

IO& Emu::getIO() {
    return m_io;
}

Timer& Emu::getTimer() {
    return m_timer;
}

UI& Emu::getUI() {
    return m_ui;
}

Dma& Emu::getDma() {
    return m_dma;
}

Lcd& Emu::getLcd() {
    return m_lcd;
}

Gamepad& Emu::getGamepad() {
    return m_gamepad;
}