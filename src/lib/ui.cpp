#include "ui.hpp"

UI::UI(Emu* emu) {
    m_emu = emu;
}

void UI::init(int screenWidth, int screenHeight) {
    InitWindow(screenWidth, screenHeight, "GBRay");
    SetTargetFPS(60);
}

void UI::run() {
    while (!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(RAYWHITE);

        EndDrawing();
    }
}

void UI::deinit() {
    CloseWindow();
}