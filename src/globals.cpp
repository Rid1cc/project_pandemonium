#include "headers/globals.h"
#include <string>
#include <raylib.h>
#include "headers/MiniGameManager.h"

// Global variables

// Gameplay
GameScreen currentScreen = TITLE;
Rectangle textBox = { 640.0f, 180.0f, 225, 50 };
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

//Main
const int screenWidth = 1280;
const int screenHeight = 720;
Rectangle screen = {50, 25, screenWidth-100, screenHeight-50};


//Settings
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
void DrawTextC(const char *text, float posX, float posY, int fontSize, Color color)
{
    DrawTextEx(pixeled, text, (Vector2){ posX, posY }, fontSize, 2, color);
}