#include "../headers/settings_update.h"
#include "../headers/globals.h"
#include <raylib.h>
#include "../headers/settings_vars.h"
#include "../headers/shader_handler.h"

FileSystemManager fsm;

void sc_switcher(Vector2 &mousePos, Rectangle button, bool &highlight, enum SettingsScreen parseToScreen){
    if(CheckCollisionPointRec(mousePos, button)==true){
        highlight = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentSettings = parseToScreen;
            highlight = true;
            }
    } else if (currentSettings != parseToScreen )highlight = false;
}

void SettingsUpdate(float& general_volume, float& effects_volume, bool& mute_audio) {

    //Return on escape
    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;

        //frames counter
    framesCounter ++;
    if(framesCounter>=60){
        framesCounter = 0;
    }
 
    //Highlight Inhibitor
    switch (currentSettings) {
            case GRAPHICS: {
                graph_highl = true;
            } break;
            case AUDIO: {
                audio_highl = true;
            } break;
            case DISPLAY: {
                display_highl = true;
            } break;
            case CUSTOM: {
                custom_highl = true;
            } break;
            default: break;
        }
    
    //Buttons
    sc_switcher(mousePos, button_graphic, graph_highl, GRAPHICS);
    sc_switcher(mousePos, button_audio, audio_highl, AUDIO);
    sc_switcher(mousePos, button_display, display_highl, DISPLAY);
    sc_switcher(mousePos, button_custom, custom_highl, CUSTOM);

    //return
    if(CheckCollisionPointRec(mousePos, button_return)==true){
        return_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = TITLE;
            return_highl = false;
            }
    } else return_highl = false;

    //apply
    if(CheckCollisionPointRec(mousePos, button_apply)==true && (glowIntensity > 0.05f || brightness > 0.05f)){
        apply_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            switch (shaderQuality) {
                case LOW: {
                    sh_resolution = {854,480};
                } break;
                case MID: {
                    sh_resolution = {1280,720};
                } break;
                case HI: {
                    sh_resolution = {1600,900};
                } break;
                default: break;
            }
            primaryColor = displayColor; // Ensure primaryColor is set to displayColor
            fsm.saveSettings((configPath + "settings.json").c_str());
            ReloadShader(); 
        }
    } else apply_highl = false;

    //restore
    if(CheckCollisionPointRec(mousePos, button_restore)==true){
        restore_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            restore_highl = false;
            LoadSettingsDefault();
            ReloadShader();
            }
    } else restore_highl = false;
}

