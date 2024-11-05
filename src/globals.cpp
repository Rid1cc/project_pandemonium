#include "globals.h"
#include <string>

// Definicje zmiennych globalnych (inicjalizacja)

// Gameplay
GameScreen currentScreen = LOGO;
Rectangle textBox = { 640.0f, 180.0f, 225, 50 };
char command[100] = "\0";
int letterCount = 0;
bool mouseOnText = false;
int framesCounter = 0;

int backTimer = 0;

const int screenWidth = 1280;
const int screenHeight = 720;

//Settings
int general_volume = 100;
int effects_volume = 100;
int upTimes = 0;


//Do przeniesienia oddzielny plik dla zmiennych do terminala
std::string history[30] = {" "};
std::string input = "";

