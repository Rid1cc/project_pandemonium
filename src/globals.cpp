#include "headers/globals.h"
#include <string>
#include "headers/MiniGameManager.h"
#include <random>
#include <chrono>

#if defined(_WIN32)
    // #include <windows.h> // Removed to prevent conflicts
    #include <raylib.h>
    
    // Define necessary Windows types manually
    typedef void* HMODULE;
    typedef char* LPSTR;
    typedef unsigned long DWORD; // Added definition for DWORD
    #define WINAPI __stdcall     // Added definition for WINAPI
    
    // Declare only GetModuleFileNameA
    extern "C" __declspec(dllimport) DWORD WINAPI GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize);
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#else
    #include <dlfcn.h>
    #include <unistd.h>
#endif

//Random init
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// Global variables
bool exitGame = false;
std::string assetsPath;
std::string configPath;
Rectangle TextureKernel;

//3D stuff
Model model_globe;
Model model_cog;
Model model_door;
Model model_data;
Camera camera;

// Shader parameters
extern float curvature;
extern float bloomIntensity;
extern float glowIntensity;
extern float scanlineIntensity;
extern float brightness;
extern Vector2 sh_resolution;

// Gameplay
GameScreen currentScreen = TITLE;
Texture2D botnetTexture;
Texture2D ddosTexture;
Texture2D mailbombTexture;

// Rectangle textBox = {terminalWindow.x + 5, terminalWindow.y + terminalWindow.height, terminalWindow.width, terminalWindow.height};
char command[100] = "\0";
int letterCount = 0;
bool mouseOnText = false;
int framesCounter = 0;
int backTimer = 0;
int upTimes = 0;
std::string history[50] = {" "};
std::string historyDrawn[50] = {" "};
std::string input = "";
MiniGameManager miniGamesManager;
GameplayManager gameplayManager;
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

// Difficulty
int SelectedDifficulty = 0;

//Settings
SettingsScreen currentSettings = GRAPHICS;
SettingState debugMode = MID;

float general_volume = 1.0f;
float effects_volume = 1.0f;
Color primaryColor;


// Music
Music main_theme;
Music game_theme;
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

// Function to get the path to the assets directory
std::string getSubfolderPath(std::string subfolder){
    char buffer[1024];
    std::string path;

    #if defined(_WIN32)
        DWORD size = GetModuleFileNameA(NULL, buffer, sizeof(buffer));
        if (size == 0 || size == sizeof(buffer)) {
            std::cerr << "Failed to get executable path." << std::endl;
            return "";
        }
        path = std::string(buffer);
    #elif defined(__APPLE__)
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) != 0) {
            std::cerr << "Buffer too small; need size " << size << std::endl;
            return "";
        }
        path = std::string(buffer);
    #else
        ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (count == -1) {
            std::cerr << "Failed to get executable path." << std::endl;
            return "";
        }
        buffer[count] = '\0';
        path = std::string(buffer);
    #endif

    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        std::cerr << "Invalid executable path." << std::endl;
        return "";
    }
    return path.substr(0, pos) + "/../" + subfolder + "/";
}