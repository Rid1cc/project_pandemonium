#include "headers/CommandInterpreter.h"
#include <iostream>
#include <sstream>
#include "headers/globals.h"

CommandInterpreter::CommandInterpreter() : currentCommand("") {
    // Feature NYD
}

void CommandInterpreter::executeCommand(const std::string& command) {
    currentCommand = command;
    parseCommand(command, historyDrawn);
    addToHistory(command);
}

void CommandInterpreter::addToHistory(const std::string& command) {
    if (history.size() >= maxHistorySize) {
        history.erase(history.begin()); 
    }
    history.push_back(command);
}

void CommandInterpreter::showHistory() const {
    for (const auto& cmd : history) {
        std::cout << cmd << std::endl;
    }
}

const std::string& CommandInterpreter::getCurrentCommand() const {
    return currentCommand;
}

const std::vector<std::string>& CommandInterpreter::getHistory() const {
    return history;
}

void CommandInterpreter::historyDrawnUp() {
    for(int i = 29; i > 0; i--) {
        historyDrawn[i] = historyDrawn[i - 1];
    }
}

void CommandInterpreter::parseCommand(const std::string& command, std::string* historyDrawn) {
    std::istringstream iss(command);
    std::string cmd;
    std::vector<std::string> args;

    iss >> cmd;

    std::string arg;
   

    while (iss >> arg) {
        args.push_back(arg);
    }

    if (cmd == "echo") {
        historyDrawnUp();
        std::string output;
        for (const auto& a : args) {  // chceck every arg
            output += a + " ";
        }
        historyDrawn[0] = output;
    } else if (cmd == "ipconfig") {
        historyDrawnUp();
        historyDrawn[0] = "IP address: 192.168.100.1";
    } 

    //ADD COMMANDS HERE AS ELSEIF, ADD ARGS AS ARGS, REMEMBER TO EXECUTE historyDrawnUp EVERY TIME LINE IS UPPED.
    else {
        historyDrawnUp();      
        historyDrawn[0] = "Unknown command: " + command;
    }
}

