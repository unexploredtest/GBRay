#pragma once

#include "common.hpp"


struct CartHeader {
    u32 entry;
    u8 logo[48];
    // If the whole 16 bytes are full, then it's not null-terminated for now I'll
    // do a work around but latter should make it work even with 16 bytes
    u8 title[16];
    u16 licenseeCode;
    u8 SGBFlag;
    u8 cartridgeType;
    u8 ROMSize;
    u8 RAMSize;
    u8 destCode;
    u8 old_licenseeCode;
    u8 maskROM;
    u8 lChecksum; // local checksum
    u16 gChecksum; // global checksum
};

class Cart {
    public:
        Cart() = default;
        Cart(Emu* emu);
        void loadROM(std::string& filePath);
        void printROMInfo();
        u8 read(u16 address);
        void write(u16 address, u8 value);
        std::string getTitle();
        std::string getLicensee();
        std::string getLicenseeCode();
        std::string getType();
        u32 getROMSize();
        u32 getRAMSize();
        

    private:
        Emu* m_emu;
        std::vector<char> m_buffer;
        CartHeader m_cartHeader;
        bool m_validHeader;
};