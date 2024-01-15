#include "RadIm.hpp"
#include "InvRadIm.hpp"
#include "CSVHandler.hpp"
#include "VectorOperations.h"
#include "Alarm.h"
#include "FilterWheel.hpp"
#include "CSVHandler.hpp"

#include <vector>
#include <cmath>
#include <string> 

int main() {

	//Reading the input parameters from csv file
	CSVHandler input;
	std::vector<std::vector<std::string>> inputParameters;

	input.Load2DStringVectorFromCSV(inputParameters, "../input.csv", ';');
	// in inputParameters[cols][rows]
	Print2DVector(inputParameters);
	std::cout << inputParameters[0][1] << std::endl;

	


	


	// Radon transform
	// {{{

    // Declaring parameters
   //	std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/build/white_circle.png";
//	std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/Images/smallcirc.png";	

	std::string imagepath = inputParameters[0][1];
	//std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/Images/small_sample.jpg";

	int steps = std::stoi(inputParameters[1][1]);



    // Create object by passing values to the constructor
    RadIm radobj(steps, imagepath);

    //obj.PrintMatrix(obj.newImage);

	
	radobj.RadonTransform();
	//obj.PrintTransformMatrix();
	std::cout << "eddig ok" << std::endl;
	radobj.SaveTransformMatrixAsCSV(inputParameters[3][1]);

//	radobj.SaveMatrixAsImage(radobj.transformedImage, "img2.png");	
	radobj.SaveMatrixAsImage(radobj.transformedImage, inputParameters[2][1]);	
 
 	// }}} 
	

	// Here comes the inverse
	//std::string transformedimagepath = "/home/peppermintlarry/Radon/RadonTransform/build/img2.png";	
	//std::string transformedimagepath = "/home/peppermintlarry/Radon/RadonTransform/build/filtered.png";	
	std::string transformedimagepath = inputParameters[4][1];
	
	InvRadIm invradobj(transformedimagepath);
		
	//std::cout << invradobj.newImage << std::endl;
	//std::cout << invradobj.transformedImage << std::endl;

	//invradobj.SaveMatrixAsImage(invradobj.transformedImage, "invrad2.jpg");

	// Filtering
	invradobj.SeppLoganFilter(200);
	invradobj.SaveMatrixAsImage(invradobj.newImage, inputParameters[5][1]);


	invradobj.InverseRadonTransform();


	//std::cout << invradobj.rotatedImage << std::endl;

	invradobj.SaveTransformMatrixAsCSV(inputParameters[7][1]);

//	std::cout << invradobj.transformedImage << std::endl;
	invradobj.displayValues();

	invradobj.SaveMatrixAsImage(invradobj.transformedImage, inputParameters[6][1]);

	playSound(120, 1.0);



	return 0;
}

