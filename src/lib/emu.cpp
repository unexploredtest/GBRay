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
    m_paused = false;
    m_ticks = 0;
    while(m_running) {
        std::cout << "Step number: " << std::hex << (int)m_ticks << ":" << std::endl;
        if(m_paused) {
            continue;
        }

        m_cpu->step();
        // 0x2d000 - 0x2f000 (inst)
        // 0x2d8aa - 0x2d8ab (A) - address DD02
        // 2d710 - -0x2d804 - Stack Pointer
        // 0xc65b - address DD01
        // if(m_ticks == 0x403d) {
        //     std::cin.get();
        // }
        m_ticks++;
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