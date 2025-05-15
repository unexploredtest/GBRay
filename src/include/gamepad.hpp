#pragma once

#include "common.hpp"

struct Buttons
{
    bool a;
    bool b;
    bool start;
    bool select;
    bool up;
    bool right;
    bool down;
    bool left;
};

enum Button {
    BT_A,
    BT_B,
    BT_START,
    BT_SELECT,
    BT_UP,
    BT_RIGHT,
    BT_DOWN,
    BT_LEFT
};

class Gamepad {
    public:
        Gamepad() = default;
        Gamepad(Emu* emu);

        void write(u8 value);
        u8 read();

        void changeButton(Button button, bool set);
        Buttons getButton();
        bool getDir();
        bool getBut();
        
    private:
        Emu* m_emu;
        Buttons m_buttons;
        bool m_isDirSelect;
        bool m_isButSelect;
};
