#include <opencv2/opencv.hpp>

int main() {
    // Load your image
    cv::Mat image = cv::imread("/home/peppermintlarry/Radon/RadonTransform/Images/SheppLogan_Phantom.svg.png");

    if (image.empty()) {
        std::cerr << "Could not read the image." << std::endl;
        return -1;
    }

    // Define the center of rotation
    cv::Point2f center(static_cast<float>(image.cols) / 2, static_cast<float>(image.rows) / 2);

    // Get the rotation matrix
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, 10.0, 1.0);

    // Apply the affine transformation
    cv::Mat rotatedImage;
    cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());

    // Display the original and rotated images
    cv::imshow("Original Image", image);
    cv::imshow("Rotated Image", rotatedImage);
    cv::waitKey(0);

    // Save the rotated image
    cv::imwrite("path_to_save_rotated_image.jpg", rotatedImage);

    return 0;
}

