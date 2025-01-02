#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>
#include <vector>
#include "../managers/GameplayManager.h"

class CommandInterpreter {
public:
    CommandInterpreter(GameplayManager* manager);
    void executeCommand(const std::string& command);
    void addToHistory(const std::string& command);
    void showHistory() const;

    // Getters
    const std::string& getCurrentCommand() const;
    const std::vector<std::string>& getHistory() const;

    TimeManager timer; // TimeManager instance

private:
    
    std::string currentCommand;
    std::vector<std::string> history;
    const int maxHistorySize = 30; // not yet used, in future - replace for history[]
    GameplayManager* gameplayManager; // Pointer to GameplayManager

    void parseCommand(const std::string& command, std::string* historyDrawn);
    void historyDrawnUp();
    void outputLine(std::string output);
};

#endif
