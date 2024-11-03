#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#define MAX_INPUT_CHARS 9

// Definicja typu wyliczeniowego GameScreen
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

// Deklaracja zmiennej globalnej currentScreen
extern GameScreen currentScreen;

#endif // GAMESCREEN_H