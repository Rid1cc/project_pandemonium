#include "raylib.h"
#include <vector>
#include <fstream>
#include "./headers/json.hpp"
#include "./headers/globals.h"
#include "./headers/settings_vars.h"


//Locations
int curvatureLoc;
int bloomIntensityLoc;
int glowIntensityLoc;
int scanlineIntensityLoc;
int brightnessLoc;
int sh_resolutionLoc;

//Parameters
float curvature;
float bloomIntensity;
float glowIntensity;
float scanlineIntensity;
float brightness;
Vector2 sh_resolution;
Shader shader;


std::vector<std::vector<Vector2>> curvatureMap;

void GenerateCurvatureMap(Vector2 resolution, float curvature) {
    curvatureMap.resize(resolution.y, std::vector<Vector2>(resolution.x));

    for (int y = 0; y < resolution.y; y++) {
        for (int x = 0; x < resolution.x; x++) {
            Vector2 uv = {x / (float)resolution.x, y / (float)resolution.y};

            uv = {uv.x * 2.0f - 1.0f, uv.y * 2.0f - 1.0f};
            uv.x *= 1.0f + curvature * (uv.y * uv.y);
            uv.y *= 1.0f + curvature * (uv.x * uv.x);
            uv = {(uv.x + 1.0f) * 0.5f, (uv.y + 1.0f) * 0.5f};

            curvatureMap[y][x] = {uv.x * resolution.x, uv.y * resolution.y};
        }
    }
}
Vector2 MapMouseToFlat(Vector2 mousePos, Vector2 resolution) {
    int x = (int)mousePos.x;
    int y = (int)mousePos.y;

    // Upewnij się, że pozycja jest w granicach
    x = Clamp(x, 0, resolution.x - 1);
    y = Clamp(y, 0, resolution.y - 1);

    return curvatureMap[y][x];
}
void ReloadShader(){
    SetShaderValue(shader, curvatureLoc, &curvature, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, bloomIntensityLoc, &bloomIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, scanlineIntensityLoc, &scanlineIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, brightnessLoc, &brightness, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, sh_resolutionLoc, &sh_resolution, SHADER_UNIFORM_VEC2);
    GenerateCurvatureMap({static_cast<float>(screenWidth), static_cast<float>(screenHeight)}, curvature);
    primaryColor = displayColor; // Ensure primaryColor is set to displayColor
}
void InitializeShader() {
    std::string assetsPath = getAssetsPath();
    shader = LoadShader(0, (assetsPath + "shaders/fx.fs").c_str());

    if (shader.id == 0) {
        std::cerr << "Failed to load shader" << std::endl;
        return;
    }

    // Get locs
    curvatureLoc = GetShaderLocation(shader, "curvature");
    bloomIntensityLoc = GetShaderLocation(shader, "bloomIntensity");
    glowIntensityLoc = GetShaderLocation(shader, "glowIntensity");
    scanlineIntensityLoc = GetShaderLocation(shader, "scanlineIntensity");
    brightnessLoc = GetShaderLocation(shader, "brightness");
    sh_resolutionLoc = GetShaderLocation(shader, "resolution");

    // Load default settings first
    LoadSettingsDefault();

    // Check if settings file exists and is readable
    std::ifstream settingsFile("settings.json");
    if (!settingsFile.good()) {
        // Create settings.json with default settings
        FileSystemManager fsm;
        fsm.saveSettings("settings.json");
    } else {
        try {
            // Load settings from file
            FileSystemManager fsm;
            fsm.loadSettings("settings.json");
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Failed to parse settings.json: " << e.what() << std::endl;
            // Create settings.json with default settings
            FileSystemManager fsm;
            fsm.saveSettings("settings.json");
        }
    }

    ReloadShader();
}

