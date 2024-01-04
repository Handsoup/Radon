#include "RadIm.hpp"
#include "InvRadIm.hpp"
#include "CSVHandler.hpp"
#include "VectorOperations.h"

#include <vector>

int main() {

	// Radon transform
		
	  // {{{

    // Declaring parameters
   	//std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/build/white_circle.png";	
	std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/Images/SheppLogan_Phantom.svg.png";
	//std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/Images/small_sample.jpg";

	int steps = 50;



    // Create object by passing values to the constructor
    RadIm radobj(steps, imagepath);

    //obj.PrintMatrix(obj.newImage);

	
	
	radobj.RadonTransform();
	//obj.PrintTransformMatrix();

	radobj.SaveTransformMatrixAsCSV("transformedimg.csv");

//	radobj.SaveMatrixAsImage(radobj.transformedImage, "img2.png");	
	radobj.SaveMatrixAsImage(radobj.transformedImage, "smallout.png");	
  
	// }}}
	

	// Here comes the inverse
		
	//std::string transformedimagepath = "/home/peppermintlarry/Radon/RadonTransform/build/img2.png";	
	//std::string transformedimagepath = "/home/peppermintlarry/Radon/RadonTransform/build/smallout.png";	

	std::string transformedimagepath = "/home/peppermintlarry/Radon/RadonTransform/build/smallout.png";
	
	InvRadIm invradobj(transformedimagepath);
		
	std::cout << invradobj.newImage << std::endl;
	std::cout << invradobj.transformedImage << std::endl;

	invradobj.SaveMatrixAsImage(invradobj.transformedImage, "invrad2.jpg");

	invradobj.InverseRadonTransform();
	

	std::cout << invradobj.rotatedImage << std::endl;

	invradobj.SaveTransformMatrixAsCSV("invIMG.csv");
	
	invradobj.SaveMatrixAsImage(invradobj.transformedImage, "invradout.jpg");
	
	
		

	
		
	

    return 0;
}

