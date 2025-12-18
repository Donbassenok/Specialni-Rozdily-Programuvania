#include <opencv2/opencv.hpp>
#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Logger.hpp"
#include "ConfigManager.hpp"

void onMouse(int event, int x, int y, int flags, void* userdata) {
    KeyProcessor* keyProc = (KeyProcessor*)userdata;
    if (event == cv::EVENT_MOUSEMOVE) {
        keyProc->updateMouse(x, y);
    }
}

int main() {
    ConfigManager::getInstance().loadConfig("settings.json");

    int camId = ConfigManager::getInstance().getCameraId();
    int width = ConfigManager::getInstance().getFrameWidth();
    int height = ConfigManager::getInstance().getFrameHeight();
    
    std::string logLevel = ConfigManager::getInstance().getLogLevel();
    if (logLevel == "DEBUG") Logger::getInstance().setLevel(LogLevel::DEBUG);
    else if (logLevel == "WARN") Logger::getInstance().setLevel(LogLevel::WARN);
    else if (logLevel == "ERROR") Logger::getInstance().setLevel(LogLevel::ERROR);
    else Logger::getInstance().setLevel(LogLevel::INFO);

    Logger::getInstance().info("Application started"); 

    Logger::getInstance().info("Opening camera " + std::to_string(camId) + " with resolution " + std::to_string(width) + "x" + std::to_string(height));

    CameraProvider camera(camId, width, height);
    
    if (!camera.isOpened()) {
        Logger::getInstance().error("Failed to open camera with ID: " + std::to_string(camId));
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