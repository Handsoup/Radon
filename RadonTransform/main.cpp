#include "RadIm.hpp"

int main() {

	std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/Images/heart-ct_1.jpg";	
    int steps = 100;
    // Create object by passing values to the constructor
    RadIm obj(steps, imagepath);

    // Display the values using the member function
    obj.displayValues();

    return 0;
}

