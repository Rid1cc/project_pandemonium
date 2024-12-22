#include "headers/gameplay_draw.h"
#include "headers/globals.h"  // Wczytanie zmiennych globalnych, jeśli są potrzebne
#include <string>

void DrawGameplay(Rectangle textBox, const char* command, int letterCount, bool mouseOnText, int framesCounter, std::string* historyDrawn) {
    ClearBackground(BLACK);

    //Monitor
    DrawRectangleLinesEx(screen, 3, primaryColor);
    
    //Labels
        //TopWindow
    DrawRectangle(screenWidth-450, 25, 100, 15, primaryColor);
    DrawTextC("DESKTP.SH", screenWidth-445, 28, 12, BLACK);
        //BotWindow
    DrawRectangle(screenWidth-450, (float)(screenHeight/2)+5, 100, 15, primaryColor);
    DrawTextC("CONSL.SH", screenWidth-445, (float)(screenHeight/2)+8, 12, BLACK);   
        //RightWindow
    DrawRectangle(screenWidth-150, 25, 100, 15, primaryColor);
    DrawTextC("PIDMGR.SH", screenWidth-145, 28, 12, BLACK);
        //Sysinfo
    DrawTextC("ParadisiOS ver 7.3, up to date.", 5, 2, 12, WHITE);          

    //Horizontal lines
    DrawLineEx((Vector2){50, (float)(screenHeight/2)+5}, (Vector2){(float)screenWidth-350, (float)(screenHeight/2)+5}, 3, primaryColor); 
    DrawLineEx((Vector2){50, (float)(screenHeight/2)-5}, (Vector2){(float)screenWidth-350, (float)(screenHeight/2)-5}, 3, primaryColor);

    //Vertical lines
    DrawLineEx((Vector2){(float)screenWidth-350, 25}, (Vector2){(float)screenWidth-350, (float)(screenHeight/2)-5}, 3, primaryColor);
    DrawLineEx((Vector2){(float)screenWidth-350, (float)(screenHeight/2)+5}, (Vector2){(float)screenWidth-350, (float)screenHeight-25}, 3, primaryColor);
    DrawLineEx((Vector2){(float)screenWidth-340, 25}, (Vector2){(float)screenWidth-340, (float)screenHeight-25}, 3, primaryColor);

    //Terminal Input
    DrawText(">", 55, GetScreenHeight()-50, 20, primaryColor);
    DrawTextB(command, 65, GetScreenHeight()-50, 20, primaryColor);
    if (letterCount < 99 && ((framesCounter / 20) % 2) == 0) {
        //Draw "_" if frames/20%2=0 (blinking) - measure text with exact spacing for the font.
        DrawTextB("_", 65 + 4 + MeasureTextEx(alagard, command, 20, 2).x, GetScreenHeight()-50, 20, primaryColor);
    }

    //Terminal Output
    for(int i = 0; i<15; i++){
        DrawTextB(historyDrawn[i].c_str(), 55, GetScreenHeight()-70-(i*20), 20, primaryColor);
    }
    
    gameManager.Draw();
}
