#include "ui.hpp"
#include "gamepad.hpp"
#include "emu.hpp"

UI::UI(Emu* emu) {
    m_emu = emu;
}

void UI::init(int screenWidth, int screenHeight) {
    m_paused = false;
    m_keepAspectRatio = true;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "GBRay");
    initGameText();
    initTilesText();
    SetTargetFPS(60);
}

void UI::run() {
    m_showTiles = false;
    while (!WindowShouldClose()) {
        input();
        BeginDrawing();

            if(m_showTiles){
                drawTiles();
            } else {
                ClearBackground(RAYWHITE);
                drawLCD();
            }

            displaySpeed();

            if(m_paused) {
                drawPaused();
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

    if(IsKeyPressed(KEY_A)) {
        m_keepAspectRatio = !m_keepAspectRatio;
    } 

    if(IsKeyPressed(KEY_F)) {
        m_emu->getPpu().toggleFrameLock();
    }

    if(IsKeyPressed(KEY_Z)) {
        m_emu->getGamepad().changeButton(BT_A, true);
    }

    if(IsKeyReleased(KEY_Z)) {
        m_emu->getGamepad().changeButton(BT_A, false);
    }

    if(IsKeyPressed(KEY_X)) {
        m_emu->getGamepad().changeButton(BT_B, true);
    }

    if(IsKeyReleased(KEY_X)) {
        m_emu->getGamepad().changeButton(BT_B, false);
    }

    if(IsKeyPressed(KEY_ENTER)) {
        m_emu->getGamepad().changeButton(BT_START, true);
    }

    if(IsKeyReleased(KEY_ENTER)) {
        m_emu->getGamepad().changeButton(BT_START, false);
    }

    if(IsKeyPressed(KEY_BACKSPACE)) {
        m_emu->getGamepad().changeButton(BT_SELECT, true);
    }

    if(IsKeyReleased(KEY_BACKSPACE)) {
        m_emu->getGamepad().changeButton(BT_SELECT, false);
    }

    if(IsKeyPressed(KEY_UP)) {
        m_emu->getGamepad().changeButton(BT_UP, true);
    }

    if(IsKeyReleased(KEY_UP)) {
        m_emu->getGamepad().changeButton(BT_UP, false);
    }

    if(IsKeyPressed(KEY_DOWN)) {
        m_emu->getGamepad().changeButton(BT_DOWN, true);
    }

    if(IsKeyReleased(KEY_DOWN)) {
        m_emu->getGamepad().changeButton(BT_DOWN, false);
    }

    if(IsKeyPressed(KEY_RIGHT)) {
        m_emu->getGamepad().changeButton(BT_RIGHT, true);
    }

    if(IsKeyReleased(KEY_RIGHT)) {
        m_emu->getGamepad().changeButton(BT_RIGHT, false);
    }

    if(IsKeyPressed(KEY_LEFT)) {
        m_emu->getGamepad().changeButton(BT_LEFT, true);
    }

    if(IsKeyReleased(KEY_LEFT)) {
        m_emu->getGamepad().changeButton(BT_LEFT, false);
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
                u8 lowByte = m_emu->getBus().read(baseIndex + 16*tileIndex + 2*line);
                u8 highByte = m_emu->getBus().read(baseIndex + 16*tileIndex + 2*line + 1);

                for(int pixel = 7; pixel >= 0; pixel--) {
                    u8 lowBit = (lowByte & (1 << pixel)) >> pixel;
                    u8 highBit = (highByte & (1 << pixel)) >> pixel;
                    int colorIndex = (highBit << 1) | lowBit;

                    Color color = COLORS[colorIndex];
                    ImageDrawPixel(&m_tilesImg, static_cast<float>(x*8+(7 - pixel)), static_cast<float>(y*8+line), color);
                }
            }
        }
    }

    UpdateTexture(m_tilesText, m_tilesImg.data);

    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();

    if(m_keepAspectRatio) {

        float scaleX = (float)currentWidth / (TILE_HIZ*8);
        float scaleY = (float)currentHeight / (TILE_VER*8);
        float scale = scaleX < scaleY ? scaleX : scaleY;

        int offset_x = (currentWidth - scale*TILE_HIZ*8) / 2;
        int offset_y = (currentHeight - scale*TILE_VER*8) / 2;

        Rectangle srcRec = {0.0f, 0.0f, (float)TILE_HIZ*8, (float)TILE_VER*8};
        Rectangle desRec = {offset_x, offset_y, (float)(TILE_HIZ*8 * scale), (float)(TILE_VER*8 * scale)};
        Vector2 org = {0.0f, 0.0f};

        ClearBackground(BLACK);
        DrawTexturePro(m_tilesText, srcRec, desRec, org, 0, RAYWHITE);
    } else {
        Rectangle srcRec = {0.0f, 0.0f, (float)TILE_HIZ*8, (float)TILE_VER*8};
        Rectangle desRec = {0.0f, 0.0f, currentWidth, currentHeight};
        Vector2 org = {0.0f, 0.0f};

        ClearBackground(BLACK);
        DrawTexturePro(m_tilesText, srcRec, desRec, org, 0, RAYWHITE);
    }
}

