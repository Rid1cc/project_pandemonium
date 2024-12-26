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
    void saveSettings(const std::string& filePath);
    void loadSettings(const std::string& filePath);
private:
    void save(const std::string& filePath, const nlohmann::json& data);
    nlohmann::json load(const std::string& filePath);
    std::string getConfigPath();
};

#endif // FILESYSTEMMANAGER_H
