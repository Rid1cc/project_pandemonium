#include "command_interpreter.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include <sstream>

void echoCommand(const std::vector<std::string>& args) {
    for (const auto& word : args) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

void ifconfigCommand(const std::vector<std::string>& args) {
    (void)args; // Ignorujemy argumenty, jeśli komenda ich nie wymaga
    std::cout << "IP Address: 192.168.100.1" << std::endl;
}

void unknownCommand(const std::string& command) {
    std::cout << "Command not found: " << command << std::endl;
}

std::pair<std::string, std::vector<std::string>> parseCommand(const std::string& input) {
    std::istringstream iss(input);
    std::string command;
    std::vector<std::string> args;

    iss >> command;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return {command, args};
}

void executeCommand(const std::string& input) {
    static std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> commands = {
        {"echo", echoCommand},
        {"ifconfig", ifconfigCommand},
    };

    auto [command, args] = parseCommand(input);
    if (commands.find(command) != commands.end()) {
        commands[command](args);
    } else {
        unknownCommand(command);
    }
}
