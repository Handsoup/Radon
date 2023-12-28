#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

int main() {
    // Read the original image
    cv::Mat originalImage = cv::imread("/home/peppermintlarry/Radon/RadonTransform/Images/heart-ct_1.jpg"); // Replace with your image path
    
    if (originalImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // Calculate the dimensions for the new image
    double newS = sqrt(pow(originalImage.rows,2)+pow(originalImage.cols,2))+1; // Twice the size of the larger dimension
    int newSize = static_cast<int>(newS);

    // Create a black square image with dimensions based on the new size
    cv::Mat newImage(newSize, newSize, CV_8UC3, cv::Scalar(0, 0, 0)); // Black background
    
    // Calculate the radius of the circle (half of the new image's side)
    int radius = newSize / 2;
    
    // Calculate the center of the new image
    cv::Point center(newSize / 2, newSize / 2);
    
    // Draw the white circle
    cv::circle(newImage, center, radius, cv::Scalar(255, 255, 255), -1); // -1 indicates filled circle
    
    // Calculate the position for placing the original image in the center of the new image
    int offsetX = (newSize - originalImage.cols) / 2;
    int offsetY = (newSize - originalImage.rows) / 2;
    cv::Rect roi(offsetX, offsetY, originalImage.cols, originalImage.rows);
    
    // Copy the original image onto the new image on top of the white circle
    originalImage.copyTo(newImage(roi));

    // Save the image with the original image placed on top of the white circle, inside the black square
    cv::imwrite("image_with_circle_and_square.png", newImage);

    // new section
      return 0;
}

