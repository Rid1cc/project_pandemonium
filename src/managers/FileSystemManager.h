#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H

#include <string>
#include "../headers/json.hpp"
#include "../headers/shader_handler.h"
#include <fstream>
#include "../headers/globals.h"
#include <cstdio>

class FileSystemManager {
public:
    void initialize(); // Initialization method
    void saveSettings(const std::string& filePath);
    void loadSettings(const std::string& filePath);

    // Difficulty methods
    void saveMaxDifficulty(int maxDifficulty);
    int loadMaxDifficulty();
    void difficultyCompleted(int difficulty);
    bool isDifficultyCompleted(int difficulty);
    bool difficulty3Completed = false;

private:
    void save(const std::string& filePath, const nlohmann::json& data);
    nlohmann::json load(const std::string& filePath);
    std::string getConfigPath();
};

#endif // FILESYSTEMMANAGER_H
