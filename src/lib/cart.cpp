#include "cart.hpp"

// static const char *ROM_TYPES[] = {
//     "ROM ONLY",
//     "MBC1",
//     "MBC1+RAM",
//     "MBC1+RAM+BATTERY",
//     "0x04 ???",
//     "MBC2",
//     "MBC2+BATTERY",
//     "0x07 ???",
//     "ROM+RAM 1",
//     "ROM+RAM+BATTERY 1",
//     "0x0A ???",
//     "MMM01",
//     "MMM01+RAM",
//     "MMM01+RAM+BATTERY",
//     "0x0E ???",
//     "MBC3+TIMER+BATTERY",
//     "MBC3+TIMER+RAM+BATTERY 2",
//     "MBC3",
//     "MBC3+RAM 2",
//     "MBC3+RAM+BATTERY 2",
//     "0x14 ???",
//     "0x15 ???",
//     "0x16 ???",
//     "0x17 ???",
//     "0x18 ???",
//     "MBC5",
//     "MBC5+RAM",
//     "MBC5+RAM+BATTERY",
//     "MBC5+RUMBLE",
//     "MBC5+RUMBLE+RAM",
//     "MBC5+RUMBLE+RAM+BATTERY",
//     "0x1F ???",
//     "MBC6",
//     "0x21 ???",
//     "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
// };

static const std::array<const char*, 0xFF> ROM_TYPES = [] {
    std::array<const char*, 0xFF> temp = {};
    temp.fill("???"); // Unassigned value get the default value "???"
    temp[0x00] = "ROM ONLY";
    temp[0x01] = "MBC1";
    temp[0x02] = "MBC1+RAM";
    temp[0x03] = "MBC1+RAM+BATTERY";
    // temp[0x04] = "0x04 ???";
    temp[0x05] = "MBC2";
    temp[0x06] = "MBC2+BATTERY";
    // temp[0x07] = "0x07 ???";
    temp[0x08] = "ROM+RAM 1";
    temp[0x09] = "ROM+RAM+BATTERY 1";
    // temp[0x0A] = "0x0A ???";
    temp[0x0B] = "MMM01";
    temp[0x0C] = "MMM01+RAM";
    temp[0x0D] = "MMM01+RAM+BATTERY";
    // temp[0x0E] = "0x0E ???";
    temp[0x0F] = "MBC3+TIMER+BATTERY";
    temp[0x10] = "MBC3+TIMER+RAM+BATTERY 2";
    temp[0x11] = "MBC3";
    temp[0x12] = "MBC3+RAM 2";
    temp[0x13] = "MBC3+RAM+BATTERY 2";
    // temp[0x14] = "0x14 ???";
    // temp[0x15] = "0x15 ???";
    // temp[0x16] = "0x16 ???";
    // temp[0x17] = "0x17 ???";
    // temp[0x18] = "0x18 ???";
    temp[0x19] = "MBC5";
    temp[0x1A] = "MBC5+RAM";
    temp[0x1B] = "MBC5+RAM+BATTERY";
    temp[0x1C] = "MBC5+RUMBLE";
    temp[0x1D] = "MBC5+RUMBLE+RAM";
    temp[0x1E] = "MBC5+RUMBLE+RAM+BATTERY";
    // temp[0x1F] = "0x1F ???";
    temp[0x20] = "MBC6";
    // temp[0x21] = "0x21 ???";
    temp[0x22] = "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
    temp[0xFC] = "POCKET CAMERA";
    temp[0xFD] = "BANDAI TAMA5";
    temp[0xFE] = "HuC3";
    temp[0xFF] = "HuC1+RAM+BATTERY";
    return temp;
}();

