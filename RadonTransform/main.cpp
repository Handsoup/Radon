#include "RadIm.hpp"

int main() {

    // Declaring parameters
   std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/Images/small_sample.jpg";	
    int steps = 10;



    // Create object by passing values to the constructor
    RadIm obj(steps, imagepath);

    // Display the values using the member function
    //obj.displayValues();
    obj.PrintMatrix(obj.newImage);

	//obj.RotateOne();
	//obj.PrintMatrix(obj.rotatedImage);
	
	//std::cout << "element 7:" << static_cast<int>(obj.rotatedImage.at<uchar>(6,0)) << std::endl;//M(y,x)
	
	//std::cout << "sum of col 1:" << cv::sum(obj.rotatedImage.col(9))[0] << std::endl;
	obj.RadonTransform();
	obj.PrintTransformMatrix();

    return 0;
}

