#include "headers/title_update.h"
#include "headers/globals.h"
#include <cstdio>


void TitleUpdate() {
    if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
    if (IsKeyPressed(KEY_S)) currentScreen = SETTINGS;

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
    }
    
    //settings
    if(CheckCollisionPointRec(mousePos, button_settings)==true){
        printf("opcje\n");
    }

    //lore
    if(CheckCollisionPointRec(mousePos, button_lore)==true){
        printf("lore\n");
    }

    //quit
    if(CheckCollisionPointRec(mousePos, button_exit)==true){
        printf("quit\n");
    }

}