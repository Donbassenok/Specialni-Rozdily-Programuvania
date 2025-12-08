#pragma once
#include <opencv2/opencv.hpp>
#include "KeyProcessor.hpp"

class FrameProcessor {
private:
    cv::Mat edges; 
    cv::Mat gx, gy;   
    cv::Mat roi, enlargedRoi; 

public:
    void process(const cv::Mat& src, cv::Mat& dst, const KeyProcessor& keyProc);
};