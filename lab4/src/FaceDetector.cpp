#include "FaceDetector.hpp"
#include <iostream>

FaceDetector::FaceDetector() : stopFlag(false), hasNewFrame(false) {
    std::string protoPath = std::string(RESOURCES_PATH) + "deploy.prototxt";
    std::string modelPath = std::string(RESOURCES_PATH) + "res10_300x300_ssd_iter_140000.caffemodel";
    try {
        net = cv::dnn::readNetFromCaffe(protoPath, modelPath);
    } catch (const cv::Exception& e) {
        std::cerr << "FaceDetector Error: " << e.what() << std::endl;
    }
}

FaceDetector::~FaceDetector() {
    stop();
}

void FaceDetector::start() {
    stopFlag = false;
    workerThread = std::thread(&FaceDetector::worker, this);
}

void FaceDetector::stop() {
    stopFlag = true;
    if (workerThread.joinable()) {
        workerThread.join();
    }
}

void FaceDetector::updateFrame(const cv::Mat& frame) {
    std::lock_guard<std::mutex> lock(dataMutex);
    frame.copyTo(currentFrame);
    hasNewFrame = true;
}

std::vector<cv::Rect> FaceDetector::getFaces() {
    std::lock_guard<std::mutex> lock(dataMutex);
    return detectedFaces;
}

void FaceDetector::worker() {
    while (!stopFlag) {
        cv::Mat frameToProcess;
        bool shouldProcess = false;

        {
            std::lock_guard<std::mutex> lock(dataMutex);
            if (hasNewFrame && !currentFrame.empty()) {
                currentFrame.copyTo(frameToProcess);
                hasNewFrame = false;
                shouldProcess = true;
            }
        }

        if (shouldProcess) {
            cv::Mat blob = cv::dnn::blobFromImage(frameToProcess, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0));
            net.setInput(blob);
            
            cv::Mat detections = net.forward();

            std::vector<cv::Rect> faces;
            cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

            for (int i = 0; i < detectionMat.rows; i++) {
                float confidence = detectionMat.at<float>(i, 2);

                if (confidence > 0.5) {
                    int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameToProcess.cols);
                    int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameToProcess.rows);
                    int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameToProcess.cols);
                    int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameToProcess.rows);

                    faces.push_back(cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2)));
                }
            }

            {
                std::lock_guard<std::mutex> lock(dataMutex);
                detectedFaces = faces;
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
}