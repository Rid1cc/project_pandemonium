#include "../headers/DifficultySelector.h"
#include "../managers/FileSystemManager.h"

/*
!!!!!!!!!!!!!!!!!!!!!
Max unlocked difficulty is saved as a number in the file difficulty.json !
    1 = EASY 
    2 = NORMAL 
    3 = HARD 
!!!!!!!!!!!!!!!!!!!!!
*/

// declarations (max unlocked difficulty)
// Remove the following functions:
// void SaveMaxDifficulty(int maxDifficulty);
// int LoadMaxDifficulty();
void DifficultyCompleted(int difficulty); // saving new max difficulty if it is greater than written
bool isDifficultyCompleted(int difficulty); // return true if it is 

// declarations
void DrawDifficultySelection();
bool isMouseOnButton(Rectangle rect);
void DrawDifficultyButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton);
void UpdateDifficultySelection();
void DrawDescription(Rectangle rect, int FontSize, std::string text, Color color);
void DrawBlockedButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton);

// Add a flag to track if the screen was just entered
bool screenJustEntered = true;

using json = nlohmann::json;

// Remove the following functions:
// void SaveMaxDifficulty(int maxDifficulty);
// int LoadMaxDifficulty();

void DifficultyCompleted(int difficulty){
    // Use FileSystemManager to handle difficulty completion
    FileSystemManager fsm;
    fsm.difficultyCompleted(difficulty);
}

bool isDifficultyCompleted(int difficulty){
    // Use FileSystemManager to check difficulty status
    FileSystemManager fsm;
    return fsm.isDifficultyCompleted(difficulty);
}


void DrawDifficultySelection(){
    if (screenJustEntered){
        // Ignore the initial mouse click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            // Consume the click
            screenJustEntered = false;
            return;
        }
        screenJustEntered = false;
    }

    ClearBackground(BLACK);
    //DrawText("Select Difficulty", 20, 20, 40, ORANGE);

    // buttons positions 
    Rectangle easyRect = { 150, 150, 330, 110 };
    Rectangle normalRect = { 150, 310, 330, 110 };
    Rectangle hardRect = { 150, 470, 330, 110 };

    // Screen Lines
    DrawRectangleLinesEx(screen, 5, primaryColor);

    // UP TEXT
    const char* set = "SELECT A DIFFICULTY LEVEL";
    DrawTextB(set, (screen.width - MeasureText(set, 70))/2 + 170, 50, 70, primaryColor);

    // Description box 
    Rectangle description = {600, 150, 500, 430};
    DrawRectangleRec(description, BLACK);
    DrawRectangleLinesEx(description, 5, primaryColor);

    // font sizes
    int buttonFontSize = 40;
    int descriptionFontSize = 30;
 
    // buttons
    const char* easy = "E A S Y";
    DrawDifficultyButton(easyRect, easy, primaryColor, buttonFontSize, isMouseOnButton(easyRect));
    if (isMouseOnButton(easyRect)){
        std::string easyDescription = 
        ">Relax and take your time!\n"
        "\n"
        ">This difficulty level offers\n"
        " generous time limits for\n"
        " completing mini-games,\n"
        " making it perfect for\n"
        " beginners or those\n"
        " looking to enjoy a casual\n"
        " experience.";
        DrawDescription (description, descriptionFontSize, easyDescription, primaryColor);
    } 
    if (isMouseOnButton(easyRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        SelectedDifficulty = 1;
        screenJustEntered = true;
    }


    const char* normal = "N O R M A L";
    if (isDifficultyCompleted(2)){
        DrawDifficultyButton(normalRect, normal, primaryColor, buttonFontSize, isMouseOnButton(normalRect));    
        if(isMouseOnButton(normalRect)){
            std::string normalDescription = 
                ">Strike a balance!\n"
                "\n"
                ">Mini-games require focus\n"
                " and moderate speed to complete.\n"
                "\n"
                ">This level provides a fair\n"
                " challenge for most players.";
            DrawDescription(description, descriptionFontSize, normalDescription, primaryColor);
        }
        if (isMouseOnButton(normalRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            SelectedDifficulty = 2;
            screenJustEntered = true;
        }
    } else {
        DrawBlockedButton(normalRect, normal, primaryColor, buttonFontSize, isMouseOnButton(normalRect));
        if(isMouseOnButton(normalRect)){
            std::string normalDescription = 
                ">To unlock Normal difficulty\n" 
                " level, first complete the game\n" 
                " on Easy difficulty.\n";
            DrawDescription(description, descriptionFontSize, normalDescription, DARKGRAY);
        }
    }

    const char* hard = "H A R D";
    if (isDifficultyCompleted(3)){
        DrawDifficultyButton(hardRect, hard, primaryColor, buttonFontSize, isMouseOnButton(hardRect));
        if(isMouseOnButton(hardRect)){
            std::string hardDescription = 
            ">Only for the brave!\n"
            "\n"
            ">With tight time limits,\n"
            " mini-games demand quick\n"
            " thinking and fast reflexes.\n"
            "\n"
            ">A true test of skill and\n"
            " composure.";
            DrawDescription(description, descriptionFontSize, hardDescription, primaryColor);
        }
        if (isMouseOnButton(hardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            SelectedDifficulty = 3;
            screenJustEntered = true;
        }
    } else {
        DrawBlockedButton(hardRect, hard, primaryColor, buttonFontSize, isMouseOnButton(hardRect));
        if(isMouseOnButton(hardRect)){
            std::string hardDescription = 
            ">To unlock Hard difficulty level,\n"
            " first complete the game on\n"
            " Normal difficulty.\n";
            DrawDescription(description, descriptionFontSize, hardDescription, DARKGRAY);
        }
    }
}

bool isMouseOnButton(Rectangle rect){
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

void DrawDifficultyButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton){
    if (isMouseOnButton){
        DrawRectangleRec(rect, color);
        DrawRectangleLinesEx(rect, 5, BLACK);
        DrawTextB(text, ShakeXY((float)rect.x + (rect.width - MeasureText(text, FontSize))/2, 1.5), ShakeXY((float)rect.y + (rect.height - FontSize)/2, 1.5), FontSize, BLACK);
    } else {
        DrawRectangleRec(rect, BLACK);
        DrawRectangleLinesEx(rect, 5, color);
        DrawTextB(text, rect.x + (rect.width - MeasureText(text, FontSize))/2, rect.y + (rect.height - FontSize)/2, FontSize, color);
    }
}

void DrawBlockedButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton){
    DrawRectangleRec(rect, BLACK);
    DrawRectangleLinesEx(rect, 5, DARKGRAY);
    DrawTextB(text, rect.x + (rect.width - MeasureText(text, FontSize))/2, rect.y + (rect.height - FontSize)/2, FontSize, DARKGRAY);
}


void DrawDescription(Rectangle rect, int FontSize, std::string text, Color color){
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


void UpdateDifficultySelection(){
    if (SelectedDifficulty == 1 || SelectedDifficulty == 2 || SelectedDifficulty == 3){
        std::cout << "SelectedDifficulty: " << SelectedDifficulty << std::endl;
        currentScreen = GAMEPLAY;
    }
}

// When switching to this screen, set the flag
void SwitchToDifficultySelection(){
    // ...existing code...
    screenJustEntered = true;
}