bool UI::isPaused() {
    return m_paused;
}

void UI::initGameText() {
    m_gameImg = GenImageColor(Ppu::WIDTH_SIZE, Ppu::HEIGHT_SIZE, RAYWHITE);
    m_gameText = LoadTextureFromImage(m_gameImg);
}

void UI::initTilesText() {
    m_tilesImg = GenImageColor(TILE_HIZ*8, TILE_VER*8, RAYWHITE);
    m_tilesText = LoadTextureFromImage(m_tilesImg);
}

void UI::drawLCD() {
    auto video = m_emu->getPpu().getVideo();
    for(int y = 0; y < Ppu::HEIGHT_SIZE; y++) {
        for(int x = 0; x < Ppu::WIDTH_SIZE; x++) {
            ImageDrawPixel(&m_gameImg, x, y, COLORS[video[y*Ppu::WIDTH_SIZE + x]]);
        }
    }
        
    UpdateTexture(m_gameText, m_gameImg.data);

    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();

    if(m_keepAspectRatio) {
        float scaleX = (float)currentWidth / Ppu::WIDTH_SIZE;
        float scaleY = (float)currentHeight / Ppu::HEIGHT_SIZE;
        float scale = scaleX < scaleY ? scaleX : scaleY;

        int offset_x = (currentWidth - scale*Ppu::WIDTH_SIZE) / 2;
        int offset_y = (currentHeight - scale*Ppu::HEIGHT_SIZE) / 2;

        Rectangle srcRec = {0.0f, 0.0f, (float)Ppu::WIDTH_SIZE, (float)Ppu::HEIGHT_SIZE};
        Rectangle desRec = {offset_x, offset_y, (float)(Ppu::WIDTH_SIZE * scale), (float)(Ppu::HEIGHT_SIZE * scale)};
        Vector2 org = {0.0f, 0.0f};

        ClearBackground(BLACK);
        DrawTexturePro(m_gameText, srcRec, desRec, org, 0, RAYWHITE);
    } else {
        Rectangle srcRec = {0.0f, 0.0f, (float)Ppu::WIDTH_SIZE, (float)Ppu::HEIGHT_SIZE};
        Rectangle desRec = {0.0f, 0.0f, currentWidth, currentHeight};
        Vector2 org = {0.0f, 0.0f};

        ClearBackground(BLACK);
        DrawTexturePro(m_gameText, srcRec, desRec, org, 0, RAYWHITE);
    }
}

void UI::drawPaused() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int fontSize = screenHeight / 9;

    const char *text = "paused";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1.0f);
    Vector2 textPosition = {(screenWidth - textSize.x) / 2, (screenHeight - textSize.y) / 2};

    DrawTextEx(GetFontDefault(), text, textPosition, fontSize, 1.0f, BLACK);
}

void UI::displaySpeed() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    float speedRatio = m_emu->getPpu().getSpeedRatio();

    char text[20];
    snprintf(text, sizeof(text), "%.2f", speedRatio);
    int marginX = screenWidth * 0.02;
    int marginY = screenHeight * 0.02;
    
    DrawText(text, marginX, marginY, 20, RED);
}