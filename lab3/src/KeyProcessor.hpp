#pragma once
#include <opencv2/opencv.hpp>

class KeyProcessor {
public:
    enum Mode {
        ORIGINAL,
        INVERT,
        BLUR,
        CANNY,
        SOBEL,
        ZOOM,
        FACE 
    };

private:
    Mode mode;
    float zoomLevel;      
    cv::Point zoomCenter; 

public:
    KeyProcessor();
  
    void processKey(int key);
    
    void updateMouse(int x, int y);

    Mode getMode() const;
    float getZoomLevel() const;
    cv::Point getZoomCenter() const;
};