#include "raylib.h"

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

void InitializeShader() {
    shader = LoadShader(0, "../assets/shaders/fx.fs");

    // Get locs
    curvatureLoc = GetShaderLocation(shader, "curvature");
    bloomIntensityLoc = GetShaderLocation(shader, "bloomIntensity");
    glowIntensityLoc = GetShaderLocation(shader, "glowIntensity");
    scanlineIntensityLoc = GetShaderLocation(shader, "scanlineIntensity");
    brightnessLoc = GetShaderLocation(shader, "brightness");
    sh_resolutionLoc = GetShaderLocation(shader, "resolution");

    // Set params
    curvature = 0.07f;
    bloomIntensity = 2.3f;
    glowIntensity = 1.5f;
    scanlineIntensity = 1.0f;
    brightness = 1.4f;
    sh_resolution = { 1920.0f, 1080.0f };

    SetShaderValue(shader, curvatureLoc, &curvature, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, bloomIntensityLoc, &bloomIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, scanlineIntensityLoc, &scanlineIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, brightnessLoc, &brightness, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, sh_resolutionLoc, &sh_resolution, SHADER_UNIFORM_VEC2);

}
