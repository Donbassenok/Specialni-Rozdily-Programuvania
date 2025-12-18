#include "ConfigManager.hpp"
#include "Logger.hpp"
#include <fstream>
#include <iostream>

ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

ConfigManager::ConfigManager() {
    configData = {
        {"camera", {
            {"id", 0},
            {"width", 640},
            {"height", 480}
        }},
        {"model", {
            {"proto", "deploy.prototxt"},
            {"weights", "res10_300x300_ssd_iter_140000.caffemodel"},
            {"threshold", 0.5}
        }},
        {"logger", {
            {"level", "INFO"}
        }}
    };
}

void ConfigManager::loadConfig(const std::string& filename) {
    std::lock_guard<std::mutex> lock(configMutex);
    
    std::string fullPath = std::string(RESOURCES_PATH) + filename;
    
    std::ifstream configFile(fullPath);
    if (!configFile.is_open()) {
        Logger::getInstance().error("Config file not found at: " + fullPath + ". Using defaults.");
        return;
    }

    try {
        json loadedJson;
        configFile >> loadedJson;
        
        configData.merge_patch(loadedJson);
        Logger::getInstance().info("Configuration loaded successfully from " + filename);
        
    } catch (const json::parse_error& e) {
        Logger::getInstance().error("JSON parse error: " + std::string(e.what()) + ". Using defaults.");
    }
}

int ConfigManager::getCameraId() const {
    return configData["camera"].value("id", 0);
}

int ConfigManager::getFrameWidth() const {
    return configData["camera"].value("width", 640);
}

int ConfigManager::getFrameHeight() const {
    return configData["camera"].value("height", 480);
}

std::string ConfigManager::getModelProto() const {
    return configData["model"].value("proto", "deploy.prototxt");
}

std::string ConfigManager::getModelWeights() const {
    return configData["model"].value("weights", "res10_300x300_ssd_iter_140000.caffemodel");
}

float ConfigManager::getModelThreshold() const {
    return configData["model"].value("threshold", 0.5f);
}

std::string ConfigManager::getLogLevel() const {
    return configData["logger"].value("level", "INFO");
}