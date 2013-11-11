/*
 * Filename:      face-detector-test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Sun Nov 10 15:15:02 2013
 * Modified at:   Sun Nov 10 21:14:02 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/face_detector.h"
#include <iostream>

using namespace kinvrf_img;

int main(int argv, char** argc) {
        
   
    string path = argc[1];


    FaceDetector* fd = new FaceDetector(path);
    
    fd->eyes();
    
    Mat image = fd->image();

    std::cout << image.rows << " " << image.cols << endl;
    cv::imshow("hello", image);

    cv::waitKey();

    return 0;
}
