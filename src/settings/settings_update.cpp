#include "../headers/settings_update.h"
#include "../headers/globals.h"
#include <raylib.h>
#include "../headers/settings_vars.h"
#include "../headers/shader_handler.h"

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

    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;

        //frames counter
    framesCounter ++;
    if(framesCounter>=60){
        framesCounter = 0;
    }

    //mouse pointer collision
    mousePos = GetMousePosition();
 
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
        printf("powrot\n");
        return_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = TITLE;
            return_highl = false;
            }
    } else return_highl = false;

    //apply
    if(CheckCollisionPointRec(mousePos, button_apply)==true){
        printf("apply\n");
        apply_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ReloadShader();
            }
    } else apply_highl = false;

    //restore
    if(CheckCollisionPointRec(mousePos, button_restore)==true){
        printf("restore\n");
        restore_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            restore_highl = false;
            }
    } else restore_highl = false;
}

