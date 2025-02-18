#pragma once

#include "common.hpp"
#include "emu.hpp"


struct CartHeader {
    uint32_t entry;
    uint8_t logo[48];
    // If the whole 16 bytes are full, then it's not null-terminated for now I'll
    // do a work around but latter should make it work even with 16 bytes
    uint8_t title[16];
    uint16_t licenseeCode;
    uint8_t SGBFlag;
    uint8_t cartridgeType;
    uint8_t ROMSize;
    uint8_t RAMSize;
    uint8_t destCode;
    uint8_t old_licenseeCode;
    uint8_t maskROM;
    uint8_t lChecksum; // local checksum
    uint16_t gChecksum; // global checksum
};

class Cart {
    public:
        Cart();
        Cart(Emu* emu);
        void loadROM(std::string& filePath);
        void printROMInfo();
        std::string getTitle();
        std::string getLicensee();
        std::string getType();
        uint32_t getROMSize();
        uint32_t getRAMSize();
        

    private:
        Emu* m_emu;
        std::vector<char> m_buffer;
        CartHeader m_cartHeader;
        bool m_validHeader;
};