#include "TypeGame.h"

TypeGame::TypeGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title) {
        text = {
            // TEXT INSTRUCTION:
            // Add \n after every endline without adding space behind or after '\n'
            // Every line should be in " "

            "Firewall activated.\n"
            "Unauthorized access attempts logged.\n"
            "System integrity checks in progress.\n"
            "Deploying countermeasures.", // text 1 [0]

            "Encryption keys verified successfully.\n"
            "Suspicious activity neutralized.\n"
            "Real-time traffic monitoring engaged.\n" 
            "Secure communication channel established.", // text 2 [1]

            "Alert! Possible phishing attack detected.\n"
            "User credentials remain uncompromised.\n"
            "Training staff on security protocols.\n"
            "Audit scheduled for vulnerable systems.", // text 3 [2]

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
        isTypeWin = false;
        randomText = text[GetRandomValue(0, 7)]; // drawn text to display (for now we have 8 texts (0 - 7))
        //randomText = text[0];
        typedText = std::string(randomText.length(), '\0');

        correctness = std::vector<bool>(randomText.length(), true);
        isCursorVisible = true;
        currentNumber = 0;
}

TypeGame::~TypeGame(){
}

void TypeGame::Update(){
    MiniGame::Update(); // handle dragging
    UpdateCorrectness(); 
    UpdateTypedText();
    UpdateCursor(GetFrameTime());
    if (AllCorrect() && currentNumber == randomText.length()){
        gameComplete = true;
        isTypeWin = true;
        std::cout << "TypeGame Complete - win." << std::endl;
    }
}

void TypeGame::Draw(){
    MiniGame::Draw(); // draw window
    DrawRandomText();
    DrawCursor();
}

void TypeGame::UpdateCorrectness(){
    for (size_t i = 0; i < randomText.length(); i++){
        if (typedText[i] == '\0'){
            continue;
        }
        else if (typedText[i] == randomText[i] || (randomText[i] == '\n' && typedText[i] == ' ')){
            correctness[i] = true;
        } else {
            correctness[i] = false;
        }
    }
}

void TypeGame::DrawRandomText(){
    int textLineHeight = textFontSize + 5; // line height with spacing
    int textY = 100;
    
    std::istringstream textStream(randomText);
    std::string line;

    int globalIndex = 0; // tracks index in typedText/randomText/correctness
    int lineNum = 0;

    int n = 0; // for '\n' in text (DrawText ignore it)

    while (std::getline(textStream, line)) {
        int lineWidth = MeasureText(line.c_str(), textFontSize);
        int xPos = window.x + (window.width - lineWidth) / 2;
        int yPos = window.y + textY + lineNum * textLineHeight;

        // DRAWING  TEXT:
        for (size_t i = 0; i < line.length(); i++){
            std::string subText = line.substr(0, i);
            float currentX = xPos + MeasureText(subText.c_str(), textFontSize);

            std::string letter(1, line[i]);
            Color colorText = GRAY; // default text color         
            if (typedText[globalIndex + n] != '\0'){
                if (correctness[globalIndex + n]){
                    colorText = GREEN;
                } else {
                    colorText = RED;
                    if (randomText[globalIndex + n] == ' '){
                        DrawRectangle(ShakeXY(currentX, 3), ShakeXY(yPos, 3), MeasureText(" ", textFontSize), textFontSize, colorText); // drawing red rectangle, when player input is incorrect
                    }
                    DrawText(letter.c_str(), ShakeXY(currentX, 3), ShakeXY(yPos, 3), textFontSize, colorText);
                }
                    //std::cout << "globalIndex: " << globalIndex << std::endl;
            }
            DrawText(letter.c_str(), currentX, yPos, textFontSize, colorText);

            globalIndex++;
        }
        n++;
        lineNum++;
    }
    //std::cout << "globalIndex: " << globalIndex << std::endl;
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

void TypeGame::UpdateTypedText(){
    std::lock_guard<std::mutex> lock(inputMutex); // Ensure thread safety
    if (!gameManager.hasActiveTypeGame()) {
        return; // Exit if TypeGame is no longer active
    }

    int typedKey = GetCharPressed();

    if ((typedKey > 0) && (typedKey >= 32) && (typedKey <= 125) && (currentNumber < randomText.length())) {
        isTyping = true;
        typedText[currentNumber] = static_cast<char>(typedKey);
        currentNumber++;
    } else {
        isTyping = false;
    }

    if (IsKeyPressed(KEY_BACKSPACE) && currentNumber > 0){
        currentNumber--;
        isTyping = true;
        typedText[currentNumber] = '\0';
    }

    if (IsKeyDown(KEY_BACKSPACE)) {
        if (backTimer >= 30) {
            currentNumber--;
            if (currentNumber < 0) currentNumber = 0;
            typedText[currentNumber] = '\0';
        }
        else {
            backTimer++;
        }
    } else {
        backTimer = 0;
    }
    std::cout << "currentNumber: " << currentNumber << std::endl;
    std::cout << "typed text: " << typedText << std::endl;
}

bool TypeGame::AllCorrect(){
    for (bool c : correctness){
        if (!c){
            return false;
        }
    }
    return true;
}


