#include "FileSystemManager.h"

// Function to get the path to the assets directory
std::string getConfigPath() {
    char buffer[1024];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        std::string path(buffer);
        size_t pos = path.find_last_of("/\\");
        return path.substr(0, pos) + "/../config/";
    } else {
        std::cerr << "Buffer too small; need size " << size << std::endl;
        return "";
    }
}

void FileSystemManager::save(const std::string& filePath, const nlohmann::json& data) {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << data.dump(4); // Pretty print with 4 spaces
        file.close();
    } else {
        printf("Error saving file: %s\n", filePath.c_str());
    }
}

nlohmann::json FileSystemManager::load(const std::string& filePath) {
    std::ifstream file(filePath);
    nlohmann::json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        printf("Error reading file: %s\n", filePath.c_str());
    }
    return data;
}

void FileSystemManager::saveSettings(const std::string& filePath) {
    nlohmann::json data;
    data["primaryColor"] = { primaryColor.r, primaryColor.g, primaryColor.b, primaryColor.a };
    data["curvature"] = curvature;
    data["bloomIntensity"] = bloomIntensity;
    data["glowIntensity"] = glowIntensity;
    data["scanlineIntensity"] = scanlineIntensity;
    data["brightness"] = brightness;

    save(filePath, data);
}

void FileSystemManager::loadSettings(const std::string& filePath) {
    nlohmann::json data = load(filePath);
    if (!data.is_null()) {
        primaryColor = { data["primaryColor"][0], data["primaryColor"][1], data["primaryColor"][2], data["primaryColor"][3] };
        curvature = data["curvature"];
        bloomIntensity = data["bloomIntensity"];
        glowIntensity = data["glowIntensity"];
        scanlineIntensity = data["scanlineIntensity"];
        brightness = data["brightness"];
    } else {
        printf("Error reading file: %s\n , loading default", filePath.c_str());
    }
}


