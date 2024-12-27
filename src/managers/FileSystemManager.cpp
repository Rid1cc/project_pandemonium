#include "FileSystemManager.h"
#include "../headers/json.hpp"
#include <fstream>
#include "../headers/settings_vars.h"


void FileSystemManager::save(const std::string& filePath, const nlohmann::json& data) {
    std::ofstream file(filePath.c_str());
    if (file.is_open()) {
        file << data.dump(4); // Pretty print with 4 spaces
        file.close();
    } else {
        printf("Error saving file: %s\n", filePath.c_str());
    }
}

nlohmann::json FileSystemManager::load(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    nlohmann::json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        printf("Error reading file: %s\n", filePath.c_str());
    }
    return data;
}
    // master_volume = 0.5;
    // music_volume = 1.0;
    // sfx_volume = 1.0;
    // shaderQuality = LOW;
    // primaryColor = ORANGE;
    // curvature = 0.07f;
    // bloomIntensity = 2.3f;
    // glowIntensity = 1.5f;
    // scanlineIntensity = 1.0f;
    // brightness = 1.4f;

void FileSystemManager::saveSettings(const std::string& filename) {
    nlohmann::json settingsJson;
    settingsJson["master_volume"] = master_volume;
    settingsJson["music_volume"] = music_volume;
    settingsJson["sfx_volume"] = sfx_volume;
    settingsJson["shaderQuality"] = shaderQuality;
    settingsJson["primaryColor"] = { primaryColor.r, primaryColor.g, primaryColor.b, primaryColor.a };
    settingsJson["curvature"] = curvature;
    settingsJson["bloomIntensity"] = bloomIntensity;
    settingsJson["glowIntensity"] = glowIntensity;
    settingsJson["scanlineIntensity"] = scanlineIntensity;
    settingsJson["brightness"] = brightness;
    settingsJson["sh_resolution"] = { sh_resolution.x, sh_resolution.y };
    settingsJson["displayColor"] = { displayColor.r, displayColor.g, displayColor.b, displayColor.a };

    std::ofstream file(filename);
    file << settingsJson.dump(4);
}

void FileSystemManager::loadSettings(const std::string& filename) {
    std::ifstream file(filename);
    nlohmann::json settingsJson;
    file >> settingsJson;

    master_volume = settingsJson["master_volume"];
    music_volume = settingsJson["music_volume"];
    sfx_volume = settingsJson["sfx_volume"];
    shaderQuality = settingsJson["shaderQuality"];
    primaryColor = { settingsJson["primaryColor"][0], settingsJson["primaryColor"][1], settingsJson["primaryColor"][2], settingsJson["primaryColor"][3] };
    curvature = settingsJson["curvature"];
    bloomIntensity = settingsJson["bloomIntensity"];
    glowIntensity = settingsJson["glowIntensity"];
    scanlineIntensity = settingsJson["scanlineIntensity"];
    brightness = settingsJson["brightness"];
    sh_resolution = { settingsJson["sh_resolution"][0], settingsJson["sh_resolution"][1] };
    displayColor = { settingsJson["displayColor"][0], settingsJson["displayColor"][1], settingsJson["displayColor"][2], settingsJson["displayColor"][3] };
}


