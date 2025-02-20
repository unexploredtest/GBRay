#pragma once

#include "common.hpp"
#include "cart.hpp"
#include "bus.hpp"
#include "cpu.hpp"

class Emu {
    public:
        Emu();
        void run(std::string filePath);
        std::unique_ptr<Cart>& getCart(); 
        std::unique_ptr<Bus>& getBus();

    private:
        std::unique_ptr<Cart> m_cart;
        std::unique_ptr<Bus> m_bus;
        std::unique_ptr<Cpu> m_cpu;
};