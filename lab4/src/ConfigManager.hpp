#pragma once
#include <string>
#include <mutex>
#include "json.hpp"

using json = nlohmann::json;

class ConfigManager {
public:
    static ConfigManager& getInstance();
    ConfigManager(const ConfigManager&) = delete;
    void operator=(const ConfigManager&) = delete;

    void loadConfig(const std::string& filename);

    int getCameraId() const;
    int getFrameWidth() const;
    int getFrameHeight() const;
    
    std::string getModelProto() const;
    std::string getModelWeights() const;
    float getModelThreshold() const;
    
    std::string getLogLevel() const;

private:
    ConfigManager();
    json configData;
    std::mutex configMutex;
};