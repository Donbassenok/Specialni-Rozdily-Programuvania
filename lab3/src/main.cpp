#include <opencv2/opencv.hpp>
#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "FaceDetector.hpp"

void onMouse(int event, int x, int y, int flags, void* userdata) {
    KeyProcessor* keyProc = (KeyProcessor*)userdata;
    if (event == cv::EVENT_MOUSEMOVE) {
        keyProc->updateMouse(x, y);
    }
}

int main() {
    CameraProvider camera(0); 
    if (!camera.isOpened()) return -1;

    KeyProcessor keyProc;
    FrameProcessor frameProc;
    FaceDetector faceDetector;

    cv::Mat rawFrame;
    cv::Mat processedFrame;
    
    cv::namedWindow("Camera");
    cv::setMouseCallback("Camera", onMouse, &keyProc);

    faceDetector.start();

    while (true) {
        if (!camera.getFrame(rawFrame)) break;

        int key = cv::waitKey(1);
        keyProc.processKey(key);

        if (keyProc.getMode() == KeyProcessor::FACE) {
            faceDetector.updateFrame(rawFrame);
        }

        frameProc.process(rawFrame, processedFrame, keyProc);

        if (keyProc.getMode() == KeyProcessor::FACE) {
             std::vector<cv::Rect> faces = faceDetector.getFaces();
             for (const auto& rect : faces) {
                 cv::rectangle(processedFrame, rect, cv::Scalar(0, 255, 0), 2);
                 cv::putText(processedFrame, "Face", cv::Point(rect.x, rect.y - 5),
                             cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
             }
        }

        cv::imshow("Camera", processedFrame);

        if (key == 27) break;
    }
    
    faceDetector.stop();
    return 0;
}