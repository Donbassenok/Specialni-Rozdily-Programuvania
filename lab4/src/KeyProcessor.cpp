#include "KeyProcessor.hpp"
#include "Logger.hpp"

KeyProcessor::KeyProcessor() : mode(ORIGINAL), zoomLevel(2.0f), zoomCenter(320, 240) {}

void KeyProcessor::processKey(int key) {
    switch (key) {
        case '0': 
            mode = ORIGINAL; 
            Logger::getInstance().info("Mode changed to: ORIGINAL"); 
            break;
        case '1':
            mode = INVERT; 
            Logger::getInstance().info("Mode changed to: INVERT"); 
            break;
        case '2':
            mode = BLUR; 
            Logger::getInstance().info("Mode changed to: BLUR"); 
            break;
        case '3':
            mode = CANNY; 
            Logger::getInstance().info("Mode changed to: CANNY"); 
            break;
        case '4': 
            mode = SOBEL; 
            Logger::getInstance().info("Mode changed to: SOBEL"); 
            break;
        case '5': 
            mode = ZOOM; 
            Logger::getInstance().info("Mode changed to: ZOOM"); 
            break;

        case 'f': 
        case 'F': 
            mode = FACE; 
            Logger::getInstance().info("Mode changed to: FACE"); 
            break;

        case '=': 
            zoomLevel += 0.5f; 
            Logger::getInstance().info("Zoom increased to: " + std::to_string(zoomLevel)); 
            break;
        case '-':
            zoomLevel = std::max(1.0f, zoomLevel - 0.5f); 
            Logger::getInstance().info("Zoom decreased to: " + std::to_string(zoomLevel)); 
            break;
        default:
            Logger::getInstance().debug("Unknown key pressed: " + std::to_string(key));
            break;
    }
}

void KeyProcessor::updateMouse(int x, int y) {
    zoomCenter = cv::Point(x, y);
}

KeyProcessor::Mode KeyProcessor::getMode() const {
    return mode;
}

float KeyProcessor::getZoomLevel() const {
    return zoomLevel;
}

cv::Point KeyProcessor::getZoomCenter() const {
    return zoomCenter;
}