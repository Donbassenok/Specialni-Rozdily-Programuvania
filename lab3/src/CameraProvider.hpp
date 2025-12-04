#pragma once
#include <opencv2/opencv.hpp>

class CameraProvider {
private:
    cv::VideoCapture cap;

public:
    CameraProvider(int index = 0);
    cv::Mat getFrame();
    bool isOpened() const;
};