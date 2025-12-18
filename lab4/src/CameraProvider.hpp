#pragma once
#include <opencv2/opencv.hpp>

class CameraProvider {
private:
    cv::VideoCapture cap;

public:
    CameraProvider(int index, int width, int height);
    bool isOpened() const;

    bool getFrame(cv::Mat& frame);
};
