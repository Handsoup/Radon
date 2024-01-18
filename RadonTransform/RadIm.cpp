#include "RadIm.hpp"
#include <opencv2/opencv.hpp>
#include <cmath>
#include "CSVHandler.hpp"
#include "VectorOperations.h"

// Constructor implementations
RadIm::RadIm() { 

	// Default constructor it is used by the child class	
	steps = 0;
	path = "-1 NO PATH";
	angleSteps = 0;

}

RadIm::RadIm(double step, const std::string& pth) : steps(step), path(pth) {

	angleSteps=CalculateAngle(steps);

        InitializeClass();
}


void RadIm::displayValues() {

    std::cout << "Steps: " << steps << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Angle: " << angleSteps << std::endl;

}

double RadIm::CalculateAngle(double steps) {

	return 180.0/steps;
}

void RadIm::InitializeClass() {

	// {{{

	originalImage = cv::imread(path); 
    
    if (originalImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
       
    }

    // Calculate the dimensions for the new image
    double newS = sqrt(pow(originalImage.rows,2)+pow(originalImage.cols,2))+1; // Twice the size of the larger dimension, the plus one is because the cv::Mat wants an int parameter and to prevent data loss because of the typecast

    int newSize = static_cast<int>(newS);

    // Create a black square image with dimensions based on the new size
   	// !ATTENTION! CV_8UC3 means an 8 bit 3 channel unsigned char image so its not grayscale
    newImage = cv::Mat::zeros(newSize, newSize, CV_8UC3);
	rotatedImage =  cv::Mat::zeros(newSize, newSize, CV_64FC1);


    
    // Calculate the center of the new image
    cv::Point center(newSize / 2, newSize / 2);
    
    
    // Calculate the position for placing the original image in the center of the new image
    int offsetX = (newSize - originalImage.cols) / 2;
    int offsetY = (newSize - originalImage.rows) / 2;
    cv::Rect roi(offsetX, offsetY, originalImage.cols, originalImage.rows);
    
    // Copy the original image onto the new image on top of the square
    originalImage.copyTo(newImage(roi));
	
	// Convert newImage to grayscale in place
    cv::cvtColor(newImage, newImage, cv::COLOR_BGR2GRAY);
	
	// Copy initial state of image to the rotatedImage
	//newImage.copyTo(rotatedImage);
	rotatedImage = cv::Mat::zeros(newImage.rows, newImage.cols, CV_64FC1);
	rotatedImageInit = cv::Mat::zeros(newImage.rows, newImage.cols, CV_64FC1);

	for(int i = 0; i < newImage.rows; i++) {
		
		for(int j = 0; j < newImage.cols; j++) {

			rotatedImageInit.at<double>(i, j) = static_cast<double>(newImage.at<uchar>(i, j));

		}
	
	}


    // Display the grayscale image (optional)
    //cv::imshow("Grayscale Image", newImage);
    //cv::waitKey(0); // Wait for a key press

    // Save the image with the original image placed on top of the white circle, inside the black square
    // cv::imwrite("image_with_circle_and_square3.png", newImage);
	
		
	// properties of the transformed image
	cols = newSize;
	rows = steps; 
	transformMatrix.resize(rows, std::vector<double>(cols, 0));

//	doubleTransformedImage =  cv::Mat::zeros(rows, cols, CV_64FC1);
	transformedImage =  cv::Mat::zeros(rows, cols, CV_8UC1);


	//}}}
	
}

void RadIm::PrintMatrix(const cv::Mat& matrix) {
    std::cout << matrix << std::endl;
}

// Applies angleSteps degree rotation once to rotationMatrix
void RadIm::RotateOne() {

	//{{{
	// Define the center of rotation
    cv::Point2f center((static_cast<float>(rotatedImage.cols)-1) / 2, static_cast<float>((rotatedImage.rows)-1) / 2);

    // Get the rotation matrix
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angleSteps * stepNumber, 1.0);

    // Apply the affine transformation
    cv::warpAffine(rotatedImageInit, rotatedImage, rotationMatrix, rotatedImageInit.size(), cv::INTER_LINEAR);

	stepNumber++;
    // Display the original and rotated images
    /*cv::imshow("Original Image", newImage);
    cv::imshow("Rotated Image", rotatedImage);
    cv::waitKey(0);*/

    // Save the rotated image
	// cv::imwrite("path_to_save_rotated_image.jpg", rotatedImage);
	
	//}}}
	
}

void RadIm::SaveMatrixAsImage(const cv::Mat& matrix, const std::string& name) {
	
	
	cv::imwrite(name, matrix);

}

void RadIm::RadonTransform() {

	//{{{
	
	//in one loop: sum columns into nth subvector of our vector then rotate one and repeat
	for(int i = 0; i < rows; i++) {

		for(int j = 0; j < cols; j++) {
		
			transformMatrix[i][j] = std::round(cv::sum(rotatedImage.col(j))[0]);
		
		}

		RotateOne();
	
	}
	

	// Turning transformMatrix to cv::Mat to be able to save the transformed Image

	Convert2DVectorToMatrix(transformMatrix, transformedImage);	
	//}}}
	
}

void RadIm::PrintTransformMatrix() {

	//{{{
	
	std::cout << "Current state of transform matrix:" << std::endl;
    for (int i = 0; i < rows; ++i) {
    	for (int j = 0; j < cols; ++j) {
            std::cout << transformMatrix[i][j] << ", ";
        }
        std::cout << std::endl;
    }

	//}}}
	
}

void RadIm::SaveTransformMatrixAsCSV(const std::string& savename) {

	csvHandler.Write2DVectorToCSV(transformMatrix, savename);	

}

void RadIm::Convert2DVectorToMatrix(std::vector<std::vector<double>>& vect, cv::Mat& matrix) {
   
	//{{{   
	
	// !ATTENTION! The matrix should be unsigned char for this function to work
	if (vect.size() != matrix.rows || vect[0].size() != matrix.cols) {
        std::cerr << "Error: Input vector dimensions do not match matrix dimensions." << std::endl;
        return;
    }
	
	//get max and min
	FindMinMax(vect, min, max);
	
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            matrix.at<uchar>(i, j) = static_cast<uchar>(std::round((vect[i][j]-min)/(max-min)*255));
        }
    }
	
	//}}}
	
}























