#include "CameraProvider.hpp"

CameraProvider::CameraProvider(int index) {
    cap.open(index, cv::CAP_V4L2);
}

bool CameraProvider::isOpened() const {
    return cap.isOpened();
}

bool CameraProvider::getFrame(cv::Mat& frame) {
    return cap.read(frame);
}