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

};

#endif // INVRADIM_HPP

