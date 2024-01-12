#include "FilterWheel.hpp"
#include "VectorOperations.h"

#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <numeric>

// Constructor implementation
FilterWheel::FilterWheel() {



}


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

double FilterWheel::SeppLoganMatrixFilterFunction(double x, double L){

    double result = ((L * L) / (2 * M_PI * M_PI * M_PI) * ((M_PI / 2) - L * (x) * sin(L * (x))) / ((M_PI / 2) * (M_PI / 2) - (L * (x)) * (L * (x))));
    return result;	

}

// res is how many points you sample the Sepp Logan function
void FilterWheel::SeppLoganMatrixFilter(cv::Mat& matrix, double L) {

	int bounds = 500;

	std::vector<double> kernel(bounds*2+1,0);
	
	// Making the kernel -1 - 1  
	for(int i = 0; i < kernel.size(); i++) {

		kernel[i] = (SeppLoganMatrixFilterFunction((i/(1000)*2-1), L));

	}

	//Normailize
	
	int sum = std::accumulate(kernel.begin(), kernel.end(), 0);
	
	
	for(int i = 0; i < kernel.size(); i++) {

		kernel[i] = kernel[i]/sum;

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

//	std::cout << "tmp Matrix:\n"<< tmp << std::endl;	

	// normalizing and rounding and converting to uchar remains
	double min, max = 0;
	cv::minMaxIdx(tmp, &min, &max);

	for(int i = 0; i < matrix.rows; i++) {
		
		for(int j = 0; j < matrix.cols; j++) {

			double currentValue = static_cast<double>(matrix.at<uchar>(i, j));
			matrix.at<uchar>(i, j) = static_cast<uchar>(std::round((tmp.at<double>(i,j)-min)/(max-min)*255)); 

		}
	
	}

}
