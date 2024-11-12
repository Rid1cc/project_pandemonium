#include "headers/globals.h"
#include <string>
#include <raylib.h>

// Global variables

// Gameplay
GameScreen currentScreen = LOGO;
Rectangle textBox = { 640.0f, 180.0f, 225, 50 };
char command[100] = "\0";
int letterCount = 0;
bool mouseOnText = false;
int framesCounter = 0;
int backTimer = 0;
std::string history[30] = {" "};
std::string input = "";


//Main
const int screenWidth = 1280;
const int screenHeight = 720;

//Settings
int general_volume = 100;
int effects_volume = 100;
int upTimes = 0;

//Fonts !!! INITIALIZE IN MAIN, OPENGL THREAD NEEDED
Font alagard;

//-----------Extra functions-----------
//Drawtext using alagard font (quicker method)
void DrawTextB(const char *text, float posX, float posY, int fontSize, Color color)
{
    DrawTextEx(alagard, text, (Vector2){ posX, posY }, fontSize, 2, color);
}

