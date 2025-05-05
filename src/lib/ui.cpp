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
        
        // if(m_paused) {
        //     ClearBackground(RAYWHITE);
        //     continue;
        // }
        BeginDrawing();


            if(m_showTiles){
                SetWindowSize(TILE_HIZ*8*SCALE, TILE_VER*8*SCALE);
                drawTiles();
            } else {
                SetWindowSize(WIDTH_SIZE*SCALE, HEIGHT_SIZE*SCALE);
                ClearBackground(RAYWHITE);
                drawLCD();
            }
            

        EndDrawing();
    }
}

void UI::input() {
    if(IsKeyPressed(KEY_D)) {
        m_showTiles = !m_showTiles;
    } 

    if(IsKeyPressed(KEY_P)) {
        m_paused = !m_paused;
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
                    Rectangle pixelRec = {static_cast<float>((x*8+(7 - pixel))*SCALE), static_cast<float>((y*8+line)*SCALE), SCALE, SCALE};
                    DrawRectangleRec(pixelRec, color);
                }
            }
        }
    }
}

bool UI::isPaused() {
    return m_paused;
}

void UI::drawLCD() {
    u8* video = m_emu->getPpu()->getVideo();
    Image gameVid = GenImageColor(WIDTH_SIZE, HEIGHT_SIZE, RAYWHITE);
    for(int y = 0; y < HEIGHT_SIZE; y++) {
        for(int x = 0; x < WIDTH_SIZE; x++) {
            ImageDrawPixel(&gameVid, x, y, COLORS[video[y*WIDTH_SIZE + x]]);
        }
    }
    Texture2D texture = LoadTextureFromImage(gameVid);
    UnloadImage(gameVid);
    // DrawTexture(texture, 0, 0, RAYWHITE);
    Rectangle srcRec = {0.0f, 0.0f, WIDTH_SIZE, HEIGHT_SIZE};
    Rectangle desRec = {0, 0, WIDTH_SIZE*SCALE, HEIGHT_SIZE*SCALE};
    Vector2 org = {0.0f, 0.0f};
    DrawTexturePro(texture, srcRec, desRec, org, 0, RAYWHITE);
}