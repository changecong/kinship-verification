/*
 * Filename:      mat-test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Oct 23 15:03:05 2013
 * Modified at:   Wed Oct 23 15:19:42 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main() {

    string imagename("lena.jpg");

    Mat image = imread(imagename, 0);

    printf("the mat width is %d, height is %d\n", image.rows, image.cols);

    return 0;
}
