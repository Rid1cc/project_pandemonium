#include "raylib.h"
#include <vector>
#include <fstream>
#include "./headers/json.hpp"
#include "./headers/globals.h"
#include "./headers/settings_vars.h"
#include <filesystem>
#include "./managers/FileSystemManager.h"


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
            float dotProduct = uv.x * uv.x + uv.y * uv.y;
            uv.x *= 1.0f + curvature * dotProduct;
            uv.y *= 1.0f + curvature * dotProduct;
            uv = {(uv.x + 1.0f) * 0.5f, (uv.y + 1.0f) * 0.5f};

            curvatureMap[y][x] = {uv.x * resolution.x, uv.y * resolution.y};
        }
    }
}

Vector2 MapMouseToFlat(Vector2 mousePos, Vector2 resolution) {
    int x = (int)mousePos.x;
    int y = (int)mousePos.y;

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
void InitializeShader() { //and load + initialize settings, extremely important, graphics wont work without this
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

    // Initialize FileSystemManager
    FileSystemManager fsm;
    fsm.initialize();

    ReloadShader();
}

