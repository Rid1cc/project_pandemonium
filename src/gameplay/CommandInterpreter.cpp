#include "../headers/CommandInterpreter.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "../headers/globals.h"
#include "../managers/GameplayManager.h"
#include "gameplay_vars.h"
#include "../headers/player.h"

const int maxHistoryDrawnSize = 50;

CommandInterpreter::CommandInterpreter(GameplayManager* manager) 
    : currentCommand(""), gameplayManager(manager) {
    // Initialize historyDrawn array
    for(int i = 0; i < maxHistoryDrawnSize; ++i){
        historyDrawn[i] = " ";
    }
    // Feature NYD
}

void CommandInterpreter::reset() {
    currentCommand = "";
    history.clear();
    for(int i = 0; i < maxHistoryDrawnSize; ++i){
        historyDrawn[i] = " ";
    }
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
    for(int i = maxHistoryDrawnSize - 1; i > 0; i--) {
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
        outputLine("IP Address: " + gameplayManager->enemy.getIpAddr());
    } 
    // Subscribe to events based on commands
    // else if (cmd == "start") {
    //     gameplayManager->gameplayEvent.triggerEvent("ddos");
    //     outputLine("Game started.");
    // }
    // else if (cmd == "stop") {
    //     gameplayManager->gameplayEvent.triggerEvent("stopGame");
    //     SelectedDifficulty = 0;
    //     outputLine("Game stopped.");
    // }
    else if (cmd == "botnet") {
        botnet(iss, args);
    }
    //Netscan command
    else if (cmd == "netscan"){
       netscan(iss, args);
    } 
    //Netscan command
    else if (cmd == "systemstatus"){
       systemstatus(iss, args);
    } 
    //Portscan command
    else if (cmd == "portscan") {
        portscan(iss, args);
    }

    else if (cmd == "flood") {
        flood(iss, args);
    }

    else if (cmd == "smtp") {
        smtpCommand(args);
    }

    else if (cmd == "help") {
        outputLine("Available commands:");
        outputLine("- echo <text>: Echoes the text");
        outputLine("- ipconfig: Displays the IP address");
        outputLine("- netscan: help of netscan command");
        outputLine("- portscan: help of portscan command");
        outputLine("- flood: help of flood command");
        outputLine("- smtp: help of smtp command");
        outputLine("- botnet: help of botnet command");
        outputLine("- systemstatus <ip>: status of a system");
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
                if(args[1] == gameplayManager->enemy.getHostname()){
                    if(args[2] == "-s"){
                        if(!isPIDCounting){
                            outputLine("Netscan: Silent Draining started");
                            gameplayManager->gameplayEvent.triggerEvent("drainSilent");}
                        else{
                            outputLine("error: process already running");
                        }
                    }
                    else if(args[2] == "-b"){
                        if(!isPIDCounting){
                            outputLine("Netscan: Bruteforce Draining started");
                            gameplayManager->gameplayEvent.triggerEvent("drainBruteforce");}
                        else{
                            outputLine("error: process already running");
                        }
                    }
                    else if (args[2] == "-pb") {
                        // Display remaining IPs from selectedIpPool
                        outputLine("Remaining IPs:");
                        for(const auto& ip : gameplayManager->selectedIpPool) {
                            outputLine(ip.c_str());
                        }
                    }
                    else{
                        outputLine("Error: Third argument '-s' or '-b' is needed.");
                    }
                }
                else{
                    outputLine("Netscan: Unknown hostname.");
                    printf("Expected: %s\n", gameplayManager->enemy.getHostname().c_str());
                }
            }
            else{
                outputLine("Netscan: Enemy IP already known.");
            }
        }
        else if (args.size() == 2 && args[0] == "drain") {
            outputLine("Error: Third argument '-s' or '-b' is needed.");
        }
        // Add handling for "remain" parameter
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

void CommandInterpreter::portscan(std::istringstream &iss, std::vector<std::string> &args) {
    if(args.size() == 1 && args[0] == gameplayManager->enemy.getIpAddr()) {
            outputLine("Portscan: Scanning ports on " + gameplayManager->enemy.getIpAddr());
            gameplayManager->gameplayEvent.triggerEvent("portscan");
    }
    else if(args.size() == 1 && args[0] != gameplayManager->enemy.getIpAddr()) {
        outputLine("Portscan: Scanning ports on " + args[0]);
        outputLine("Error: Scanning failed");
    }
    else if(args.size() == 0) {
        outputLine("Error: IP address required.");
    }
    else {
        outputLine("Usage: portscan <ip_address>");
    }
}

void CommandInterpreter::systemstatus(std::istringstream &iss, std::vector<std::string> &args) {
    if(args.size() != 1) {
        outputLine("Error: Syntax error");
        outputLine("Usage: systemstatus <ip_address>");
        return;
    }

    std::string ipNumber = args[0];

    if(ipNumber == gameplayManager->enemy.getIpAddr()) {
        outputLine("Systemstatus: Scanning target:");
        outputLine("Systemstatus: Target: " + gameplayManager->enemy.getHostname() + "@" + gameplayManager->enemy.getIpAddr());
        outputLine("Systemstatus: Target IP: " + gameplayManager->enemy.getIpAddr());
        outputLine("Systemstatus: Target Firewall State: " + std::to_string(gameplayManager->enemy.getHealth()) + "%");
        outputLine("Systemstatus: Target SMTP Client: ");
        outputLine(gameplayManager->enemy.getMail());
        
    }
    else if(std::find(gameplayManager->ipPool,
                     gameplayManager->ipPool + sizeof(gameplayManager->ipPool)/sizeof(gameplayManager->ipPool[0]),
                     ipNumber) != gameplayManager->ipPool + sizeof(gameplayManager->ipPool)/sizeof(gameplayManager->ipPool[0])) {
        outputLine("Systemstatus: Target: Unknown@" + ipNumber);
        outputLine("Systemstatus: Target IP: " + ipNumber);
        outputLine("Systemstatus: Target Firewall State: Unknown");
        outputLine("Systemstatus: Target SMTP Client: Unknown");
    }
    else {
        outputLine("Error: IP address not in pool.");
    }
}

