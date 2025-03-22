#pragma once

#include <thread>

#include "common.hpp"
#include "cart.hpp"
#include "bus.hpp"
#include "cpu.hpp"
#include "ram.hpp"
#include "io.hpp"
#include "timer.hpp"
#include "ui.hpp"
#include "ppu.hpp"
#include "dma.hpp"
#include "lcd.hpp"

class Emu {
    public:
        Emu();
        void run(std::string filePath);
        void runCpu();
        std::unique_ptr<Cart>& getCart(); 
        std::unique_ptr<Bus>& getBus();
        std::unique_ptr<Ram>& getRam();
        std::unique_ptr<Cpu>& getCpu();
        std::unique_ptr<IO>& getIO();
        std::unique_ptr<Timer>& getTimer();
        std::unique_ptr<UI>& getUI();
        std::unique_ptr<Ppu>& getPpu();
        std::unique_ptr<Dma>& getDma();
        std::unique_ptr<Lcd>& getLcd();
        
    private:
        bool m_running;
        bool m_paused;
        bool m_die;
        u32 m_ticks;

        std::unique_ptr<Cart> m_cart;
        std::unique_ptr<Bus> m_bus;
        std::unique_ptr<Cpu> m_cpu;
        std::unique_ptr<Ppu> m_ppu;
        std::unique_ptr<Ram> m_ram;
        std::unique_ptr<IO> m_io;
        std::unique_ptr<Timer> m_timer;
        std::unique_ptr<UI> m_ui;
        std::unique_ptr<Dma> m_dma;
        std::unique_ptr<Lcd> m_lcd;
};