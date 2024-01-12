#ifndef FILTERWHEEL_HPP
#define FILTERWHEEL_HPP

#include "VectorOperations.h"

#include <opencv2/opencv.hpp>
#include <vector>

class FilterWheel  {
	private:

	public:
	
		FilterWheel();
		
		void VectorFullConvolve(std::vector<double> vect, std::vector<double> kernel, std::vector<double>& result);
		void SeppLoganMatrixFilter(cv::Mat& Matrix, double L);
		double SeppLoganMatrixFilterFunction(double value, double L);
};

#endif // FILTERWHEEL_HPP

