#pragma once

#include "common.hpp"
#include "cart.hpp"

class Emu {
    public:
        Emu();
        void run(std::string filePath);

    private:
        std::unique_ptr<Cart> m_cart;
};