static const std::array<const char*, 0xA5> LIC_CODE = [] {
    std::array<const char*, 0xA5> temp = {};
    temp.fill("UKNOWN"); // Unassigned value get the default value "UKNOWN"
    temp[0x00] = "None";
    temp[0x01] = "Nintendo R&D1";
    temp[0x08] = "Capcom";
    temp[0x13] = "Electronic Arts";
    temp[0x18] = "Hudson Soft";
    temp[0x19] = "b-ai";
    temp[0x20] = "kss";
    temp[0x22] = "pow";
    temp[0x24] = "PCM Complete";
    temp[0x25] = "san-x";
    temp[0x28] = "Kemco Japan";
    temp[0x29] = "seta";
    temp[0x30] = "Viacom";
    temp[0x31] = "Nintendo";
    temp[0x32] = "Bandai";
    temp[0x33] = "Ocean/Acclaim";
    temp[0x34] = "Konami";
    temp[0x35] = "Hector";
    temp[0x37] = "Taito";
    temp[0x38] = "Hudson";
    temp[0x39] = "Banpresto";
    temp[0x41] = "Ubi Soft";
    temp[0x42] = "Atlus";
    temp[0x44] = "Malibu";
    temp[0x46] = "angel";
    temp[0x47] = "Bullet-Proof";
    temp[0x49] = "irem";
    temp[0x50] = "Absolute";
    temp[0x51] = "Acclaim";
    temp[0x52] = "Activision";
    temp[0x53] = "American sammy";
    temp[0x54] = "Konami";
    temp[0x55] = "Hi tech entertainment";
    temp[0x56] = "LJN";
    temp[0x57] = "Matchbox";
    temp[0x58] = "Mattel";
    temp[0x59] = "Milton Bradley";
    temp[0x60] = "Titus";
    temp[0x61] = "Virgin";
    temp[0x64] = "LucasArts";
    temp[0x67] = "Ocean";
    temp[0x69] = "Electronic Arts";
    temp[0x70] = "Infogrames";
    temp[0x71] = "Interplay";
    temp[0x72] = "Broderbund";
    temp[0x73] = "sculptured";
    temp[0x75] = "sci";
    temp[0x78] = "THQ";
    temp[0x79] = "Accolade";
    temp[0x80] = "misawa";
    temp[0x83] = "lozc";
    temp[0x86] = "Tokuma Shoten Intermedia";
    temp[0x87] = "Tsukuda Original";
    temp[0x91] = "Chunsoft";
    temp[0x92] = "Video system";
    temp[0x93] = "Ocean/Acclaim";
    temp[0x95] = "Varie";
    temp[0x96] = "Yonezawa/s’pal";
    temp[0x97] = "Kaneko";
    temp[0x99] = "Pack in soft";
    temp[0xA4] = "Konami (Yu-Gi-Oh!)";
    return temp;
}();

Cart::Cart(Emu* emu) {
    m_emu = emu;
    m_buffer = std::vector<char>(0);
}

void Cart::loadROM(std::string& filePath) {
    // std::vector<char> headerBuffer(80);
    // std::copy(buffer.begin() + 2, buffer.begin() + 6, headerBuffer.begin());
    std::cout << "LOG: Reading ROM file " << filePath << std::endl;
    std::ifstream romFile(filePath, std::ios::binary);
    if(!romFile) {
        // std::cout << "ERROR: Unable to read the file" << std::endl;
        throw std::runtime_error("ERROR: Unable to read the file: " + filePath);
    }

    romFile.seekg(0, std::ios::end);
    long size = romFile.tellg();
    std::cout << "LOG: File size is " << size << std::endl;
    romFile.seekg(0, std::ios::beg);

    m_buffer = std::vector<char>(size);

    if (!romFile.read(m_buffer.data(), size)) {
        throw std::runtime_error("Error reading file: " + filePath);
    }

    m_buffer[0x143] = 0; // In case the title is 16 byte, TODO: Should support a 16 byte title too
    m_cartHeader = reinterpret_cast<CartHeader&>(*(m_buffer.data() + 0x100));

    u8 checksum = 0;
    for (u16 address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - m_buffer[address] - 1;
    }

    if(m_cartHeader.lChecksum == checksum) {
        m_validHeader = true;
    } else {
        m_validHeader = false;
        std::cout << "WARNING: ROM header is not valid!" << std::endl;
    }

}

std::string Cart::getTitle() {
    const char* title = reinterpret_cast<char*>(m_cartHeader.title);
    return std::string(title);
}
std::string Cart::getLicensee() {
    if(m_cartHeader.licenseeCode <= 0x9A) {
        if(m_cartHeader.old_licenseeCode == 0x33) {
            return LIC_CODE[m_cartHeader.licenseeCode];
        } else {
            return LIC_CODE[m_cartHeader.old_licenseeCode];
        }
        
    } else {
        return "UKNOWN";
    }
}

std::string Cart::getLicenseeCode() {
    if(m_cartHeader.old_licenseeCode == 0x33) {
        std::string codeType = "NEW ";
        std::string code = std::to_string(m_cartHeader.licenseeCode);
        return codeType + code;
    } else {
        std::string codeType = "OLD ";
        std::string code = std::to_string(m_cartHeader.old_licenseeCode);
        return codeType + code;
    }
}

std::string Cart::getType() {
    return ROM_TYPES[m_cartHeader.cartridgeType];
}

void Cart::printROMInfo() {
    if(m_buffer.size() == 0) {
        std::cout << "WARNING: No ROM is loaded into the cartridge!" << std::endl;
        return;
    }

    m_cartHeader = reinterpret_cast<CartHeader&>(*(m_buffer.data() + 0x100));
    std::cout << "CARTRIDGE INFO:" << std::endl;
    std::cout << "TITLE: " << getTitle() << std::endl;
    std::cout << "LICENSEE: " << getLicenseeCode() << " " << getLicensee() << std::endl;
    std::cout << "TYPE: " << m_cartHeader.cartridgeType << getType() << std::endl;
    std::cout << "ROM SIZE: " << m_buffer.size() << std::endl;
    std::cout << "HEADER VALIDITY: " << m_validHeader << std::endl;

}