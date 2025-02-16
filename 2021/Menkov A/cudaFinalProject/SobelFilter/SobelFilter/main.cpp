//
// Sobel Edge Detection Filter using CUDA
//
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;


extern "C" bool sobelFilter_GPU_wrapper(const cv::Mat & input, cv::Mat & output);
extern "C" bool sobelFilter_CPU(const cv::Mat & input, cv::Mat & output);

// Program main
int main(int argc, char** argv) {

    // name of image
    string image_name = "sample";

    // input & output file names
    string input_file = image_name + ".jpeg";
    string output_file_cpu = image_name + "_cpu.jpeg";
    string output_file_gpu = image_name + "_gpu.jpeg";

    // Read input image 
    cv::Mat srcImage = cv::imread(input_file, CV_LOAD_IMAGE_UNCHANGED);
    if (srcImage.empty())
    {
        std::cout << "Image Not Found: " << input_file << std::endl;
        return -1;
    }
    cout << "\ninput image size: " << srcImage.cols << " " << srcImage.rows << " " << srcImage.channels() << "\n";

    // convert RGB to gray scale
    cv::cvtColor(srcImage, srcImage, CV_BGR2GRAY);

    // Declare the output image  
    cv::Mat dstImage(srcImage.size(), srcImage.type());

    // run sobel edge detection filter on GPU  
    sobelFilter_GPU_wrapper(srcImage, dstImage);
    // normalization to 0-255
    dstImage.convertTo(dstImage, CV_32F, 1.0 / 255, 0);
    dstImage *= 255;
    // Output image
    imwrite(output_file_gpu, dstImage);

    // run sobel edge detection filter on CPU  
    sobelFilter_CPU(srcImage, dstImage);
    // normalization to 0-255
    dstImage.convertTo(dstImage, CV_32F, 1.0 / 255, 0);
    dstImage *= 255;
    // Output image
    imwrite(output_file_cpu, dstImage);

    return 0;
}