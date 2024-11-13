#include "headers/gameplay_draw.h"
#include "headers/globals.h"  // Wczytanie zmiennych globalnych, jeśli są potrzebne
#include <string>

void DrawGameplay(Rectangle textBox, const char* command, int letterCount, bool mouseOnText, int framesCounter, std::string* historyDrawn) {
    ClearBackground(BLACK);

    //Monitor
    DrawRectangleLinesEx(screen, 3, ORANGE);
    
    //Labels
        //TopWindow
    DrawRectangle(screenWidth-450, 25, 100, 15, ORANGE);
    DrawTextC("desktop.frm", screenWidth-445, 22, 20, BLACK);
        //BotWindow
    DrawRectangle(screenWidth-450, (float)(screenHeight/2)+5, 100, 15, ORANGE);
    DrawTextC("   csnl.frm", screenWidth-445, (float)(screenHeight/2)+2, 20, BLACK);   
        //RightWindow
    DrawRectangle(screenWidth-150, 25, 100, 15, ORANGE);
    DrawTextC(" pidmgr.frm", screenWidth-145, 22, 20, BLACK);
        //Sysinfo
    DrawTextC("paradisiOS ver 7.3, up to date.", 5, 2, 20, WHITE);          

    //Horizontal lines
    DrawLineEx((Vector2){50, (float)(screenHeight/2)+5}, (Vector2){(float)screenWidth-350, (float)(screenHeight/2)+5}, 3, ORANGE); 
    DrawLineEx((Vector2){50, (float)(screenHeight/2)-5}, (Vector2){(float)screenWidth-350, (float)(screenHeight/2)-5}, 3, ORANGE);

    //Vertical lines
    DrawLineEx((Vector2){(float)screenWidth-350, 25}, (Vector2){(float)screenWidth-350, (float)(screenHeight/2)-5}, 3, ORANGE);
    DrawLineEx((Vector2){(float)screenWidth-350, (float)(screenHeight/2)+5}, (Vector2){(float)screenWidth-350, (float)screenHeight-25}, 3, ORANGE);
    DrawLineEx((Vector2){(float)screenWidth-340, 25}, (Vector2){(float)screenWidth-340, (float)screenHeight-25}, 3, ORANGE);

    //Terminal Input
    DrawText(">", 55, screenHeight-50, 20, ORANGE);
    DrawTextB(command, 65, screenHeight-50, 20, ORANGE);
    if (letterCount < 99 && ((framesCounter / 20) % 2) == 0) {
        //Draw "_" if frames/20%2=0 (blinking) - measure text with exact spacing for the font.
        DrawText("_", 65 + 4 + MeasureTextEx(alagard, command, 20, 2).x, screenHeight-50, 20, ORANGE);
    }

    //Terminal Output
    for(int i = 0; i<15; i++){
        DrawTextB(historyDrawn[i].c_str(), 55, screenHeight-70-(i*20), 20, ORANGE);
    }
    
}
