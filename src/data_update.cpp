#include "headers/data_update.h"
#include "headers/data_draw.h"

// declarations
void UpdateData();
void UpdateTutorial();

bool tutorials_highl;
bool recovered_highl;

// tutorials buttons
bool ballgame_highl;
bool connectinggame_highl;
bool findergame_highl;
bool typegame_highl;

// functions

void UpdateData(){
    // escape handle
    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;

    // if highlighted
    if(CheckCollisionPointRec(mousePos, button_tutorials)==true){
        tutorials_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentDataScreen = TUTORIALS;
            tutorials_highl = false;
            }
    } else tutorials_highl = false;

    if(CheckCollisionPointRec(mousePos, button_recovered)==true){
        recovered_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentDataScreen = RECOVERED;
            recovered_highl = false;
            }
    } else recovered_highl = false;

    switch (currentDataScreen) {
        case TUTORIALS: {
            tutorials_highl = true;
            UpdateTutorial();
        } break;
        case RECOVERED: {
            recovered_highl = true;
        } break;
        default: break;
    }
}

void UpdateTutorial() {
    if(CheckCollisionPointRec(mousePos, button_BallGame)==true){
        ballgame_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentTutorial = BALL;
            ballgame_highl = false;
            }
    } else ballgame_highl = false;

    if(CheckCollisionPointRec(mousePos, button_ConnectingGame)==true){
        connectinggame_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentTutorial = CONNECTING;
            connectinggame_highl = false;
            }
    } else connectinggame_highl = false;

    if(CheckCollisionPointRec(mousePos, button_FinderGame)==true){
        findergame_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentTutorial = FINDER;
            findergame_highl = false;
            }
    } else findergame_highl = false;

    if(CheckCollisionPointRec(mousePos, button_TypeGame)==true){
        typegame_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentTutorial = TYPE;
            typegame_highl = false;
            }
    } else typegame_highl = false;

    switch (currentTutorial){
        case BALL: {
            ballgame_highl = true;
        } break;
        case CONNECTING: {
            connectinggame_highl = true;
        } break;
        case FINDER: {
            findergame_highl = true;
        } break;
        case TYPE: {
            typegame_highl = true;
        } break;
        default: break;
    }

}
