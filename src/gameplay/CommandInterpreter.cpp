#include "../headers/CommandInterpreter.h"
#include <iostream>
#include <sstream>
#include "../headers/globals.h"
#include "../managers/GameplayManager.h"

CommandInterpreter::CommandInterpreter(GameplayManager* manager) : currentCommand(""), gameplayManager(manager) {
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
    for(int i = 49; i > 0; i--) {
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
        for (const auto& a : args) {  // check every arg
            output += a + " ";
        }
        historyDrawn[0] = output;
    } else if (cmd == "ipconfig") {
        historyDrawnUp();
        historyDrawn[0] = "IP address: 192.168.100.1";
    } 
    // Subscribe to events based on commands
    else if (cmd == "start") {
        gameplayManager->gameplayEvent.triggerEvent("startGame");
        historyDrawnUp();
        historyDrawn[0] = "Start command executed.";
    }
    else if (cmd == "stop") {
        gameplayManager->gameplayEvent.triggerEvent("stopGame");
        historyDrawnUp();
        historyDrawn[0] = "Stop command executed.";
    }
    else if (cmd == "netscan"){
        if (args.size() != 1) {
            historyDrawnUp();
            historyDrawn[0] = "Usage: netscan <page_number>";
        } else {
            int page = std::stoi(args[0]);
            if(page < 1 || page > 5){
                historyDrawnUp();
                historyDrawn[0] = "Usage: netscan <page_number>";
            } else {
                historyDrawnUp();
                historyDrawn[0] = "Scanning network... Page " + std::to_string(page);
                int start = (page - 1) * 24;
                int end = std::min(start + 24, 100);
                for(int i = start; i < end; i++) {
                    historyDrawnUp();
                    historyDrawn[0] = gameplayManager->ipPool[i];
                }
            }
        }
    }
    else if (cmd == "help") {
        historyDrawnUp();
        historyDrawn[0] = "Available commands: echo, ipconfig, start, stop, netscan, help";
    }
    //ADD COMMANDS HERE AS ELSEIF, ADD ARGS AS ARGS, REMEMBER TO EXECUTE historyDrawnUp EVERY TIME LINE IS UPPED.
    else {
        historyDrawnUp();      
        historyDrawn[0] = "Unknown command: " + command;
    }
}

