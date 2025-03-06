#pragma once

#include <thread>

#include "common.hpp"
#include "cart.hpp"
#include "bus.hpp"
#include "cpu.hpp"
#include "ram.hpp"

class Emu {
    public:
        Emu();
        void run(std::string filePath);
        void runCpu();
        std::unique_ptr<Cart>& getCart(); 
        std::unique_ptr<Bus>& getBus();
        std::unique_ptr<Ram>& getRam();
        std::unique_ptr<Cpu>& getCpu();

    private:
        bool m_running;
        bool m_paused;
        bool m_die;
        u32 m_ticks;

        std::unique_ptr<Cart> m_cart;
        std::unique_ptr<Bus> m_bus;
        std::unique_ptr<Cpu> m_cpu;
        std::unique_ptr<Ram> m_ram;
};