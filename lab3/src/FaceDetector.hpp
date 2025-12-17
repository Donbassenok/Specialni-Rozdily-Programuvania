#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

class FaceDetector {
private:
    std::thread workerThread;      
    std::mutex dataMutex;          
    std::atomic<bool> stopFlag;    
    std::atomic<bool> hasNewFrame; 

    cv::Mat currentFrame;         
    std::vector<cv::Rect> detectedFaces;
    cv::dnn::Net net;             

    void worker();

public:
    FaceDetector();
    ~FaceDetector();

    void start(); 
    void stop();  
    
    void updateFrame(const cv::Mat& frame);
    
    std::vector<cv::Rect> getFaces();
};