#include "sc_graphics.h"
#include "../headers/globals.h"
#include "../headers/settings_vars.h"
#include "../headers/shader_handler.h"
#include <string>
#include <stdio.h>
#include <cmath>

using namespace std;
//Sliders
Rectangle curvature_slider = {settings_screen.x+300,settings_screen.y+50,270,30};
Rectangle bloomIntensity_slider = {settings_screen.x+300,settings_screen.y+100,270,30};
Rectangle glowIntensity_slider = {settings_screen.x+300,settings_screen.y+150,270,30};
Rectangle scanlineIntensity_slider = {settings_screen.x+300,settings_screen.y+200,270,30};
Rectangle brightness_slider = {settings_screen.x+300,settings_screen.y+250,270,30};

//Frames
Rectangle shader_quality_frame = {settings_screen.x+300,settings_screen.y+300,270,50};

void graphic_slider(string label, Rectangle slider, float &parameter, float min, float max){
   string text;
   parameter = DrawSlider(slider, min, max, parameter, 3);
   DrawRectangleLinesEx(slider, 3, primaryColor);
   text = label+ " " + floatToString(Enround(parameter/max * 100, 1)) + "%";
   DrawTextC(text.c_str(), slider.x-280, slider.y+5, 20, primaryColor);
};

void HandleSetShader(){
    graphic_slider("CURVATURE", curvature_slider, curvature, 0.00, 0.07);
    graphic_slider("BLOOM", bloomIntensity_slider, bloomIntensity, 0.00, 2.3);
    graphic_slider("GLOW", glowIntensity_slider, glowIntensity, 0.00, 1.5);
    graphic_slider("SCANLINES", scanlineIntensity_slider, scanlineIntensity, 0.00, 1.0);
    graphic_slider("BRIGHTNESS", brightness_slider, brightness, 0.00, 1.4);

    multiple_choice("SHADER INTENSITY" ,shader_quality_frame, "LOW", "MID", "HI", mousePos, shaderQuality);

};