void CommandInterpreter::flood(std::istringstream &iss, std::vector<std::string> &args) {
    // Check if there are at least two arguments
    if(args.size() < 2) {
        outputLine("Error: Syntax error");
        outputLine("Usage: flood <target_ip> <port_number>");
        return;
    }

    // Convert args[1] to integer safely
    int portNumber;
    try {
        portNumber = std::stoi(args[1]);
    } catch(const std::invalid_argument& e) {
        outputLine("Error: Invalid port number.");
        return;
    }

    // Check if portNumber exists in gameplayManager's port array
    if(args.size() == 2 
        && std::find(gameplayManager->port,
                     gameplayManager->port + sizeof(gameplayManager->port)/sizeof(gameplayManager->port[0]),
                     portNumber
                    ) != gameplayManager->port + sizeof(gameplayManager->port)/sizeof(gameplayManager->port[0]) 
        && args[0] == gameplayManager->enemy.getIpAddr()) 
        { if (isPIDCounting) {
            outputLine("Error: Process already running.");
        } else {
        outputLine("Flood: Started flooding:");
        outputLine("Flood: Target IP: " + args[0]);
        outputLine("Flood: Target Port: " + args[1]);
        gameplayManager->gameplayEvent.triggerEvent("ddos");}
    }
    else if(args.size() == 2 && args[0] != gameplayManager->enemy.getIpAddr()) {
        outputLine("Error: flooding failed");
        outputLine("Error: target invalid");
    }
    else if(args.size() == 2 
        && std::find(gameplayManager->port,
                     gameplayManager->port + sizeof(gameplayManager->port)/sizeof(gameplayManager->port[0]),
                     portNumber
                    ) == gameplayManager->port + sizeof(gameplayManager->port)/sizeof(gameplayManager->port[0]) 
        && args[0] == gameplayManager->enemy.getIpAddr()) {
        outputLine("Error: flooding failed");
        outputLine("Error: port invalid");
    }
    else {
        outputLine("Usage: flood <target_ip> <port_number>");
    }
}

void CommandInterpreter::smtpCommand(const std::vector<std::string>& args) {
    if (args.size() == 1 && args[0] == "prime") {
        if (payloadState == 1) {
            outputLine("Payload already primed.");
        } else {
            payloadState = 1;
            outputLine("Payload primed.");
        }
    } else if (args.size() == 2 && args[0] == "send") {
        if(isPIDCounting){
            outputLine("Error: Process already running.");
        } else {
            if (payloadState != 1) {
                outputLine("Error: Payload not primed.");
            } else if (args[1] == gameplayManager->enemy.getMail()) {
                outputLine("Mail sent to " + args[1]);
                gameplayManager->gameplayEvent.triggerEvent("mailbomb");
                payloadState = 0; // Reset payload state after sending
            } else {
                outputLine("Error: Wrong mail address.");
            }
        }
    } else {
        outputLine("Usage: smtp prime | smtp send mail");
    }
}

void CommandInterpreter::botnetAttack() {
    if (gameplayManager->botnet.empty()) {
        outputLine("Error: Botnet is empty. Add bots before attacking.");
        return;
    }

    int botnetSize = gameplayManager->botnet.size();
    outputLine("Botnet: Attacking with " + std::to_string(botnetSize) + " bots.");
    
    // Trigger attack event based on botnet size
    if (botnetSize > 0) {
        gameplayManager->gameplayEvent.triggerEvent("botnetAttack");
    }

    // Clear the botnet after attack
    gameplayManager->botnet.clear();
}

void CommandInterpreter::botnet(std::istringstream &iss, std::vector<std::string> &args) {
    if(isPIDCounting){
        outputLine("Error: Process already running.");
        return;
    } 
    else { 
        if (args.size() == 2 && args[0] == "add") {
            std::string ip = args[1];
            if (ip == gameplayManager->enemy.getIpAddr()) {
                outputLine("Error: Cannot add enemy IP to botnet.");
            } else if (gameplayManager->botnet.size() >= 5) {
                outputLine("Error: Botnet is full. Maximum 5 IPs allowed.");
            } else if (std::find(std::begin(gameplayManager->ipPool), std::end(gameplayManager->ipPool), ip) != std::end(gameplayManager->ipPool)) {
                gameplayManager->botnet.insert(ip);
                outputLine("Botnet: Added IP " + ip + " to botnet.");
            } else {
                outputLine("Error: IP not found in IP pool.");
            }
        } else if (args.size() == 1 && args[0] == "discover") {
            outputLine("Botnet: Discovering bots in botnet.");
            for (const auto& ip : gameplayManager->botnet) {
                outputLine(ip);
            }
        } else if (args.size() == 1 && args[0] == "attack") {
            botnetAttack();
        } else {
            outputLine("Usage: botnet add <ip> | botnet discover | botnet attack");
        }
    }
}