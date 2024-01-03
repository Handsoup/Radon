#include "RadIm.hpp"
#include "InvRadIm.hpp"
#include "CSVHandler.hpp"
#include "VectorOperations.h"

#include <vector>

int main() {

	// Radon transform
		
	  /* {{{

    // Declaring parameters
   	std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/build/white_circle.png";	
    int steps = 600;



    // Create object by passing values to the constructor
    RadIm radobj(steps, imagepath);

    //obj.PrintMatrix(obj.newImage);

	
	
	radobj.RadonTransform();
	//obj.PrintTransformMatrix();

	radobj.SaveTransformMatrixAsCSV("transformedimg.csv");

	radobj.SaveMatrixAsImage(radobj.transformedImage, "img2.png");	
	  
	}}}*/
	

	// Here comes the inverse
		
	//std::string transformedimagepath = "/home/peppermintlarry/Radon/RadonTransform/build/img3.png";	
	std::string transformedimagepath = "/home/peppermintlarry/Radon/RadonTransform/Images/small_sample.jpg";	

	InvRadIm invradobj(transformedimagepath);

	
	invradobj.PrintMatrix(invradobj.newImage);
	
	
//	invradobj.PrintMatrix(invradobj.rotatedImage);
	invradobj.Fill(0);
	invradobj.PrintMatrix(invradobj.rotatedImage);
	invradobj.SetAngleStep(90.0);
	invradobj.RotateOne();
	invradobj.PrintMatrix(invradobj.rotatedImage);
	invradobj.displayValues();
	std::cout << invradobj.rotatedImage.cols << invradobj.rotatedImage.rows << std::endl;

//	std::cout << "here comes the test" << std::endl;
	
		

	for (int i = 0; i < invradobj.newImage.cols; ++i) {
    std::cout << static_cast<int>(invradobj.newImage.at<uchar>(0, i)) << std::endl;
}

	

    return 0;
}

