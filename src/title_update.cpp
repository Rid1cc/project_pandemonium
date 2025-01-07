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

    //check if mouse over button
    
    //play
    if(CheckCollisionPointRec(mousePos, button_play)==true){
        play_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            gameplayManager.enemy.resetPlayer();
            gameplayManager.player.resetPlayer();
            currentScreen = DIFFICULTY_SELECTION;
            gameplayManager.gameplayInit();
            play_highl = false;
            }
    } else play_highl = false;
    
    //settings
    if(CheckCollisionPointRec(mousePos, button_settings)==true){
        settings_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = SETTINGS;
            settings_highl = false;
            }
    } else settings_highl = false;

    //lore
    if(CheckCollisionPointRec(mousePos, button_lore)==true){
        data_highl = true;
    } else data_highl = false;

    //quit
    if(CheckCollisionPointRec(mousePos, button_exit)==true){
        exit_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            exitGame = true;
            }
    } else exit_highl = false;

}