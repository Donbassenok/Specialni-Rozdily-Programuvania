#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0); // камера №0

    if (!cap.isOpened()) {
        std::cerr << "Не вдалося відкрити камеру!" << std::endl;
        return -1;
    }

    cv::Mat frame;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Малювання тексту
        cv::putText(
            frame,
            "Hello World!",
            cv::Point(30, 50),
            cv::FONT_HERSHEY_SIMPLEX,
            1.0,
            cv::Scalar(0, 255, 0), // зелений
            2
        );

        // Малювання кола
        cv::circle(frame, cv::Point(200, 200), 50, cv::Scalar(255, 0, 0), 3);

        // Малювання прямокутника
        cv::rectangle(frame, cv::Rect(300, 100, 150, 100), cv::Scalar(0, 0, 255), 3);

        // Показ кадру
        cv::imshow("Camera Window", frame);

        // Вихід при натисканні ESC
        if (cv::waitKey(1) == 27) break;
    }

    return 0;
}
