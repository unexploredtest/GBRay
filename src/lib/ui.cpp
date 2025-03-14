#include "ui.hpp"

UI::UI(Emu* emu) {
    m_emu = emu;
}

void UI::init(int screenWidth, int screenHeight) {
    // InitWindow(screenWidth, screenHeight, "GBRay");
    InitWindow(TILE_HIZ*8*SCALE, TILE_VER*8*SCALE, "GBRay");
    SetTargetFPS(60);
}

void UI::run() {
    m_showTiles = true;
    while (!WindowShouldClose()) {
        input();
        BeginDrawing();

            if(m_showTiles){
                drawTiles();
            } else {
                ClearBackground(RAYWHITE);
            }
            

        EndDrawing();
    }
}

void UI::input() {
    if(IsKeyPressed(KEY_D)) {
        m_showTiles = !m_showTiles;
    } 
}

void UI::deinit() {
    CloseWindow();
}

void UI::drawTiles() {
    const int baseIndex = 0x8000;
    ClearBackground(RAYWHITE);
    for(int y = 0; y < TILE_VER; y++) {
        for(int x = 0; x < TILE_HIZ; x++) {
            int tileIndex = y*TILE_HIZ + x;
            for(int line = 0; line < 8; line++) {
                u8 lowByte = m_emu->getBus()->read(baseIndex + 16*tileIndex + 2*line);
                u8 highByte = m_emu->getBus()->read(baseIndex + 16*tileIndex + 2*line + 1);

                for(int pixel = 7; pixel >= 0; pixel--) {
                    u8 lowBit = (lowByte & (1 << pixel)) >> pixel;
                    u8 highBit = (highByte & (1 << pixel)) >> pixel;
                    int colorIndex = (highBit << 1) | lowBit;

                    Color color = COLORS[colorIndex];
                    Rectangle pixelRec = {(x*8+(7 - pixel))*SCALE, (y*8+line)*SCALE, SCALE, SCALE};
                    DrawRectangleRec(pixelRec, color);
                }
            }
        }
    }
}