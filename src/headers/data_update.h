#ifndef DATA_UPDATE_H
#define DATA_UPDATE_H

#include "globals.h"
#include "raylib.h"

extern bool tutorials_highl;
extern bool recovered_highl;

// tutorial buttons
extern bool ballgame_highl;
extern bool connectinggame_highl;
extern bool findergame_highl;
extern bool typegame_highl;

void UpdateData();
void UpdateTutorial();

#endif