#include "logo_screen.h"

RenderTexture2D logo_screen;
Image logoImage;
Texture2D logo;
int recposy = 0;

void InitLogoScreen() {
    // Define screen
    logo_screen = LoadRenderTexture(screenWidth, screenHeight);
    // Load the logo texture
    logoImage = LoadImage((assetsPath + "/images/undersmokedstudios.png").c_str());
    logo = LoadTextureFromImage(logoImage);
    UnloadImage(logoImage);
}

void DrawLogoScreen() {
    ClearBackground(BLACK);
    float scale = 0.5f;
    int logoWidth = static_cast<int>(logo.width * scale);
    int logoHeight = static_cast<int>(logo.height * scale);
    DrawTextureEx(logo, (Vector2){static_cast<float>((ShakeXY(screenWidth, 1.5) - logoWidth) / 2), static_cast<float>((ShakeXY(screenHeight, 1.5) - logoHeight) / 2)}, 0.0f, scale, WHITE);
    DrawRectangleGradientV(0, recposy, screenWidth, screenHeight/5, Color{0,0,0,0}, Color{0,0,0,255});
    DrawRectangle(0, recposy+(screenHeight/5), screenWidth, screenHeight, Color{0,0,0,255});
}

void UpdateLogoScreen() {
    // Wait for 2 seconds
    if (framesCounter < 400) {
        framesCounter++;
        recposy = recposy+2;
    } else {
        currentScreen = TITLE;
        // Unload logo texture
        UnloadTexture(logo);
    }
}