#include "../headers/settings_vars.h"

using namespace std;

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

Color displayColor;

SettingState shaderQuality = LOW;

//Slider drawing
float DrawSlider(Rectangle sliderRect, float minValue, float maxValue, float value, int position) {
    // Position handler
    float knobX = sliderRect.x + (value - minValue) / (maxValue - minValue) * sliderRect.width;
    Rectangle knobRect = { knobX - 10, sliderRect.y - 5, 20, sliderRect.height + 10 };

    // Slider draw
    DrawRectangleRec(sliderRect, BLACK); // Background
    DrawRectangle(sliderRect.x, sliderRect.y, knobX - sliderRect.x, sliderRect.height, primaryColor); // Infill
    DrawRectangleRec(knobRect, primaryColor); // Knob

    // Mouse handler
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
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
    DrawRectangleLinesEx(frame, 3, primaryColor);
    DrawLineEx({frame.x+(frame.width/3), frame.y}, {frame.x+(frame.width/3), frame.y+frame.height}, 3, primaryColor);
    DrawLineEx({frame.x+((frame.width/3)*2), frame.y}, {frame.x+((frame.width/3)*2), frame.y+frame.height}, 3, primaryColor);
    //LEFT BUTTON
    multiple_choice_button(0, frame, left, mousePos, setting, LOW);
    // MID BUTTON
    multiple_choice_button(1, frame, mid, mousePos, setting, MID);
    // RIGHT BUTTON
    multiple_choice_button(2, frame, right, mousePos, setting, HI);
};

void LoadSettingsDefault(){
    master_volume = 0.5;
    music_volume = 1.0;
    sfx_volume = 1.0;
    shaderQuality = LOW;
    primaryColor = ORANGE;
    curvature = 0.07f;
    bloomIntensity = 2.3f;
    glowIntensity = 1.5f;
    scanlineIntensity = 1.0f;
    brightness = 1.4f;
    sh_resolution = {800, 600}; // Add this line to set default resolution
    displayColor = ORANGE; // Ensure displayColor is set to a default value
}