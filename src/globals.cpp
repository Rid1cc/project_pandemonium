#include "headers/globals.h"
#include <string>
#include <raylib.h>
#include "headers/MiniGameManager.h"
#include <random>
#include <chrono>

//Random init
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// Global variables
bool exitGame = false;

//3D stuff
Model model_globe;
Model model_cog;
Model model_door;
Model model_data;
Camera camera;

// Gameplay
GameScreen currentScreen = TITLE;
Rectangle healthBar = {screen.x + 30, screen.y + 30, 1117, 40};
Rectangle attackMenu = {screen.x + 30, screen.y + 97, 249, 106};
Rectangle infoPanel = {screen.x + 30, screen.y + 250, 249, 383};
Rectangle terminalWindow = {screen.x + 312, screen.y + 97, 556, 540};
Rectangle PIDMenu = {screen.x + 900, screen.y + 97, 249, 540};
Rectangle textBox = terminalWindow;
// Rectangle textBox = {terminalWindow.x + 5, terminalWindow.y + terminalWindow.height, terminalWindow.width, terminalWindow.height};
char command[100] = "\0";
int letterCount = 0;
bool mouseOnText = false;
int framesCounter = 0;
int backTimer = 0;
int upTimes = 0;
std::string history[30] = {" "};
std::string historyDrawn[30] = {" "};
std::string input = "";
MiniGameManager gameManager;
Vector2 mousePos = { 0.0f, 0.0f};

//Title
Rectangle title = {float(screenWidth/5), float(screenHeight/9), float((screenWidth/5)*3), float((screenHeight/9)*1.4)};
Rectangle button_exit ={100, float(screenHeight)-130, 200, 50};
Rectangle button_lore ={100, float(screenHeight)-210, 200, 50};
Rectangle button_settings ={100, float(screenHeight)-290, 200, 50};
Rectangle button_play ={100, float(screenHeight)-370, 200, 50};
Rectangle desc_window ={350, float(screenHeight)-370, 500, 290};
Rectangle anim_window_title ={880, float(screenHeight)-370, 300, 290};
RenderTexture2D space3d;

//Main
const int screenWidth = 1280;
const int screenHeight = 720;
Rectangle screen = {50, 25, screenWidth-100, screenHeight-50};


//Settings
SettingsScreen currentSettings = GRAPHICS;
float general_volume = 1.0f;
float effects_volume = 1.0f;


// Music
Music main_theme = LoadMusicStream("country.mp3");
bool mute_audio = false;


//Fonts !!! INITIALIZE IN MAIN, OPENGL THREAD NEEDED
Font alagard;
Font pixeled;


//-----------Extra functions-----------
//Drawtext using alagard font (quicker method)
void DrawTextB(const char *text, float posX, float posY, int fontSize, Color color)
{
    DrawTextEx(alagard, text, (Vector2){ posX, posY }, fontSize, 2, color);
}
//Drawtext using pixeleted font
void DrawTextC(const char *text, float posX, float posY, int fontSize, Color color)
{
    DrawTextEx(pixeled, text, (Vector2){ posX, posY }, fontSize, 2, color);
}
//Shake float !
float ShakeXY(float pos, float intensity){
    float shook;
    std::uniform_int_distribution<int> rS(pos-intensity, pos+intensity);
    shook = rS(rng);
    return shook;
}

//Shake rectangle!
Rectangle ShakeRectangle(Rectangle rec, float intensity){
    Rectangle shook;
    std::uniform_int_distribution<int> rX(rec.x-intensity, rec.x+intensity);
    std::uniform_int_distribution<int> rY(rec.y-intensity, rec.y+intensity);
    std::uniform_int_distribution<int> rW(rec.width-intensity, rec.width+intensity);
    std::uniform_int_distribution<int> rH(rec.height-intensity, rec.height+intensity);
    shook = {float(rX(rng)),float(rY(rng)),float(rW(rng)),float(rH(rng))};
    return shook; 
}

//Shake rectangle on click!
Rectangle ShakeRectangleOnClick(Rectangle rec, float intensity){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true){
    Rectangle shook;
    std::uniform_int_distribution<int> rX(rec.x-intensity, rec.x+intensity);
    std::uniform_int_distribution<int> rY(rec.y-intensity, rec.y+intensity);
    std::uniform_int_distribution<int> rW(rec.width-intensity, rec.width+intensity);
    std::uniform_int_distribution<int> rH(rec.height-intensity, rec.height+intensity);
    shook = {float(rX(rng)),float(rY(rng)),float(rW(rng)),float(rH(rng))};
    return shook; 
    }
    else{
        return rec;
    }
}

//Custom round (number, decimal pos)
float Enround(float num, int pos) {
    float mpower = std::pow(10.0, pos); // 10^miejsca
    return std::round(num * mpower) / mpower;
}

//Clamping (purpose sliders, can be used wherever)
float Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
