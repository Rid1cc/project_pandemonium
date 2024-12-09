#include "headers/title_update.h"
#include "headers/globals.h"
#include <cstdio>

bool play_highl;
bool settings_highl;
bool data_highl;
bool exit_highl;

void TitleUpdate() {

    //frames counter
    framesCounter ++;
    if(framesCounter>=60){
        framesCounter = 0;
    }

    //mouse pointer collision
    mousePos = GetMousePosition();

    //check if mouse over button
    
    //play
    if(CheckCollisionPointRec(mousePos, button_play)==true){
        printf("graj\n");
        play_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = GAMEPLAY;
            play_highl = false;
            }
    } else play_highl = false;
    
    //settings
    if(CheckCollisionPointRec(mousePos, button_settings)==true){
        printf("opcje\n");
        settings_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = SETTINGS;
            settings_highl = false;
            }
    } else settings_highl = false;

    //lore
    if(CheckCollisionPointRec(mousePos, button_lore)==true){
        printf("lore\n");
        data_highl = true;
    } else data_highl = false;

    //quit
    if(CheckCollisionPointRec(mousePos, button_exit)==true){
        printf("quit\n");
        exit_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            exitGame = true;
            }
    } else exit_highl = false;

}