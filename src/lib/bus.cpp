#include "bus.hpp"
#include "ram.hpp"
#include "cart.hpp"
#include "cpu.hpp"

Bus::Bus(Emu* emu) {
    m_emu = emu;
}

u8 Bus::read(u16 address) {
    if(address < 0x8000) { // Cartridge ROM
        return m_emu->getCart()->read(address);
    } else if(address < 0xA000) { // VRAM
        std::cout << "WARNING: Bus read address 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xC000) { // External RAM, from cartridge
        return m_emu->getCart()->read(address);
    } else if(address < 0xE000) { // WRAM
        return m_emu->getRam()->readWRam(address - 0xC000);
    } else if(address < 0xFE00) { // Echo RAM
        std::cout << "WARNING: Bus read address 0x" << std::hex <<
            (int)address << " is prohibited!" << std::endl;
    } else if(address < 0xFEA0) { // Object attribute memory
        std::cout << "WARNING: Bus read address 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xFF00) { // Not Usable
        std::cout << "WARNING: Bus read address 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xFF80) { // I/O Registers
        std::cout << "WARNING: Bus read address 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xFFFF) { // HRAM
        return m_emu->getRam()->readWRam(address - 0xFF80); 
    } else if(address == 0xFFFF) { // IE Register
        return m_emu->getCpu()->readIERegister();
    }
}

void Bus::write(u16 address, u8 value) {
    if(address < 0x8000) {
        return m_emu->getCart()->write(address, value);
    } else if(address < 0xA000) { // VRAM
        std::cout << "WARNING: Bus write saddress 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xC000) { // External RAM, from cartridge
        return m_emu->getCart()->write(address, value);
    } else if(address < 0xE000) { // WRAM
        return m_emu->getRam()->writeWRam(address - 0xC000, value);
    } else if(address < 0xFE00) { // Echo RAM
        std::cout << "WARNING: Bus write saddress 0x" << std::hex <<
            (int)address << " is prohibited!" << std::endl;
    } else if(address < 0xFEA0) { // Object attribute memory
        std::cout << "WARNING: Bus write saddress 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xFF00) { // Not Usable
        std::cout << "WARNING: Bus write saddress 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xFF80) { // I/O Registers
        std::cout << "WARNING: Bus write saddress 0x" << std::hex <<
            (int)address << " not supported!" << std::endl;
    } else if(address < 0xFFFF) { // HRAM
        return m_emu->getRam()->writeWRam(address - 0xFF80, value); 
    } else if(address == 0xFFFF) { // IE Register
        return m_emu->getCpu()->writeIERegister(value);
    }
}

u16 Bus::read16(u16 address) {
    u16 lo = read(address);
    u16 hi = read(address + 1);

    return lo | (hi << 8);
}

void Bus::write16(u16 address, u16 value) {
    write(address + 1, (value >> 8) & 0xFF);
    write(address, value & 0xFF);
}
