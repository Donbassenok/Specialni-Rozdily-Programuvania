#include <opencv2/opencv.hpp>
#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"

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

        if (key == 27) break;
    }
    return 0;
}