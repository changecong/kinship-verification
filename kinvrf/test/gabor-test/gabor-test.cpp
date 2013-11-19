/*
 * Filename:      gabor-test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Thu Nov 14 12:52:01 2013
 * Modified at:   Sun Nov 17 09:05:48 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/gabor_filter.h"
#include "include/image_reader.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace kinvrf_fltr;
using namespace kinvrf_img;
using namespace cv;
using namespace std;

int main() {

    string path = "../../py/static/upload/family/41644d01.jpg";
    
    ImageReader* ir = new ImageReader(path);

    GaborFilter* gf = new GaborFilter(1, 1);
    
    Mat real = gf->kernel_real();
    Mat imag = gf->kernel_imag();

    Mat src = ir->image_gray();
    Mat dst(src.size(), CV_8UC1);
    gf->convert_image(src, dst);

    PCA pca(real, Mat(), CV_PCA_DATA_AS_ROW, 5);
    
    Mat subspace_feature = pca.project(real);
    
    // write into a xml file
    
    Mat eigen_values = pca.eigenvalues;
    Mat eigen_vectors = pca.eigenvectors;
    
    cout << "real : " << real.rows << " x " << real.cols << endl;
    cout << "subspace : " << subspace_feature.rows << " x " << subspace_feature.cols << endl;
    cout << "eigen value : " << eigen_values.rows << " x " << eigen_values.cols << endl;
    cout << "eigen value : " << eigen_values << endl;
    cout << "eigen vector : " << eigen_vectors.rows << " x " << eigen_vectors.cols << endl;

    

    // cout << real << endl;

    // imshow("hello", real);
    // imwrite("~/1.jpg", real);
    // waitKey();

    // imshow("hello", imag);
    // imwrite("~/2.jpg", imag);
    // waitKey();

    // imshow("hello", dst);
    // imwrite("~/3.jpg", dst);
    // waitKey();

    return 0;
}
