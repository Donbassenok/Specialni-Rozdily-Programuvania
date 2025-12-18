#include "CameraProvider.hpp"
#include "Logger.hpp"

CameraProvider::CameraProvider(int index, int width, int height) {
    cap.open(index, cv::CAP_V4L2);
    
    if (!cap.isOpened()) {
        cap.open(index);
    }

    if (cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    }
}

bool CameraProvider::isOpened() const {
    return cap.isOpened();
}

bool CameraProvider::getFrame(cv::Mat& frame) {
    return cap.read(frame);
}