#include "FrameProcessor.hpp"

FrameProcessor::FrameProcessor() {
    faceDetector.start();
}

FrameProcessor::~FrameProcessor() {
    faceDetector.stop();
}


void FrameProcessor::process(const cv::Mat& src, cv::Mat& dst, const KeyProcessor& keyProc) {
    
    KeyProcessor::Mode mode = keyProc.getMode();

    if (mode != KeyProcessor::ORIGINAL) {
        src.copyTo(dst);
    }

    switch (mode) {
        case KeyProcessor::INVERT: cv::bitwise_not(src, dst); break;
        case KeyProcessor::BLUR: cv::GaussianBlur(src, dst, cv::Size(11, 11), 0); break;
        
        case KeyProcessor::CANNY:
            cv::Canny(src, edges, 50, 150);
            cv::cvtColor(edges, dst, cv::COLOR_GRAY2BGR);
            break;

        case KeyProcessor::SOBEL:
            cv::Sobel(src, gx, CV_16S, 1, 0);
            cv::Sobel(src, gy, CV_16S, 0, 1);
            cv::convertScaleAbs(gx, gx);
            cv::convertScaleAbs(gy, gy);
            cv::addWeighted(gx, 0.5, gy, 0.5, 0, dst);
            break;

        case KeyProcessor::ZOOM: {

            float scale = keyProc.getZoomLevel();
            cv::Point center = keyProc.getZoomCenter();
            
            int pipWidth = 240;
            int pipHeight = 180;

            int roiW = pipWidth / scale;
            int roiH = pipHeight / scale;

            int x = center.x - roiW / 2;
            int y = center.y - roiH / 2;

            x = std::max(0, std::min(x, src.cols - roiW));
            y = std::max(0, std::min(y, src.rows - roiH));

            cv::Rect sourceRect(x, y, roiW, roiH);
            roi = src(sourceRect);

            cv::resize(roi, enlargedRoi, cv::Size(pipWidth, pipHeight), 0, 0, cv::INTER_LINEAR);

            cv::rectangle(enlargedRoi, cv::Rect(0,0,pipWidth, pipHeight), cv::Scalar(0,255,0), 2);

            cv::Rect destRect(dst.cols - pipWidth - 10, 10, pipWidth, pipHeight); // Відступ 10px
            
            enlargedRoi.copyTo(dst(destRect));

            cv::rectangle(dst, sourceRect, cv::Scalar(0, 255, 0), 1);
            break;
        }

        case KeyProcessor::FACE: {
            faceDetector.updateFrame(src);

            std::vector<cv::Rect> faces = faceDetector.getFaces();

            for (const auto& rect : faces) {
                cv::rectangle(dst, rect, cv::Scalar(0, 255, 0), 2);
                cv::putText(dst, "Face", cv::Point(rect.x, rect.y - 5),
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
            }
            break;
        }

        default:
            src.copyTo(dst);
            break;
    }
}