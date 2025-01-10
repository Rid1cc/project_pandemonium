#include "headers/data_draw.h"
#include "headers/data_update.h"
#include "headers/settings_update.h"
#include "managers/FileSystemManager.h"


// declarations
void DrawData();
void DataButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton, int xPos);
void DrawTutorials();
void DrawTutorialDescription(Rectangle rect, int FontSize, std::string text, Color color);
void DrawRecovered();
void DrawBlockedRecoveredButton(Rectangle rect, const char* text, int FontSize, bool isMouseOnButton, int xPos);

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

// Recovered buttons
Rectangle button_recovered1 = {100, float(screenHeight)-370, 270, 50};
Rectangle button_recovered2 = {100, float(screenHeight)-290, 270, 50};
Rectangle button_recovered3 = {100, float(screenHeight)-210, 270, 50};



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
    DrawTextB("Exorcist's", 100, float(screenHeight)-530, TutorialsButtonsFontSize, primaryColor);
    DrawTextB("handbook.", 100, float(screenHeight)-485, TutorialsButtonsFontSize, primaryColor);
    DrawTextB("Be prepared.", 100, float(screenHeight)-440, TutorialsButtonsFontSize, primaryColor);
    DataButton(button_BallGame, "PKG SPOOF", primaryColor, TutorialsButtonsFontSize, ballgame_highl, 100);
    DataButton(button_ConnectingGame, "SPLINTER-45", primaryColor, TutorialsButtonsFontSize, connectinggame_highl, 100);
    DataButton(button_FinderGame, "BACKDOOR", primaryColor, TutorialsButtonsFontSize, findergame_highl, 100);
    DataButton(button_TypeGame, "REG.HACK", primaryColor, TutorialsButtonsFontSize, typegame_highl, 100);

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

void DrawRecovered(){

    int RecoveredButtonsFontSize = 40;
    DrawTextB("Scrapped logs,", 100, float(screenHeight)-530, RecoveredButtonsFontSize, primaryColor);
    DrawTextB("recovered", 100, float(screenHeight)-485, RecoveredButtonsFontSize, primaryColor);
    DrawTextB("from battles", 100, float(screenHeight)-440, RecoveredButtonsFontSize, primaryColor);

    // description box
    Rectangle descriptionRect = {400, float(screenHeight) - 530, 780, 450};
    DrawRectangleRec(descriptionRect, BLACK);
    DrawRectangleLinesEx(descriptionRect, 3, primaryColor);

    if (fsm.isDifficultyCompleted(2)) {
        DataButton(button_recovered1, "RECOVERED 1", primaryColor, RecoveredButtonsFontSize, recovered1_highl, 100);
    } else {
        DrawBlockedRecoveredButton(button_recovered1, "RECOVERED 1", RecoveredButtonsFontSize, recovered1_highl, 100);
        if (recovered1_highl){
            DrawTextB("Come back after", 100, float(screenHeight)-130, 25, DARKGRAY);
            DrawTextB("beating EASY mode!", 100, float(screenHeight)-100, 25, DARKGRAY);
        }
    }

    if (fsm.isDifficultyCompleted(3)) {
        DataButton(button_recovered2, "RECOVERED 2", primaryColor, RecoveredButtonsFontSize, recovered2_highl, 100);
    } else {
        DrawBlockedRecoveredButton(button_recovered2, "RECOVERED 2", RecoveredButtonsFontSize, recovered2_highl, 100);
        if (recovered2_highl){
            DrawTextB("Come back after", 100, float(screenHeight)-130, 25, DARKGRAY);
            DrawTextB("beating NORMAL mode!", 100, float(screenHeight)-100, 25, DARKGRAY);
        }
    }

    if (fsm.difficulty3Completed) {
        DataButton(button_recovered3, "RECOVERED 3", primaryColor, RecoveredButtonsFontSize, recovered3_highl, 100);
    } else {
        DrawBlockedRecoveredButton(button_recovered3, "RECOVERED 3", RecoveredButtonsFontSize, recovered3_highl, 100);
        if (recovered3_highl){
            DrawTextB("Come back after", 100, float(screenHeight)-130, 25, DARKGRAY);
            DrawTextB("beating HARD mode!", 100, float(screenHeight)-100, 25, DARKGRAY);
        }
    }

    int DescriptionFontSize = 27;
    switch (currentRecovered) {
        case R0: break;
        case R1: {
            std::string description =
            "log:exorcist_001 04:09:10 01.02.1984\n"
            "------------------------------------\n"
            "I have been selected as the exorcist of my platoon.\n"
            "I was told that it was some kind of\n"
            "experimental type of hack service.... \n"
            "and that I would find out more already on duty.\n"
            "Strangely enough, they started forcibly selecting people\n"
            "to join the army just when news of this whole mega\n"
            "investment about drilling into the earth's interior stopped.\n"
            "\n"
            "I have a bad feeling about this... \n";
            DrawTutorialDescription(descriptionRect, DescriptionFontSize, description, primaryColor);
        } break;
        case R2: {
            std::string description =
            "log:exorcist_431 22:13:04 20.12.2001\n"
            "------------------------------------\n"
            "The war is slowly coming to an end, they have stopped\n"
            "sending “us” into hostile territory. Two of my platoon\n"
            "didn't return from the last expedition. To be honest,\n"
            "it doesn't feel good to sit in front of a a computer\n"
            "by myself and not risk my life on the battlefield.\n"
            "At least not like this - physically.\n"
            "Most of ours don't even know what they're fighting.\n"
            "They've been told it's just another rogue software leak.\n"
            "\n"
            "The barbarity...\n"
            "At least tell them what their deaths will look like...";
            DrawTutorialDescription(descriptionRect, DescriptionFontSize, description, primaryColor);
        } break;
        case R3: {
            std::string description =
            "Strictly confidential - information hazard\n"
            "------------------------------------\n"
            "The CEO of [Babel inc.] announces the freezing of\n"
            "excavation in (loc.). Reason: accident to a digging unit,\n"
            "loss of 1492 employees. Investigation led by IBP branch,\n"
            "only led to further loss of manpower.\n"
            "We seek government action immediately,\n"
            "possible risk of human extinction category.\n"
            "If action is taken - under no circumstances disclose\n"
            "details of the situation to anyone outside the facility.\n"
            "\n"
            "Babel inc. CEO, Joseph Nimrod\n"
            "loc. 51.1283757226213, 20.412782326273952";
            DrawTutorialDescription(descriptionRect, DescriptionFontSize, description, primaryColor);
        } break;
        default: break;
    }
}

void DrawBlockedRecoveredButton(Rectangle rect, const char* text, int FontSize, bool isMouseOnButton, int xPos){
    DrawRectangleRec(rect, BLACK);
    DrawRectangleLinesEx(rect, 5, DARKGRAY);
    DrawTextB(text, xPos + 10, rect.y + (rect.height - FontSize)/2, FontSize, DARKGRAY);
}


