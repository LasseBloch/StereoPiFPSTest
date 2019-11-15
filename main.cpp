#include <iostream>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>

void captureFromTwoCams()
{
    std::cout << "How fast can we go two cams: " << std::endl;

    const auto numFrames{120};
    cv::VideoCapture capture0(0);
    capture0.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture0.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cv::VideoCapture capture1(1);
    capture1.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture1.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    // start time stamp
    auto startTime = std::chrono::system_clock::now();
    cv::Mat frame0;
    cv::Mat frame1;

    for(int n = 0; n < numFrames; n++)
    {
        capture0 >> frame0;
        capture1 >> frame1;
        cv::waitKey(1);
    }

    std::chrono::duration<float> elapsedTime = std::chrono::system_clock::now() - startTime;
    auto fps = numFrames / elapsedTime.count();
    std::cout << "Both cams results" << std::endl;
    std::cout << "Capturing from both cams: " << numFrames << " Frames took: " << elapsedTime.count() << std::endl;
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "FPS read from cam: " << capture0.get(cv::CAP_PROP_FPS) << std::endl;
    std::cout << "resolution read from cam: " << capture0.get(cv::CAP_PROP_FRAME_WIDTH) << " x " << capture0.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
}

void captureFromOneCam(int camNum, int width = 640, int height = 480)
{
    std::cout << "How fast can we go cam: " << camNum << std::endl;

    const auto numFrames{120};
    cv::VideoCapture capture(camNum);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    // start time stamp
    auto startTime = std::chrono::system_clock::now();
    cv::Mat frame;

    for(int n = 0; n < numFrames; n++)
    {
        capture >> frame;
    }

    std::chrono::duration<float> elapsedTime = std::chrono::system_clock::now() - startTime;
    auto fps = numFrames / elapsedTime.count();
    std::cout << "cam " << camNum <<  " results" << std::endl;
    std::cout << "Capturing: " << numFrames << " Frames took: " << elapsedTime.count() << std::endl;
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "FPS read from cam: " << capture.get(cv::CAP_PROP_FPS) << std::endl;
    std::cout << "resolution read from cam: " << capture.get(cv::CAP_PROP_FRAME_WIDTH) << " x " << capture.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
}

int main()
{
    std::cout << "Capturing with one cam" << std::endl;
    captureFromOneCam(0);
    std::cout << " Capturing with both cams" << std::endl;
    captureFromTwoCams();
    std::cout << "Capturing from 2 threads" << std::endl;
    std::thread t1(captureFromOneCam, 0,  640, 480);
    captureFromOneCam(1);
    t1.join();
    return 0;
}