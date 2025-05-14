#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <array>
#include <memory>

#include "raylib.h"

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;

// Declared here so that one can use the other in their definition
class Cart;
class Emu;
class Bus;
class Cpu;
class Ram;
class IO;
class Timer;
class UI;
class Ppu;
class Dma;
class Lcd;
class Gamepad;