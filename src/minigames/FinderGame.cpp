#include "FinderGame.h"

FinderGame::FinderGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), scissorMode(true){

    isFinderWin = false;
    currentScreen = MENU; // MENU, GAMEPLAY i END
    panel = { 100, 100, 1100, 400 }; // window dimensions with instructions and start
    startButton = { panel.x + (panel.width - 200) / 2, panel.y + panel.height - 80, 200, 50 }; // start button

    // green and red texts
    goodObjects = {
        "if(passwordCorrect) { accessGranted(); }",
        "connectionEstablished();",
        "printf(\"Access Granted\");",
        "encryptionKeyFound = true;",
        "No errors found",
        "[Build successful]",
        "[OK]",
        "secureConnection();",
        "dataEncrypted();",
        "safeModeActivated();",
        "protectedByFirewall = true;",
        "[Server running smoothly...]",
        "\"Success is just one step away!\"",
        "\"You're in control!\"",
    };
    badObjects = {
        "Error: Cannot establish connection",
        "syntaxError: unexpected token",
        "Access denied!",
        "File not found!",
        "TrojanDetected();",
        "[HACK ALERT]",
        "virus.exe ",
        "Warning: Firewall breach!",
        "Critical Error!",
        "Memory leak detected.",
        "Unstable connection.",
        "Blue Screen of Death",
        "[!] SYSTEM FAILURE",
        "!!! DO NOT CLICK !!!",
        "\"You're too slow!\"",
        "\"404: Success not found.\"",
        "404_brain_not_found;",
        "password=\"1234\";"
    };

    // isGameStarted = false;
    timer = 31; // time of the game
    lastUpdateTime = 0.0f; // a variable that helps with the timer
    
    collected = 0; // score (collected pop ups texts)

    endScreenStartTime = 0.0;

    GenerateRandomObjects(); // generating once before start 
}


void FinderGame::Update() {
    switch (FinderGame::currentScreen) {
        case MENU:
            StartButton();
            break;
        case GAMEPLAY:
            MiniGame::Update(); // Hangle dragging

            // switch scissor mode (key 'S')
            if (IsKeyPressed(KEY_S)) {
                scissorMode = !scissorMode;
            }

            // scissorArea will follow window
            scissorArea = window;

            // countdown timer
            currentTime = GetTime();
            if (currentTime - lastUpdateTime >= 1.0f) { // Co 1 sekundę
                lastUpdateTime = currentTime;
                if (timer > 0) {
                    timer--; // we reduce the time counter
                }
            }

            // scoring points for clicking the text
            if (IfTextClicked(good)){
                collected++;
                GenerateRandomObjects();
            } 
            if (IfTextClicked(bad)){
                collected--;
                GenerateRandomObjects();
            }

            // LOSE 
            if (timer <=0){
                isFinderWin = false;
                currentScreen = END; // go to end
                endScreenStartTime = GetTime();
            }
            
            // WIN
            if (collected == 10){
                isFinderWin = true;
                currentScreen = END; // go to end
                endScreenStartTime = GetTime();
            }
            break;
        case END:
            if (GetTime() - endScreenStartTime >= 3.0) {
                MiniGame::Close();
            }
            break;

    }
    
}

void FinderGame::Draw() {
    switch (FinderGame::currentScreen) {
        case MENU:
            DrawStartScreen();
            break;
        case GAMEPLAY:
            MiniGame::Draw(); // draw window
            DrawTextB("Collect 10 positive messages (green!)", window.x + 10, window.y + 40, 20, ORANGE); // draw game instruction

            // draw collected counter
            // collectedText = "Collected: " + std::to_string(collected);
            // DrawText(collectedText.c_str(), window.x + 10, window.y + 80, 20, ORANGE);
            DrawTextB("Collected: ", window.x + 10, window.y + 80, 20, ORANGE);
            DrawTextB(std::to_string(collected).c_str(), window.x + 130, window.y + 80, 20, WHITE);

            // draw timer
            // timerText = "Time left: " + std::to_string(timer) + "s";
            // DrawText(timerText.c_str(), window.x + 10, window.y + 120, 20, ORANGE);
            DrawTextB("Time left: ", window.x + 10, window.y + 120, 20, ORANGE);
            DrawTextB((std::to_string(timer) + "s").c_str(), window.x + 120, window.y + 120, 20, RED);

            // IF CAN BE DELETED IN THE FUTURE!!!!
            if (scissorMode) {
                BeginScissorMode((int)scissorArea.x, (int)scissorArea.y, (int)scissorArea.width, (int)scissorArea.height);
            } // Begin Scissor Mode 

            // draw good and bad texts
            DrawTextB(good.text.c_str(),  good.x, good.y, 20, GREEN);
            DrawTextB(bad.text.c_str(), bad.x, bad.y, 20, RED);

            if (scissorMode) {
                EndScissorMode();
            } // IF CAN BE DELETED IN THE FUTURE!!!!

            break;
         case END:
            DrawEndScreen(isFinderWin); 
            break;
    }

}

