#include "io.hpp"

IO::IO(Emu* emu) {
    m_emu = emu;
}

u8 IO::read(u16 address) {
    switch(address) {
        case 0x01:
        case 0x02:
            return m_serialData[address - 1];
        case 0x04:
            return m_emu->getTimer()->read(TT_DIV);
        case 0x05:
            return m_emu->getTimer()->read(TT_TIMA);
        case 0x06:
            return m_emu->getTimer()->read(TT_TMA);
        case 0x07:
            return m_emu->getTimer()->read(TT_TAC);
        case 0x0F:
            return m_emu->getCpu()->readIntFlags();
        default:
            std::cout << "WARNING: IO read address 0x" << std::hex <<
            (int)address + 0xFF00 << " not supported!" << std::endl;
            return 0;
    }
}

void IO::write(u16 address, u8 value) {
    switch(address) {
        case 0x01:
        case 0x02:
            m_serialData[address - 1] = value;
            break;
        case 0x04:
            m_emu->getTimer()->write(TT_DIV, value);
            break;
        case 0x05:
            m_emu->getTimer()->write(TT_TIMA, value);
            break;
        case 0x06:
            m_emu->getTimer()->write(TT_TMA, value);
            break;
        case 0x07:
            m_emu->getTimer()->write(TT_TAC, value);
            break;
        case 0x0F:
            m_emu->getCpu()->writeIntFlags(value);
            break;
        default:
            std::cout << "WARNING: IO write address 0x" << std::hex <<
            (int)address + 0xFF00 << " not supported!" << std::endl;
            break;
    }
    
}


// std::cout << "WARNING: Bus read address 0x" << std::hex <<
//             (int)address << " not supported!" << std::endl;

// std::cout << "WARNING: Bus write saddress 0x" << std::hex <<
//             (int)address << " not supported!" << std::endl;