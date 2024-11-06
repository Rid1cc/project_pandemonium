#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>
#include <vector>

class CommandInterpreter {
public:
    CommandInterpreter();
    void executeCommand(const std::string& command);
    void addToHistory(const std::string& command);
    void showHistory() const;

    // Getters
    const std::string& getCurrentCommand() const;
    const std::vector<std::string>& getHistory() const;

private:
    std::string currentCommand;
    std::vector<std::string> history;
    const int maxHistorySize = 30; // not yet used, in futute - replace for history[]

    void parseCommand(const std::string& command);
};

#endif
