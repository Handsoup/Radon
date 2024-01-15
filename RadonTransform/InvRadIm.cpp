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
	buffer =  cv::Mat::zeros(rows, cols, CV_64FC1);


	steps = newImage.rows;
	angleSteps = - CalculateAngle(steps);

	transformMatrix.resize(rows, std::vector<double>(cols, 0));

	transformedImage =  cv::Mat::zeros(rows, cols, CV_8UC1);

	stepNumber = 0;

	//}}}
	
}

void InvRadIm::InvRotateOne() {

	//{{{
	// Define the center of rotation
    cv::Point2f center((static_cast<float>(buffer.cols)-1) / 2, static_cast<float>((buffer.rows)-1) / 2);

    // Get the rotation matrix
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angleSteps * stepNumber, 1.0);

    // Apply the affine transformation
    cv::warpAffine(buffer, buffer, rotationMatrix, buffer.size());
		
	stepNumber++;



    // Display the original and rotated images
    /*cv::imshow("Original Image", newImage);
    cv::imshow("Rotated Image", rotatedImage);
    cv::waitKey(0);*/

    // Save the rotated image
	// cv::imwrite("path_to_save_rotated_image.jpg", rotatedImage);
	
	//}}}
	
}

void InvRadIm::SeppLoganFilter(double L) {
	
		Filter.SeppLoganMatrixFilter(newImage, L);	

}

void InvRadIm::Fill(int n) {

	//originalImage nth row -> rotatedImage
	//accessing matrix elements: .at<type>(y,x) y,x are the coordinates of the matrix elements
	
	for(int i = 0; i < rotatedImage.rows; i++) {

		for(int j = 0; j < rotatedImage.cols; j++) {

			rotatedImage.at<double>(i,j) = rotatedImage.at<double>(i,j) + static_cast<double>(newImage.at<uchar>(n, j));


		}
	}	
	
//	std::cout << rotatedImage << std::endl;

}

void InvRadIm::Fill2(cv::Mat& matrix, int n) {

	//originalImage nth row -> rotatedImage
	//accessing matrix elements: .at<type>(y,x) y,x are the coordinates of the matrix elements
	//this function fills the nth row of the radontransformed image into a matrix
	
	for(int i = 0; i < matrix.rows; i++) {

		for(int j = 0; j < rotatedImage.cols; j++) {

			matrix.at<double>(i,j) =  static_cast<double>(newImage.at<uchar>(n, j));


		}
	}	
	
//	std::cout << rotatedImage << std::endl;

}

void InvRadIm::SetAngleStep(double s) {

	angleSteps = s;

}

void InvRadIm::InverseRadonTransform() {	

	// Rotating and filling in the values
	for(int i = 0; i < steps + 1; i++ ) {

		Fill2(buffer, i);

		InvRotateOne();

		for(int i = 0; i < rotatedImage.rows; i++) {

			for(int j = 0; j < rotatedImage.cols; j++) {

				rotatedImage.at<double>(i,j) = rotatedImage.at<double>(i,j) + buffer.at<double>(i, j);


			}
		}

		

	}
	
//	cv::imshow("Grayscale Image", rotatedImage);
  //  cv::waitKey(0); 


	// Getting max and min of rotatedImage
	cv::minMaxIdx(rotatedImage, &min, &max);		



	// Constructing the transformedImage and averaging the individual pixels
	for(int i = 0; i < transformedImage.rows; i++) {
		
		for(int j = 0; j < transformedImage.cols; j++) {

			//transformedImage.at<uchar>(i,j) = static_cast<uchar>(std::round(rotatedImage.at<double>(i, j))/steps);
			transformedImage.at<uchar>(i,j) = static_cast<uchar>(std::round((rotatedImage.at<double>(i, j)-min)/(max-min)*255));

		}
	
	}
	SaveMatrixAsImage(transformedImage, "nofilterIMG.jpg");	




	for(int i = 0; i < transformedImage.rows; i++) {
		
		for(int j = 0; j < transformedImage.cols; j++) {

			if(transformedImage.at<uchar>(i, j) <= 217) {

				transformedImage.at<uchar>(i, j) = static_cast<uchar>(217); 

			}
		}
	
	}

	min, max = 0;
	cv::minMaxIdx(transformedImage, &min, &max);

	for(int i = 0; i < transformedImage.rows; i++) {
		
		for(int j = 0; j < transformedImage.cols; j++) {

			transformedImage.at<uchar>(i, j) = ((transformedImage.at<uchar>(i,j)-min)/(max-min))*255; 

		}
	
	}
	



//	std::cout << transformedImage << std::endl;

	//constructing and std::vector for storing the image
	ConvertMatrixTo2DVector(transformedImage, transformMatrix);

}

void InvRadIm::ConvertMatrixTo2DVector(cv::Mat& matrix, std::vector<std::vector<double>>& vect) {

	for(int i = 0; i < matrix.rows; i++) {
		
		for(int j = 0; j < matrix.cols; j++) {

			vect[i][j] = static_cast<double>(matrix.at<uchar>(i, j));

		}
	
	}

}





