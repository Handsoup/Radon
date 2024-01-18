# Implementing Radon-transform and it's inverse and Sepp-Logan filtering 

This project implements Radon transform and it's inverse in C++ for medical imaging applications.

It even has a usefull csv reader/writer header, a sound playing header for alarm applications and a header for useful std vector operations that can be used in future projects. 

This project has the following parts:
1. Alarm.h
2. CMakeLists.txt
3. CSVHandler.cpp CSVHandler.hpp
4. FilterWheel.cpp FilterWheel.hpp
5. input.csv
6. InvRadIm.cpp InvRadim.hpp
7. main.cpp
8. RadIm.cpp RadIm.hpp
9. VectorOperations.h

# Alarm

This header file has a function that generates an n sec long f frequency signal to the speakers using the SFML package.

# CMakeLists.txt

I use cmake to make compilying the program easier. It collects and manages all the dependencies.

# CSVHandler

It has 3 methods one for writing a 2d std vector to csv file, one for loading a csv file into a 2d std vector, and one for doing the same but the std vector is a string vector.

# FilterWheel

It is a class that has methods associated with filtering. It implements the Sepp Logan filter and samples it in 1001 points. It even has vector convolution methods that are accessable outside the class.

# input.csv

Thanks to this file the input files can be modified without recompiling the code. It has the different input parameters under each other, and before any parameter there is a short description for what that parameter sets.

# InvRadIm

This implements the inverse radon transform. This inherits from the radon transform class. The class has an Initialization methods for filtering thanks to having a FilterWheel member. The most important methods of this class are InverseRadonTransform Fill2 and RotateOne. InverseRadonTransform does the radon transforms inverse for this it uses the Fill2 which the nth row of a matrix to another matrix, adding the values to the new matrix. InvRotateOne rotates the input sinogramm with an angle step that is derived from the row number of the sinogramm. The rotatio After that using RotateOne and a loop the image is rotated and all the values in each rows are summed and saved as the consecutive rows of the output image. RotateOne rotates the original image in each steps with increasing angles.n is always done by using the original image and rotating it with increasing angles. The output is saved as an image and as a .csv at the end. the image is noramlized using the max and min values of pixels after the transform to the 0-255 range, after that a histogram smoothing is done to make the contrast better.

# main

In the main from input.txt the input data is read into the corresponding variables and after that first a Radon-transform is made than the created image is filtered using a Sepp-Logan filter and after that it is inverse Radon-Transformed. The Radon-transformed image the filtered image and the inverse radontransformed image is saved as images and the transformed images are also saved as csv files.

# RadIm

This implements the radon transform of an image. First the image is put into the middle of a black square. The square has dimensions as big as the image can freely rotate in it without touching it's borders thus decreasing the chance that some crucial information is lost at the corners of the image during the rotations. After that using RotateOne and a loop the image is rotated and all the values in each rows are summed and saved as the consecutive rows of the output image. RotateOne rotates the original image in each steps with increasing angles. after the transform the image is normalized using the max and min values of the pixels in the transformed matrix and fitted to the 0-255 interval.

# VectorOperations

It has functions for printing any std vectors 1 and 2 dimensional ones  using a template and a function to find min and max of a 2d vector.
