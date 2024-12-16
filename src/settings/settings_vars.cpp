#include "../headers/globals.h"
#include <string>
#include <raylib.h>
#include "../headers/MiniGameManager.h"
#include "../headers/globals.h"

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

//Slider parameters
Rectangle sliderRect = { 300, 200, 200, 20 }; // Pos and sizes
float minValue = 0.0f;
float maxValue = 100.0f;
float currentValue = 50.0f; // Start value
bool isValueFinalized = false;


//Slider drawing
float DrawSlider(Rectangle sliderRect, float minValue, float maxValue, float value) {
    // Position handler
    float knobX = sliderRect.x + (value - minValue) / (maxValue - minValue) * sliderRect.width;
    Rectangle knobRect = { knobX - 10, sliderRect.y - 5, 20, sliderRect.height + 10 };

    // Rysowanie slidera
    DrawRectangleRec(sliderRect, BLACK); // Background
    DrawRectangle(sliderRect.x, sliderRect.y, knobX - sliderRect.x, sliderRect.height, ORANGE); // Infill
    DrawRectangleRec(knobRect, ORANGE); // Knob

    // Obsługa myszy
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, sliderRect) || CheckCollisionPointRec(mousePos, knobRect)) {
            // New value by mousePos
            float newValue = minValue + (mousePos.x - sliderRect.x) / sliderRect.width * (maxValue - minValue);
            value = Clamp(newValue, minValue, maxValue);
        }
    }
    return value;
}