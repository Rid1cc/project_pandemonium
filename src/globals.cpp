#include "globals.h"

// Definicje zmiennych globalnych (inicjalizacja)
GameScreen currentScreen = LOGO;
Rectangle textBox = { 640.0f, 180.0f, 225, 50 };
char command[100] = "\0";
int letterCount = 0;
bool mouseOnText = false;
int framesCounter = 0;
const int screenWidth = 1280;
const int screenHeight = 720;