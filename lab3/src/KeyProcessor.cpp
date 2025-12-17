#include "KeyProcessor.hpp"

KeyProcessor::KeyProcessor() : mode(ORIGINAL), zoomLevel(2.0f), zoomCenter(320, 240) {}

void KeyProcessor::processKey(int key) {
    switch (key) {
        case '0': mode = ORIGINAL; break;
        case '1': mode = INVERT; break;
        case '2': mode = BLUR; break;
        case '3': mode = CANNY; break;
        case '4': mode = SOBEL; break;
        case '5': mode = ZOOM; break; 

        case '=': zoomLevel += 0.5f; break;
        case '-': zoomLevel = std::max(1.0f, zoomLevel - 0.5f); break;
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