#ifndef DIFFICULTY_SELECTOR_H
#define DIFFICULTY_SELECTOR_H

#include "globals.h"
#include "raylib.h"
#include <sstream>
#include <string>
#include <fstream>
#include "json.hpp"

// MAX DIFFICULTY FUNCTIONS
void SaveMaxDifficulty(int maxDifficulty); // saving new level
int LoadMaxDifficulty(); // return max level unlocked
void DifficultyCompleted(int difficulty); // saving new max difficulty
bool isDifficultyCompleted(int difficulty); // return true if it is 

// other
void DrawDifficultySelection();
bool isMouseOnButton(Rectangle rect);
void DrawDifficultyButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton);
void UpdateDifficultySelection();
void DrawDescription(Rectangle rect, int FontSize, std::string text, Color color);
void DrawBlockedButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton);

//int SelectedDifficulty; // difficulty selected by the player




#endif 