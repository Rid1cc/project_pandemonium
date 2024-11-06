#include "CommandInterpreter.h"
#include <iostream>
#include <sstream>

CommandInterpreter::CommandInterpreter() : currentCommand("") {
    // Podbudowka pod przyszlosc
}

void CommandInterpreter::executeCommand(const std::string& command) {
    currentCommand = command;
    parseCommand(command);
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

void CommandInterpreter::parseCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    std::vector<std::string> args;

    iss >> cmd;

    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    if (cmd == "echo") {
        std::string output;
        for (const auto& a : args) {  // Iteruj przez wszystkie argumenty
            output += a + " ";
        }
        std::cout << output << std::endl;
    } else if (cmd == "ifconfig") {
        std::cout << "IP address: 192.168.100.1" << std::endl;
    } else {
        std::cout << "Command not found!" << std::endl;
    }
}

