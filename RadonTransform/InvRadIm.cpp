#include <opencv2/opencv.hpp>
#include <cmath>

#include "InvRadIm.hpp"
#include "CSVHandler.hpp"

// Constructor implementation
InvRadIm::InvRadIm(const std::string& pth) : path(pth) {


        InitializeClass();
}



void InvRadIm::childFunction() {
    // Accessing public functions of the RadIm class
    publicFunction1(); // Accessible due to inheritance
    publicFunction2(); // Accessible due to inheritance
    // Other operations specific to InvRadIm class
}

// Other member function definitions for InvRadIm

void InvRadIm::InitializeClass() {

	//{{{
	originalImage = cv::imread(path);
	
	if (originalImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
       
    }

	// Now calculate cols rows of original picture and steps and angles
	
	// originalImage.cols is the original image's sides length
	
	rows, cols = originalImage.cols;

	rotatedImage =  cv::Mat::zeros(rows, cols, CV_8UC1);

	steps = originalImage.rows - 1;
	angleSteps = -CalculatedAngle(steps);
	//}}}
	
}

void InvRadIm::InverseRadonTransform() {



}
