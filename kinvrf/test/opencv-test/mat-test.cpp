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
