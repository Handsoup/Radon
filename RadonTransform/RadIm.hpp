#ifndef RADIM_HPP
#define RADIM_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

#include "CSVHandler.hpp"
#include "VectorOperations.h"

class RadIm {
public:

	// variables	
    double steps;
    std::string path;
    double angleSteps;
	double min, max;
	int stepNumber = 1;	

	// Default constructor
	RadIm(); 

	// Constructor with parameters
    RadIm(double step, const std::string& pth);

	// Variables
	double rows, cols = 0;
    cv::Mat originalImage;
    cv::Mat newImage;
	cv::Mat rotatedImage;
	cv::Mat rotatedImageInit;
	cv::Mat transformedImage;
	std::vector<std::vector<double>> transformMatrix;
	CSVHandler csvHandler;

	// Functions
    virtual void InitializeClass();
    void displayValues();
    double CalculateAngle(double steps);
    void PrintMatrix(const cv::Mat& matrix);
	void RotateOne();
	void PrintTransformMatrix();

	// This function saves a 2d std vector containing the Radon transformed image as individual pixel values
	void SaveTransformMatrixAsCSV(const std::string& savename);

	// With this function any cv::Mat can be saved as an image
	void SaveMatrixAsImage(const cv::Mat& matrix, const std::string& name);

	// This function fills a matrix containing zeros with the values of the vector, only works for grayscale 1 channel matrixes
	void Convert2DVectorToMatrix(std::vector<std::vector<double>>& vect, cv::Mat& matrix);

	void RadonTransform();
};

#endif /* RADIM_HPP */

