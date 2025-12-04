#include <opencv2/opencv.hpp>
#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"

int main() {
    CameraProvider camera(0);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Camera not found!\n";
        return -1;
    }

    KeyProcessor keyProc;
    FrameProcessor frameProc;
    Display display;

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        int key = cv::waitKey(1);
        keyProc.processKey(key);

        cv::Mat processed = frameProc.process(frame, keyProc.getMode());
        display.show(processed);

        if (key == 27) break;
    }
}