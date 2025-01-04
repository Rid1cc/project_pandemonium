#include "../headers/CommandInterpreter.h"
#include <iostream>
#include <sstream>
#include "../headers/globals.h"
#include "../managers/GameplayManager.h"
#include "gameplay_vars.h"

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

void CommandInterpreter::outputLine(std::string output) {
    historyDrawnUp();
    historyDrawn[0] = output;
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
        outputLine("IP Address: " + gameplayManager->ipPool[0]);
    } 
    // Subscribe to events based on commands
    else if (cmd == "start") {
        gameplayManager->gameplayEvent.triggerEvent("startGame");
        outputLine("Game started.");
    }
    else if (cmd == "stop") {
        gameplayManager->gameplayEvent.triggerEvent("stopGame");
        outputLine("Game stopped.");
    }
    //Netscan command
    else if (cmd == "netscan"){
       netscan(iss, args);
    } 

    else if (cmd == "help") {
        historyDrawnUp();
        historyDrawn[0] = "Available commands: echo, ipconfig, start, stop, netscan, help";
    }
    else {
        historyDrawnUp();      
        historyDrawn[0] = "Unknown command: " + command;
    }
}

void CommandInterpreter::netscan(std::istringstream &iss, std::vector<std::string> &args) {
     //DRAIN
        if (args.size() == 3 && args[0] == "drain") {
            if(!isEnemyIpKnown){
                if(args[1] == gameplayManager->enemyHostname){
                    if(args[2] == "-s"){
                        if(!isCounting){
                            outputLine("Netscan: Silent Draining started");
                            gameplayManager->gameplayEvent.triggerEvent("drainSilent");}
                        else{
                            outputLine("error: process already running");
                        }
                    }
                    else if(args[2] == "-b"){
                        if(!isCounting){
                            outputLine("Netscan: Bruteforce Draining started");
                            gameplayManager->gameplayEvent.triggerEvent("drainBruteforce");}
                        else{
                            outputLine("error: process already running");
                        }
                    }
                    else{
                        outputLine("Error: Third argument '-s' or '-b' is needed.");
                    }
                }
                else{
                    outputLine("Netscan: Unknown hostname.");
                    printf("Expected: %s\n", gameplayManager->enemyHostname.c_str());
                }
            }
            else{
                outputLine("Netscan: Enemy IP already known.");
            }
        }
        else if (args.size() == 2 && args[0] == "drain") {
            outputLine("Error: Third argument '-s' or '-b' is needed.");
        }
        else if (args.size() == 2 && args[0] == "list"){
            // Check if args[1] is a number
            bool isNumber = true;
            for(char c : args[1]){
                if(!std::isdigit(c)){
                    isNumber = false;
                    break;
                }
            }
            if(!isNumber){
                outputLine("Usage: netscan list <page_number>");
            }
            else {
                int page = std::stoi(args[1]);
                if(page < 1 || page > 5){
                    outputLine("No Page " + std::to_string(page));
                    outputLine("Usage: netscan list <page_number>");
                } else {
                    outputLine("Scanning network... Page " + std::to_string(page));
                    int start = (page - 1) * 24;
                    int end = std::min(start + 24, 100);
                    for(int i = start; i < end; i++) {
                        outputLine(gameplayManager->ipPool[i]);
                    }
                }
            }
        }else {
            outputLine("Usage: ");
            outputLine("netscan list <page_number>");
            outputLine("netscan drain <hostname> (-s) (-b)");
        }  
}


