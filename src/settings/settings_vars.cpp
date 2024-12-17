#include <string>
#include <raylib.h>
#include "../headers/MiniGameManager.h"
#include "../headers/globals.h"
#include <iostream>
#include <sstream>
#include <string>

bool graph_highl;
bool audio_highl;
bool display_highl;
bool custom_highl;
bool return_highl;
bool restore_highl;
bool apply_highl;

Rectangle button_graphic = {100, float(screenHeight)-370, 200, 50};
Rectangle button_audio = {100, float(screenHeight)-290, 200, 50};
Rectangle button_display = {100, float(screenHeight)-210, 200, 50};
Rectangle button_custom = {100, float(screenHeight)-130, 200, 50};
Rectangle button_return = {980, float(screenHeight)-130, 200, 50};
Rectangle button_apply = {980, float(screenHeight)-210, 200, 50};
Rectangle button_restore = {980, float(screenHeight)-290, 200, 50};
Rectangle settings_screen = {340, 60, 600, 580};
Rectangle settings_desc = {100, 60, 200, 260};

float master_volume = 0.5;
float music_volume = 1.0;
float sfx_volume = 1.0;

//Slider drawing
float DrawSlider(Rectangle sliderRect, float minValue, float maxValue, float value, int position) {
    // Position handler
    float knobX = sliderRect.x + (value - minValue) / (maxValue - minValue) * sliderRect.width;
    Rectangle knobRect = { knobX - 10, sliderRect.y - 5, 20, sliderRect.height + 10 };

    // Slider draw
    DrawRectangleRec(sliderRect, BLACK); // Background
    DrawRectangle(sliderRect.x, sliderRect.y, knobX - sliderRect.x, sliderRect.height, ORANGE); // Infill
    DrawRectangleRec(knobRect, ORANGE); // Knob

    // Mouse handler
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, sliderRect) || CheckCollisionPointRec(mousePos, knobRect)) {
            // New value by mousePos
            float newValue = minValue + (mousePos.x - sliderRect.x) / sliderRect.width * (maxValue - minValue);
            value = Clamp(newValue, minValue, maxValue);
        }
    }
    return Enround(value, position);
}

//custom float to string (removing additional 0s)
std::string floatToString(float num) {
    std::ostringstream oss;
    oss << num; 
    return oss.str(); 
}