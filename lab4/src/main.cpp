#include <opencv2/opencv.hpp>
#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Logger.hpp"

void onMouse(int event, int x, int y, int flags, void* userdata) {
    KeyProcessor* keyProc = (KeyProcessor*)userdata;
    if (event == cv::EVENT_MOUSEMOVE) {
        keyProc->updateMouse(x, y);
    }
}

int main() {
    Logger::getInstance().setLevel(LogLevel::INFO);
    Logger::getInstance().info("Application started"); 

    CameraProvider camera(0); 
    if (!camera.isOpened()) {
        Logger::getInstance().error("Failed to open camera!");
        return -1;
    }
    Logger::getInstance().info("Camera opened successfully");

    KeyProcessor keyProc;
    FrameProcessor frameProc;

    cv::Mat rawFrame;
    cv::Mat processedFrame;
    
    cv::namedWindow("Camera");
    cv::setMouseCallback("Camera", onMouse, &keyProc);

    while (true) {
        if (!camera.getFrame(rawFrame)) break;

        int key = cv::waitKey(1);
        keyProc.processKey(key);

        frameProc.process(rawFrame, processedFrame, keyProc);

        cv::imshow("Camera", processedFrame);

        if (key == 27) {
            Logger::getInstance().info("ESC pressed. Exiting application.");
            break;
        }
    }
    return 0;
}