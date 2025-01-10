#include "headers/data_update.h"
#include "headers/data_draw.h"
#include "headers/settings_update.h"
#include "managers/FileSystemManager.h"

// declarations
void UpdateData();
void UpdateTutorial();
void UpdateRecovered();

bool tutorials_highl;
bool recovered_highl;

// tutorials buttons
bool ballgame_highl;
bool connectinggame_highl;
bool findergame_highl;
bool typegame_highl;

// recovered buttons
bool recovered1_highl;
bool recovered2_highl;
bool recovered3_highl;

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
            UpdateRecovered();
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

void UpdateRecovered() {
    
    if(CheckCollisionPointRec(mousePos, button_recovered1)==true){
        recovered1_highl = true;
        if (fsm.isDifficultyCompleted(2)){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentRecovered = R1;
                recovered1_highl = false;
            }
        }
    } else recovered1_highl = false;

    if(CheckCollisionPointRec(mousePos, button_recovered2)==true){
        recovered2_highl = true;
        if (fsm.isDifficultyCompleted(3)){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentRecovered = R2;
                recovered2_highl = false;
            }
        }
    } else recovered2_highl = false;

    if(CheckCollisionPointRec(mousePos, button_recovered3)==true){
        recovered3_highl = true;
        if (fsm.difficulty3Completed){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentRecovered = R3;
                recovered3_highl = false;
            }
        }
    } else recovered3_highl = false;

    switch (currentRecovered) {
        case R0: break;
        case R1: {
            recovered1_highl = true;
        } break;
        case R2: {
            recovered2_highl = true;
        } break;
        case R3: {
            recovered3_highl = true;
        } break;
        default: break;
    }
}

