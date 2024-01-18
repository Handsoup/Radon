#include "FilterWheel.hpp"
#include "VectorOperations.h"

#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <numeric>

constexpr double MOD = 998244353.0;

// Constructor implementation
FilterWheel::FilterWheel() {



}

// Convolution done by me

void FilterWheel::VectorFullConvolve(std::vector<double> vect, std::vector<double> kernel, std::vector<double>& result){
	
 	int vectorLength = vect.size();                                                                      
    int kernelLength = kernel.size();                                                                    
    int paddingLength; 
    
    if (kernelLength % 2 == 0) {                                                                           
        paddingLength = kernelLength/2;                                                                  
    }   
    else {                                                                                               
        paddingLength = (kernelLength - 1)/2;                                                            
    }   
    
    std::vector<double> newVect((vectorLength + 2 * paddingLength), 0);                                  
    
    // Padding                                                                                           
    for (int i = paddingLength; i < newVect.size() - paddingLength; i++) {                           
    
        newVect[i] = vect[i-paddingLength];                                                              
        
    }                                                                                                    
    
                                                                                                         
    std::vector<double> tmp(vectorLength, 0);                                                            
    
    // convolution                                                                                       
    for(int i = 0; i < tmp.size(); i++){                                                                 
        for(int j = 0; j < kernelLength; j++ ) {
            tmp[i] += newVect[i + j] * kernel[j];                                                        }
            
    }                                                                                                    
    
    result = tmp;    	
}

// Convolution from GeeksforGeeks website, the one I wrote is better for this application 

void FilterWheel::VectorConvolve(std::vector<double> vect, std::vector<double> kernel, std::vector<double>& result) {

    // Stores the size of arrays
    int n = vect.size(), m = kernel.size();

    // Resize the convolution array c[]
    result.resize(n + m - 1, 0.0);

    // Traverse the two given arrays
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Update the convolution array
            result[i + j] = fmod((result[i + j] + (vect[i] * kernel[j])), MOD);
        }

	}
}


double FilterWheel::SeppLoganMatrixFilterFunction(double x, double L){

	double result = ((L * L) / (2 * M_PI * M_PI * M_PI) * ((M_PI / 2) - L * 0.01 * (x-100) * sin(L * 0.01 * (x-100))) / ((M_PI / 2) * (M_PI / 2) - (L * 0.01 * (x-100)) * (L * 0.01 * (x-100))));
    return result;	

}

// bounds is how many steps will be in the positive and negative region of the function, simetrically
void FilterWheel::SeppLoganMatrixFilter(cv::Mat& matrix, double L) {

	int bounds = 500;

	std::vector<double> kernel(bounds*2+1,0);
	
	// Making the kernel -1 - 1  
	for(int i = 0; i < kernel.size(); i++) {

		kernel[i] = SeppLoganMatrixFilterFunction(i/5, L);

	}

	//PrintVector(kernel);

	// newImage is the matrix this function works on, it is CV_8UC1  
	cv::Mat tmp;
	tmp = cv::Mat::zeros(matrix.rows, matrix.cols, CV_64FC1);

	for(int i = 0; i < matrix.rows; i++) {
		
		std::vector<double> rowList(matrix.cols, 0);
		std::vector<double> convList(matrix.cols, 0);
	
		for(int j = 0; j < matrix.cols; j++) {

			rowList[j] = static_cast<double>(matrix.at<uchar>(i, j));

		}

		VectorFullConvolve(rowList, kernel, convList);

		for(int j = 0; j < matrix.cols; j++) {

			tmp.at<double>(i,j) = convList[j];

		}
	
	}
	
//	cv::imshow("Grayscale Image", tmp);
//	cv::waitKey(0);
//	std::cout << "tmp Matrix:\n"<< tmp << std::endl;	
	
	// normalizing and rounding and converting to uchar
	double min, max = 0;
	cv::minMaxIdx(tmp, &min, &max);

	for(int i = 0; i < matrix.rows; i++) {
		
		for(int j = 0; j < matrix.cols; j++) {

			double currentValue = static_cast<double>(matrix.at<uchar>(i, j));
			matrix.at<uchar>(i, j) = static_cast<uchar>(std::round((tmp.at<double>(i,j)-min)/(max-min)*255)); 

		}
	
	}

}
