#include <opencv2/opencv.hpp>
#include <cmath>

#include "InvRadIm.hpp"
#include "CSVHandler.hpp"

// Constructor implementation
InvRadIm::InvRadIm(const std::string& pt) : invpath(pt) {


        InitializeClass();
}

void InvRadIm::InitializeClass() {

	//{{{
	path = invpath;
	// !ATTENTION! The program expects a grayscale image
	originalImage = cv::imread(path, cv::IMREAD_GRAYSCALE);
	
	if (originalImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
       
    }
	
	originalImage.convertTo(newImage, CV_8UC1);

	// Now calculate cols rows of original picture and steps and angles
	
	// originalImage.cols is the original image's sides length
	
	rows = newImage.cols;
	cols = newImage.cols;
	
	

	// CV_64FC1 because of the overlapping values huge containers are needed -> 64 bit pixels
	rotatedImage =  cv::Mat::zeros(rows, cols, CV_64FC1);

	steps = newImage.rows - 1;
	angleSteps = - CalculateAngle(steps);
	//}}}
	
}

void InvRadIm::InverseRadonTransform() {



}

void InvRadIm::Fill(int n) {

	//originalImage nth row -> rotatedImage
	//accessing matrix elements: .at<type>(y,x) y,x are the coordinates of the matrix elements
	
		for(int i = 0; i < rotatedImage.rows; i++) {

			for(int j = 0; j < rotatedImage.cols; j++) {

				rotatedImage.at<double>(i,j) = static_cast<double>(newImage.at<uchar>(n, j));


			}

		}	

}

void InvRadIm::SetAngleStep(double s) {

	angleSteps = s;

}









