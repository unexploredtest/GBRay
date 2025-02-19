#pragma once

#include "common.hpp"
#include "cart.hpp"
#include "bus.hpp"

class Emu {
    public:
        Emu();
        void run(std::string filePath);
        std::unique_ptr<Cart>& getCart(); 

    private:
        std::unique_ptr<Cart> m_cart;
        std::unique_ptr<Bus> m_bus;
};