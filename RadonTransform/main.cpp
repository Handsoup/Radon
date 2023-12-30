#include "RadIm.hpp"
#include "CSVHandler.hpp"
#include "VectorOperations.h"

#include <vector>

int main() {

    // Declaring parameters
   	std::string imagepath = "/home/peppermintlarry/Radon/RadonTransform/build/white_circle.png";	
    int steps = 600;



    // Create object by passing values to the constructor
    RadIm obj(steps, imagepath);

    //obj.PrintMatrix(obj.newImage);

	
	
	obj.RadonTransform();
	//obj.PrintTransformMatrix();

	obj.SaveTransformMatrixAsCSV("proba.csv");

	std::cout << "eddig ok " << std::endl;
	
	obj.SaveMatrixAsImage(obj.transformedImage, "img2.png");	
	
	// Here comes the inverse
	
		




    return 0;
}

