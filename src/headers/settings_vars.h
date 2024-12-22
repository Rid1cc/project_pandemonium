#ifndef SETTINGS_VARS_H
#define SETTINGS_VARS_H

#include "raylib.h"
#include "globals.h"

extern bool graph_highl;
extern bool audio_highl;
extern bool display_highl;
extern bool custom_highl;
extern bool return_highl;
extern bool apply_highl;
extern bool restore_highl;
extern Rectangle button_graphic ;
extern Rectangle button_audio ;
extern Rectangle button_display ;
extern Rectangle button_custom ;
extern Rectangle settings_screen ;
extern Rectangle settings_desc;
extern Rectangle button_return;
extern Rectangle button_restore;
extern Rectangle button_apply;
extern Color displayColor; 

extern float master_volume;
extern float music_volume;
extern float sfx_volume;

extern SettingState shaderQuality;

float DrawSlider(Rectangle sliderRect, float minValue, float maxValue, float value, int position);
std::string floatToString(float num);

#endif // SETTINGS_VARS_H