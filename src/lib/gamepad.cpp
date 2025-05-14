#include "gamepad.hpp"

Gamepad::Gamepad(Emu* emu) {
    m_emu = emu;
}

void Gamepad::changeButton(Button button, bool set) {
    switch(button) {
        case BT_A:
            m_buttons.a = set;
            break;
        case BT_B:
            m_buttons.b = set;
            break;
        case BT_START:
            m_buttons.start = set;
            break;
        case BT_SELECT:
            m_buttons.select = set;
            break;
        case BT_UP:
            m_buttons.up = set;
            break;
        case BT_RIGHT:
            m_buttons.right = set;
            break;
        case BT_DOWN:
            m_buttons.down = set;
            break;
        case BT_LEFT:
            m_buttons.left = set;
            break;
    }
}

bool Gamepad::getDir() {
    return m_isDirSelect;
}

bool Gamepad::getBut() {
    return m_isButSelect;
}

void Gamepad::write(u8 value) {
    m_isButSelect = value & 0x20;
    m_isDirSelect = value & 0x10;
}

u8 Gamepad::read() {
    u8 gameboyInp = 0b11 << 6;
    if(!m_isButSelect) {
        gameboyInp = gameboyInp | (!m_buttons.start << 3);
        gameboyInp = gameboyInp | (!m_buttons.select << 2);
        gameboyInp = gameboyInp | (!m_buttons.b << 1);
        gameboyInp = gameboyInp | (!m_buttons.a << 0);
    }
    
    if(!m_isDirSelect) {
        gameboyInp = gameboyInp | (!m_buttons.down << 3);
        gameboyInp = gameboyInp | (!m_buttons.up << 2);
        gameboyInp = gameboyInp | (!m_buttons.left << 1);
        gameboyInp = gameboyInp | (!m_buttons.right << 0);
    }

    return gameboyInp;
}