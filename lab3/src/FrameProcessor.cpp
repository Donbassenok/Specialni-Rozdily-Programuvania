#include "FrameProcessor.hpp"

cv::Mat FrameProcessor::process(const cv::Mat& frame, KeyProcessor::Mode mode) {
    cv::Mat out;

    switch (mode) {
        case KeyProcessor::INVERT:
            cv::bitwise_not(frame, out);
            break;

        case KeyProcessor::BLUR:
            cv::GaussianBlur(frame, out, cv::Size(11, 11), 0);
            break;

        case KeyProcessor::CANNY:
            cv::Canny(frame, out, 50, 150);
            cv::cvtColor(out, out, cv::COLOR_GRAY2BGR);
            break;

        case KeyProcessor::SOBEL: {
            cv::Mat gx, gy;
            cv::Sobel(frame, gx, CV_16S, 1, 0);
            cv::Sobel(frame, gy, CV_16S, 0, 1);
            cv::convertScaleAbs(gx, gx);
            cv::convertScaleAbs(gy, gy);
            cv::addWeighted(gx, 0.5, gy, 0.5, 0, out);
            break;
        }

        default:
            out = frame.clone();
            break;
    }

    return out;
}