void FinderGame::DrawStartScreen(){
    const char* message = 
        "Move the window to uncover hidden texts.\n"
        "Click on good messages to collect them, but watch out - clicking on a bad one will cost you a point!\n"
        "Your Goal? Collect 10 good messages in 30 seconds!\n\n"
        "Are you ready? Good luck!";

    // window cords
    DrawRectangleRec(panel, BLACK);                    // Background
    DrawRectangleLinesEx(panel, 10, GOLD); 

    const char* header = "Welcome to Finder!";
    int headerFontSize = 40;
    int headerWidth = MeasureText(header, headerFontSize);
    DrawTextB(header, 
             panel.x + (panel.width - headerWidth) / 2, // horizontal centering
             panel.y + 30,                              // distance from the top
             headerFontSize, 
             YELLOW);

    int messageFontSize = 20;
    int messageLineHeight = messageFontSize + 5; // line height with spacing
    int messageY = panel.y + 100;               // text start position

    // Podziel tekst na linie i wyświetl go w prostokącie
    std::istringstream messageStream(message);
    std::string line;
    int lineNum = 0;
    while (std::getline(messageStream, line)) {
        int lineWidth = MeasureText(line.c_str(), messageFontSize);
        DrawTextB(line.c_str(), 
                 panel.x + (panel.width - lineWidth) / 2, // Wyśrodkowanie poziome
                 messageY + lineNum * messageLineHeight, // Odstęp pionowy
                 messageFontSize, 
                 RAYWHITE);
        lineNum++;
    }   

    //START BUTTON
    DrawRectangleRec(startButton, ORANGE);
    DrawRectangleLinesEx(startButton, 3, WHITE);
    DrawTextB("START", 
             startButton.x + (startButton.width - MeasureText("START", 25)) / 2, 
             startButton.y + (startButton.height - 25) / 2, 25, WHITE);
}

void FinderGame::StartButton(){
    // start button click
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, startButton)) {
            currentScreen = GAMEPLAY; // chanche game state to GAMEPLAY
        }
    }
}

void FinderGame::GenerateRandomObjects(){
    good.text = goodObjects[GetRandomValue(0, goodObjects.size() - 1)];
    bad.text = badObjects[GetRandomValue(0, badObjects.size() - 1)];

    // gets the width of text to ensure that text will be in game window
    int goodTextWidth = MeasureText(good.text.c_str(), 20);
    int goodTextHeight = 20;
    int badTextWidth = MeasureText(bad.text.c_str(), 20);
    int badTextHeight = 20;

    auto isOutOfScissorArea = [](RandomObject& obj, Rectangle scissorArea) -> bool {
        int TextWidth = MeasureText(obj.text.c_str(), 20);
        int TextHeight = 20;

        return (obj.x + TextWidth < scissorArea.x || obj.x > scissorArea.x + scissorArea.width) &&
                (obj.y + TextHeight < scissorArea.y || obj.y > scissorArea.y + scissorArea.height);
    };

    do{
        good.x = GetRandomValue(0, GetScreenWidth() - goodTextWidth);
        good.y = GetRandomValue(0, GetScreenHeight() - 20); // -20, because of height of text
    } while (!isOutOfScissorArea(good, window));     // out of window 
    do {
        bad.x = GetRandomValue(0, GetScreenWidth() - badTextWidth);
        bad.y = GetRandomValue(0, GetScreenHeight() - 20);
    } while (checkCollision(good, bad) || !isOutOfScissorArea(bad, window)); // out of window and out of good text
}

bool FinderGame::checkCollision(const RandomObject& obj1, const RandomObject& obj2) {
    return !(obj1.x + MeasureText(obj1.text.c_str(), 20) < obj2.x || 
             obj1.x > obj2.x + MeasureText(obj2.text.c_str(), 20) || 
             obj1.y + 20 < obj2.y || 
             obj1.y > obj2.y + 20);
}

bool FinderGame::IfTextClicked(RandomObject& obj){
    int TextWidth = MeasureText(obj.text.c_str(), 20);
    int TextHeight = 20;

    Vector2 mousePos = GetMousePosition();

    if (mousePos.x >= obj.x && mousePos.x <= obj.x+TextWidth && 
        mousePos.y >= obj.y && mousePos.y <= obj.y + 20 &&
        mousePos.x >= scissorArea.x && mousePos.x <= scissorArea.x + scissorArea.width &&
        mousePos.y >= scissorArea.y && mousePos.y <= scissorArea.y + scissorArea.height &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ) {
        return true;
    } 
    return false;
}

void FinderGame::DrawEndScreen(bool isWin) {
    const char* message;
    Color messageColor;

    if (isWin) {
        message = "SUCCES!!!";
        messageColor = GREEN;
    } else {
        message = "FAILURE :/";
        messageColor = RED;
    }

    float MessageHeight = 120; // font size
    float MessageWidth = MeasureText(message, MessageHeight); // MessageHeight is font size 

    // rectangle position
    float recX = (GetScreenWidth() - MessageWidth) / 2;
    float recY = (GetScreenHeight() - MessageHeight) / 2;

    Rectangle End = {recX - 50, recY - 50, MessageWidth + 100, MessageHeight + 100};
    DrawRectangleRec(End, BLACK);              // Background
    DrawRectangleLinesEx(End, 5, ORANGE); 
    DrawTextC(message, recX, recY, MessageHeight, messageColor);  // MessageHeight is font size 
}