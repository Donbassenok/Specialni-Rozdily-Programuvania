#include "CameraProvider.hpp"
#include "Logger.hpp"

CameraProvider::CameraProvider(int index) {
    Logger::getInstance().info("Attempting to open camera index: " + std::to_string(index));
    cap.open(index, cv::CAP_V4L2);
    if (!cap.isOpened()) {
        Logger::getInstance().warn("Could not open camera with API V4L2, trying default...");
        cap.open(index);
    }
}

bool CameraProvider::isOpened() const {
    return cap.isOpened();
}

bool CameraProvider::getFrame(cv::Mat& frame) {
    return cap.read(frame);
}