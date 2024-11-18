#include "headers/title_update.h"
#include "headers/globals.h"


void TitleUpdate() {
    if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
    if (IsKeyPressed(KEY_S)) currentScreen = SETTINGS;
}