#include "FilterWheel.hpp"
#include <opencv2/opencv.hpp>
#include <cmath>

// Constructor implementation
FilterWheel::FilterWheel() {



}

FilterWheel::SeppLoganMatrixFilterFunction(double x, double L){

    double result = (L * L) / (2 * M_PI * M_PI * M_PI) * ((M_PI / 2) - L * x * sin(L * x)) / ((M_PI / 2) * (M_PI / 2) - (L * x) * (L * x));
    return result;	

}

FilterWheel::SeppLoganMatrixFilter(cv::Mat& matrix, double L) {
	
	// newImage is the matrix this function works on, it is CV_8UC1  
	cv::Mat tmp;
	tmp = cv::Mat::zeroes(matrix.rows, matrix.cols, CV_64FC1);

	for(int i = 0; i < matrix.rows; i++) {
		
		for(int j = 0; j < matrix.cols; j++) {

			double currentValue = static_cast<double>(matrix.at<uchar>(i, j));
			tmp.at<double>(i, j) = SeppLoganMatrixFilterFunction(currentValue, L); 

		}
	
	}

	// normalizing and rounding and converting to uchar remains

}
