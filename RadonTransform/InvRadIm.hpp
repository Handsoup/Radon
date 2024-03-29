#ifndef INVRADIM_HPP
#define INVRADIM_HPP

#include "RadIm.hpp" // Include the header file for the base class
#include "FilterWheel.hpp"

class InvRadIm : public RadIm {


public:

	std::string invpath;
	cv::Mat buffer;

	InvRadIm(const std::string& pt);	

	void InverseRadonTransform();
	
	void InitializeClass() override;
	
	FilterWheel Filter;
	void SeppLoganFilter(double L);

	void InvRotateOne();
	void Fill(int n);
	void Fill2(cv::Mat& matrix, int n);


	void SetAngleStep(double s);
	void ConvertMatrixTo2DVector(cv::Mat& matrix, std::vector<std::vector<double>>& vect);	

};

#endif // INVRADIM_HPP

