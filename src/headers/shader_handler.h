#ifndef SHADER_HANDLER_H
#define SHADER_HANDLER_H

#include "raylib.h"

//Locations
extern int curvatureLoc;
extern int bloomIntensityLoc;
extern int glowIntensityLoc;
extern int scanlineIntensityLoc;
extern int sh_resolutionLoc;
extern int brightnessLoc;

//Parameters
extern float curvature;
extern float bloomIntensity;
extern float glowIntensity;
extern float scanlineIntensity;
extern float brightness;
extern Vector2 sh_resolution;

//Shader
extern Shader shader;

void InitializeShader();
void ReloadShader();

#endif