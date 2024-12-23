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

void multiple_choice_button(float pos, Rectangle frame, string text, Vector2 &mousePos, SettingState &setting, SettingState state){
    if(CheckCollisionPointRec(mousePos, {frame.x+(pos*(frame.width/3)),frame.y,frame.width/3,frame.height})==true || setting == state){
        DrawRectangle(frame.x+(pos*(frame.width/3)),frame.y,frame.width/3,frame.height, primaryColor);
        DrawTextC(text.c_str(), frame.x+(pos*(frame.width/3))+((frame.width/3)-(frame.width/3)/2)-(MeasureTextEx(pixeled, text.c_str(), 30, 2).x)/2, frame.y+15, 30, BLACK);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true){
            setting = state;
        }
    } else DrawTextC(text.c_str(), frame.x+(pos*(frame.width/3))+((frame.width/3)-(frame.width/3)/2)-(MeasureTextEx(pixeled, text.c_str(), 30, 2).x)/2, frame.y+15, 30, primaryColor);
};

void multiple_choice(string label ,Rectangle frame, string left, string mid, string right, Vector2 &mousePos, SettingState &setting){
    DrawTextC(label.c_str(), frame.x-280, frame.y+15, 20, primaryColor);
    DrawRectangleLinesEx(shader_quality_frame, 3, primaryColor);
    DrawLineEx({frame.x+(frame.width/3), frame.y}, {frame.x+(frame.width/3), frame.y+frame.height}, 3, primaryColor);
    DrawLineEx({frame.x+((frame.width/3)*2), frame.y}, {frame.x+((frame.width/3)*2), frame.y+frame.height}, 3, primaryColor);
    //LEFT BUTTON
    multiple_choice_button(0, frame, left, mousePos, setting, LOW);
    // MID BUTTON
    multiple_choice_button(1, frame, mid, mousePos, setting, MID);
    // RIGHT BUTTON
    multiple_choice_button(2, frame, right, mousePos, setting, HI);
};

void HandleSetShader(){
    graphic_slider("CURVATURE", curvature_slider, curvature, 0.00, 0.07);
    graphic_slider("BLOOM", bloomIntensity_slider, bloomIntensity, 0.00, 2.3);
    graphic_slider("GLOW", glowIntensity_slider, glowIntensity, 0.00, 1.5);
    graphic_slider("SCANLINES", scanlineIntensity_slider, scanlineIntensity, 0.00, 1.0);
    graphic_slider("BRIGHTNESS", brightness_slider, brightness, 0.00, 1.4);

    multiple_choice("SHADER INTENSITY" ,shader_quality_frame, "LOW", "MID", "HI", mousePos, shaderQuality);

};