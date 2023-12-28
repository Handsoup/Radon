#ifndef RADIM_HPP
#define RADIM_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

class RadIm {
private:
    double steps;
    std::string path;
    double angleSteps;

public:
    // Constructor with parameters
    RadIm(double step, const std::string& pth);

    cv::Mat originalImage;
    cv::Mat newImage;
    void InitializeInputImage(const std::string& pth);
    void displayValues();
    double CalculateAngle(double steps);
};

#endif /* RADIM_HPP */

