#ifndef RADIM_HPP
#define RADIM_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

class RadIm {
private:
    double steps;
    std::string path;
    double angleSteps;

public:
    // Constructor with parameters
    RadIm(double step, const std::string& pth);

	// Variables
	double rows, cols = 0;
    cv::Mat originalImage;
    cv::Mat newImage;
	cv::Mat rotatedImage;
	std::vector<std::vector<double>> transformMatrix;

	// Functions
    void InitializeClass(const std::string& pth);
    void displayValues();
    double CalculateAngle(double steps);
    void PrintMatrix(const cv::Mat& matrix);
	void RotateOne();
	void PrintTransformMatrix();
	void SaveTransformMatrix(const std::string& savename);	

	void RadonTransform();
};

#endif /* RADIM_HPP */

