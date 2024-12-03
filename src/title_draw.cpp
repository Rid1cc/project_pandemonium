#include "headers/title_draw.h"
#include "headers/globals.h"
#include <random>
#include <chrono>
#include <cstdio>

Rectangle title = {float(screenWidth/5), float(screenHeight/9), float((screenWidth/5)*3), float((screenHeight/9)*1.4)};
Rectangle button_exit ={100, float(screenHeight)-130, 200, 50};
Rectangle button_lore ={100, float(screenHeight)-210, 200, 50};
Rectangle button_settings ={100, float(screenHeight)-290, 200, 50};
Rectangle button_play ={100, float(screenHeight)-370, 200, 50};


void DrawTitle() {
    //Particle randomizer
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());


    // drawing backgrounds
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawRectangleLinesEx(screen, 3, ORANGE);

    //Title
    DrawTextB("PANDEMONIUM", screenWidth/4, screenHeight/8, 100, ORANGE);
    DrawRectangleLinesEx(title, 5, ORANGE);

    //Buttons
    //Exit
    DrawRectangleLinesEx(button_exit, 3, ORANGE);
    DrawTextB("QUIT", 110, float(screenHeight)-125, 40, ORANGE);

    //Lore
    DrawRectangleLinesEx(button_lore, 3, ORANGE);
    DrawTextB("DATA", 110, float(screenHeight)-205, 40, ORANGE);

    //Settings
    DrawRectangleLinesEx(button_settings, 3, ORANGE);
    DrawTextB("SETTINGS", 110, float(screenHeight)-285, 40, ORANGE);

    //Play
    DrawRectangleLinesEx(button_play, 3, ORANGE);
    DrawTextB("MISSIONS", 110, float(screenHeight)-365, 40, ORANGE);

    //Particles
    int randomW;
    int randomH;
    if(framesCounter%3==0){
        for(int i =0; i<=20; i++){
            std::uniform_int_distribution<int> rW(50, screenWidth-100);
            std::uniform_int_distribution<int> rH(25, screenHeight-50);
            randomW = rW(rng);
            randomH = rH(rng);
            DrawText("-", randomW, randomH, 10, ORANGE);
        }
    }

}
