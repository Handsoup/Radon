#ifndef INVRADIM_HPP
#define INVRADIM_HPP

#include "RadIm.hpp" // Include the header file for the base class

class InvRadIm : public RadIm {


public:
	
	std::string invpath;

	InvRadIm(const std::string& pt);	

	void InverseRadonTransform();
	
	void InitializeClass() override;
	
	void Fill(int n);
	
	void SetAngleStep(double s);
	void ConvertMatrixTo2DVector(cv::Mat& matrix, std::vector<std::vector<double>>& vect);	

};

#endif // INVRADIM_HPP

