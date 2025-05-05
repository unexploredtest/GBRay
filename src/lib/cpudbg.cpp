#include "cpu.hpp"
#include <fstream>

static u32 curLine = 0x1;

void Cpu::writeCpuInfo() {
    std::ofstream dbgFile("cpudbg.txt", std::ios_base::app | std::ios::binary);
    char data[200];
    sprintf(data, "%08X%02X%02X%02X%02X%02X%02X%02X%02X%04X%04X\n", curLine, m_regs.A, m_regs.B, m_regs.C, m_regs.D, m_regs.E, m_regs.F, 
        m_regs.H, m_regs.L, m_regs.SP, m_regs.PC);
    curLine++;
    dbgFile << data;
    dbgFile.close();
}