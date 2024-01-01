#ifndef INVRADIM_HPP
#define INVRADIM_HPP

#include "RadIm.hpp" // Include the header file for the base class

class InvRadIm : public RadIm {
public:
    void childFunction();
	void InitializeClass() const override;
    // Other members and functions specific to InvRadIm
	void InverseRadonTransform();	
};

#endif // INVRADIM_HPP

