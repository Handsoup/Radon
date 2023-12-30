#include "RadIm.hpp"
#include <opencv2/opencv.hpp>
#include <cmath>
#include "CSVHandler.hpp"

// Constructor implementation
RadIm::RadIm(double step, const std::string& pth) : steps(step), path(pth) {

	angleSteps=CalculateAngle(steps);

        InitializeClass(path);
}

void RadIm::displayValues() {

    std::cout << "Steps: " << steps << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Angle: " << angleSteps << std::endl;

}

double RadIm::CalculateAngle(double steps) {

	return 360.0/steps;
}

void RadIm::InitializeClass(const std::string& pth) {

	// {{{

	originalImage = cv::imread(pth); 
    
    if (originalImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
       
    }

    // Calculate the dimensions for the new image
    double newS = sqrt(pow(originalImage.rows,2)+pow(originalImage.cols,2))+1; // Twice the size of the larger dimension, the plus one is because the cv::Mat wants an int parameter and to prevent data loss because of the typecast

    int newSize = static_cast<int>(newS);

    // Create a black square image with dimensions based on the new size
   
    newImage = cv::Mat::zeros(newSize, newSize, CV_8UC3);
	rotatedImage =  cv::Mat::zeros(newSize, newSize, CV_8UC3);


    // Calculate the radius of the circle (half of the new image's side)
    int radius = newSize / 2;
    
    // Calculate the center of the new image
    cv::Point center(newSize / 2, newSize / 2);
    
    // Draw the white circle
    cv::circle(newImage, center, radius, cv::Scalar(0, 0, 0), -1); // -1 indicates filled circle
    
    // Calculate the position for placing the original image in the center of the new image
    int offsetX = (newSize - originalImage.cols) / 2;
    int offsetY = (newSize - originalImage.rows) / 2;
    cv::Rect roi(offsetX, offsetY, originalImage.cols, originalImage.rows);
    
    // Copy the original image onto the new image on top of the white circle
    originalImage.copyTo(newImage(roi));
	
	// Convert newImage to grayscale in place
    cv::cvtColor(newImage, newImage, cv::COLOR_BGR2GRAY);
	
	// Copy initial state of image to the rotatedImage
	newImage.copyTo(rotatedImage);

    // Display the grayscale image (optional)
    //cv::imshow("Grayscale Image", newImage);
    //cv::waitKey(0); // Wait for a key press

    // Save the image with the original image placed on top of the white circle, inside the black square
    // cv::imwrite("image_with_circle_and_square3.png", newImage);
	
	
	cols = newSize;
	rows = steps + 1; 
	transformMatrix.resize(rows, std::vector<double>(cols, 0));

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
    cv::Point2f center(static_cast<float>(rotatedImage.cols) / 2, static_cast<float>(rotatedImage.rows) / 2);

    // Get the rotation matrix
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angleSteps, 1.0);

    // Apply the affine transformation
    cv::warpAffine(rotatedImage, rotatedImage, rotationMatrix, rotatedImage.size());

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

	//in one loop: sum columns into nth subvector of our vector then rotate one and repeat
	for(int i = 0; i < rows; i++) {

		for(int j = 0; j < cols; j++) {
		
			transformMatrix[i][j] = std::round(cv::sum(rotatedImage.col(j))[0]/cols);
		
		}

		RotateOne();
	
	}
	

	// Turning transformMatrix to cv::Mat to be able to save the transformed Image

	// itt van a hiba
	// Check if angles vector is not empty to avoid runtime errors
	
	Convert2DVectorToMatrix(transformMatrix, transformedImage);	


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
    if (vect.size() != matrix.rows || vect[0].size() != matrix.cols) {
        std::cerr << "Error: Input vector dimensions do not match matrix dimensions." << std::endl;
        return;
    }

    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            matrix.at<uchar>(i, j) = static_cast<uchar>(vect[i][j]);
        }
    }
}























