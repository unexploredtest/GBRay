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
#include "gamepad.hpp"

class Emu {
    public:
        Emu();
        void run(std::string filePath);
        void runCpu();
        Cart& getCart(); 
        Bus& getBus();
        Ram& getRam();
        Cpu& getCpu();
        IO& getIO();
        Timer& getTimer();
        UI& getUI();
        Ppu& getPpu();
        Dma& getDma();
        Lcd& getLcd();
        Gamepad& getGamepad();
        
    private:
        bool m_running;
        bool m_paused;
        bool m_die;
        u32 m_ticks;

        Cart m_cart;
        Bus m_bus;
        Cpu m_cpu;
        Ppu m_ppu;
        Ram m_ram;
        IO m_io;
        Timer m_timer;
        UI m_ui;
        Dma m_dma;
        Lcd m_lcd;
        Gamepad m_gamepad;
};