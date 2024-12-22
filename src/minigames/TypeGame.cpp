#include "TypeGame.h"

TypeGame::TypeGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title) {
        text = {
            "Firewall activated.\n"
            "Unauthorized access attempts logged.\n"
            "System integrity checks in progress.\n"
            "Deploying countermeasures.", // text 1 [0]

            "Encryption keys verified successfully.\n"
            "Suspicious activity neutralized.\n"
            "Real-time traffic monitoring engaged.\n" 
            "Secure communication channel established." , // text 2 [1]

            "Alert! Possible phishing attack detected.\n"
            "User credentials remain uncompromised.\n"
            "Training staff on security protocols.\n"
            "Audit scheduled for vulnerable systems." , // text 3 [2]

            "Multiple login attempts blocked.\n"
            "Account locked for security reasons.\n"
            "Implementing two-factor authentication.\n"
            "Stay vigilant, report unusual activity.", // text 4 [3]

            "Network scan detected unrecognized devices.\n"
            "Isolating unknown connections.\n"
            "Security updates deployed successfully.\n" 
            "Threat level reduced to minimal.", // text 5 [4]

            "The system detected unusual port activity.\n"  
            "Temporarily suspending external access.\n"
            "Logs sent to the cybersecurity team.\n"
            "Investigation underway, no breach detected.", // text 6 [5]

            "Regular backups ensure data safety.\n" 
            "Unauthorized script execution prevented.\n"
            "Patching vulnerabilities across the system.\n"
            "Cybersecurity training completed successfully.", // text 7 [6]

            "Admin privileges are locked down.\n"
            "Only authorized personnel allowed.\n"
            "Biometric verification in progress.\n"
            "Defenses are holding strong.", // text 8 [7]
        };

        randomText = text[GetRandomValue(0, 7)]; // drawn text to display (for now we have 8 texts (0 - 7))
        //randomText = text[6];
        typedText = std::string(randomText.length(), '0');

        isCursorVisible = true;
        currentNumber = 0;
}

void TypeGame::Update(){
    MiniGame::Update(); // handle dragging
    UpdateCurrentNumber();
    UpdateCursor(GetFrameTime());
    UpdateTypedText();
}

void TypeGame::Draw(){
    MiniGame::Draw(); // draw window
    DrawRandomText();
    DrawCursor();
}

void TypeGame::DrawRandomText(){

    // int textFontSize = 35;
    int textLineHeight = textFontSize + 5; // line height with spacing
    int textY = 100;

    std::istringstream textStream(randomText);
    std::string line;
    int lineNum = 0;
    while (std::getline(textStream, line)) {
        int lineWidth = MeasureText(line.c_str(), textFontSize);
        int xPos = window.x + (window.width - lineWidth) / 2;
        int yPos = window.y + textY + lineNum * textLineHeight;

        DrawText(line.c_str(), xPos, yPos, textFontSize, GRAY);
        lineNum++;
    }   
}

void TypeGame::DrawCursor(){
    if (isCursorVisible){
        DrawRectangle(cursorX, cursorY, 4, 30, ORANGE);
    }
}

void TypeGame::UpdateCursor(float deltaTime){
    // BLINKING
    timeSinceLastCursorBlink += deltaTime;
    if (isTyping) {
        isCursorVisible = true;
        timeSinceLastCursorBlink = -0.5f;
    }
    else if (timeSinceLastCursorBlink >= cursorBlinkTime){
        isCursorVisible = !isCursorVisible;
        timeSinceLastCursorBlink = 0.0f;
    }

    // CURSOR POSITION 
    std::istringstream textStream(randomText);
    std::string line;
    int lineNum = 0;

    int currentChar = 0;
    while(std::getline(textStream, line)){
        if (currentChar + line.length() >= currentNumber) {
            int lineWidthUpToCursor = MeasureText(line.substr(0, currentNumber - currentChar).c_str(), textFontSize);

            cursorX = window.x + (window.width - MeasureText(line.c_str(), textFontSize)) / 2 + lineWidthUpToCursor;

            cursorY = window.y + 100 + lineNum * (textFontSize + 5);

            return;
        }
        currentChar += line.length() + 1;
        lineNum++;
    }
}

void TypeGame::UpdateCurrentNumber(){
    int Key = GetKeyPressed();
    
    if (Key > 0){
        std::cout << " key:  " << Key << std::endl;

        if (Key >= 32 && Key <= 125){
            currentNumber++;
            isTyping = true;
        } else if (Key == KEY_BACKSPACE && currentNumber > 0){
            currentNumber--;
            isTyping = true;
        } 
        std::cout << "currentNumber: " << currentNumber << std::endl;
        //std::cout << "Typing: " << isTyping << std::endl;
    } else {
        isTyping = false;
    }
}

void TypeGame::UpdateTypedText(){
    int typedkey = GetCharPressed();

    while (typedkey > 0) {
        if ((typedkey >= 32) && (typedkey <= 125)) {
            typedText[currentNumber - 1] = (char)typedkey;
            typedText[currentNumber] = '\0';
        }
        typedkey = GetCharPressed();
        std::cout << "typed tex: " << typedText << std::endl;
    }
}

void TypeGame::DrawTypedText(){

}
