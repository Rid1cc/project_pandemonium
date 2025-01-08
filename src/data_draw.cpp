#include "headers/data_draw.h"
#include "headers/data_update.h"


// declarations
void DrawData();
void DataButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton, int xPos);
void DrawTutorials();
void DrawTutorialDescription(Rectangle rect, int FontSize, std::string text, Color color);
void DrawRecovered();


// buttons
float buttonWidth = 330.0f;
float Tx = screenWidth/4 - buttonWidth/2;
float Rx = screenWidth/4 + screenWidth/2 - buttonWidth/2;
Rectangle button_tutorials = {Tx, float(screenHeight)-655, buttonWidth, 75};
Rectangle button_recovered = {Rx, float(screenHeight)-655, buttonWidth, 75};

// tutorial buttons:
Rectangle button_BallGame = {100, float(screenHeight)-370, 270, 50};
Rectangle button_ConnectingGame = {100, float(screenHeight)-290, 270, 50};
Rectangle button_FinderGame = {100, float(screenHeight)-210, 270, 50};
Rectangle button_TypeGame = {100, float(screenHeight)-130, 270, 50};



// functions
void DrawData(){
    // borders
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawRectangleLinesEx(screen, 3, primaryColor);

    //Label
    DrawTextC("ParadisiOS ver 7.3, up to date.", 5, 2, 12, WHITE);

    int ButtonFontSize = 60;
    DataButton(button_tutorials, "TUTORIALS", primaryColor, ButtonFontSize, tutorials_highl, Tx);
    DataButton(button_recovered, "RECOVERED", primaryColor, ButtonFontSize, recovered_highl, Rx);

    switch (currentDataScreen) {
        case TUTORIALS: {
            DrawTutorials();
        } break;
        case RECOVERED: {
            DrawRecovered();
        } break;
    }
}

void DataButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton, int xPos){
    if (isMouseOnButton){
        DrawRectangleRec(rect, color);
        DrawRectangleLinesEx(rect, 3, BLACK);
        DrawTextB(text, ShakeXY((float)(xPos + 10), 1.5), ShakeXY((float)rect.y + (rect.height - FontSize)/2, 1.5), FontSize, BLACK);
    } else {
        DrawRectangleRec(rect, BLACK);
        DrawRectangleLinesEx(rect, 3, color);
        DrawTextB(text, xPos + 10, rect.y + (rect.height - FontSize)/2, FontSize, color);
    }
}

void DrawTutorials(){
    int TutorialsButtonsFontSize = 40;
    DrawTextB("Hackers are", 100, float(screenHeight)-530, TutorialsButtonsFontSize, primaryColor);
    DrawTextB("coming!", 100, float(screenHeight)-485, TutorialsButtonsFontSize, primaryColor);
    DrawTextB("Get ready!", 100, float(screenHeight)-440, TutorialsButtonsFontSize, primaryColor);
    DataButton(button_BallGame, "BALL GAME", primaryColor, TutorialsButtonsFontSize, ballgame_highl, 100);
    DataButton(button_ConnectingGame, "RJ-45 GAME", primaryColor, TutorialsButtonsFontSize, connectinggame_highl, 100);
    DataButton(button_FinderGame, "FINDER GAME", primaryColor, TutorialsButtonsFontSize, findergame_highl, 100);
    DataButton(button_TypeGame, "TYPE GAME", primaryColor, TutorialsButtonsFontSize, typegame_highl, 100);

    Rectangle descriptionRect = {400, float(screenHeight) - 530, 780, 450};
    DrawRectangleRec(descriptionRect, BLACK);
    DrawRectangleLinesEx(descriptionRect, 3, primaryColor);
    int DescriptionFontSize = 27;

    switch (currentTutorial) {
        case BALL: {
            std::string BallGameDescription = 
            "Can you outsmart the firewalls?\n"
            "\n"
            "In this minigame, your mission is to guide the ball\n"
            "to the right side of the window without touching\n"
            "any moving blocks.\n"
            "Think of those blocks as pesky firewalls\n"
            "trying to block your escape!\n"
            "Control the ball using the arrow keys on your keyboard.\n"
            "To win, you will need to succeed three times in a row,\n"
            "but beware!\n"
            "The challenge ramps up with each round.\n"
            "\n"
            "Finish before time runs out, or risk being hacked!";
            DrawTutorialDescription(descriptionRect, DescriptionFontSize, BallGameDescription, primaryColor);
        } break;
        case CONNECTING: {
            std::string ConnectingGameDescription = 
            "Wiring up your defenses!\n"
            "\n"
            "Time to wire an RJ-45 plug!\n"
            "Connect the wires on the right according to the\n"
            "T-568B standard - the hacker's go-to method.\n"
            "Here's the cheat sheet:\n"
            "1. White-Orange  2. Orange  3. White-Green  4. Blue\n"
            "5. White-Blue    6. Green   7. White-Brown  8. Brown\n"
            "Drag and drop connectors to match the order.\n"
            "Wrong connections might short-circuit!\n"
            "\n"
            "Hurry - time's ticking,\n"
            "don't leave your defenses unplugged!";
            DrawTutorialDescription(descriptionRect, DescriptionFontSize, ConnectingGameDescription, primaryColor);
        } break;
        case FINDER: {
            std::string FinderGameDescription = 
            "Find the leaks before the hackers do!\n"
            "\n"
            "Move the window around to uncover hidden messages.\n"
            "Click on the \"good\" ones to collect points,\n"
            "but steer clear of the \"bad\" ones - those will\n"
            "cost you dearly!"
            "\n"
            "Your goal? Snag 10 good messages to win,\n"
            "but be quick – the hackers won't wait forever!\n"
            "\n"
            "Stay sharp, and finish before time runs out!";
            DrawTutorialDescription(descriptionRect, DescriptionFontSize, FinderGameDescription, primaryColor);
        } break;
        case TYPE: {
            std::string TypeGameDescription =
            "Type like your system depends on it!\n"
            "\n"
            "This is a speed and accuracy test for the ultimate\n"
            "keyboard warrior.\n"
            "Type the text displayed on-screen as quickly as\n"
            "possible, but here's the catch:\n"
            "you need 100\% accuracy to succeed.\n"
            "One typo, and the hackers are in!\n"
            "\n"
            "Prove your skills before the clock hits zero,\n"
            "or it's game over!";
            DrawTutorialDescription(descriptionRect, DescriptionFontSize, TypeGameDescription, primaryColor);
        } break;
        default: break;
    }
}

void DrawTutorialDescription(Rectangle rect, int FontSize, std::string text, Color color){
    int LineHeight = FontSize + 5;
    int xStart = rect.x + 10;
    int yStart = rect.y + 10;

    std::istringstream textStream(text);
    std::string line;
    std::string currentLine = "";

    while(std::getline(textStream, line)){
        DrawTextB(line.c_str(), xStart, yStart, FontSize, color);
        yStart += LineHeight;
    }
}

// void DrawRecovered(){

// }


