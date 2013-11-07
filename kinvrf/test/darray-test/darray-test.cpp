/*
 * Filename:      darray-test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Nov  5 23:16:06 2013
 * Modified at:   Wed Nov  6 21:10:17 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/util_data_inl.h"
#include <iostream>

#include <opencv2/opencv.hpp>

typedef unsigned char uchar;

using namespace kinvrf_ml;
using namespace std;
using namespace cv;

int main() {

    int** int_arr = (int **)dynamic_array(4, 5, sizeof(int));

    int_arr[0][0] = 1;
    int_arr[1][1] = 1;

    cout << "INT" << endl;
    cout << "(0, 0): " << int_arr[0][0] << endl;
    cout << "(1, 1): " << int_arr[1][1] << endl;
    cout << "(2, 2): " << int_arr[2][2] << endl;

    free_dynamic_array(int_arr);

    double** double_arr = (double **)dynamic_array(4, 5, sizeof(double));

    double_arr[0][0] = 1.0d;
    double_arr[1][1] = 1.0d;

    cout << "DOUBLE" << endl;
    cout << "(0, 0): " << double_arr[0][0] << endl;
    cout << "(1, 1): " << double_arr[1][1] << endl;
    cout << "(2, 2): " << double_arr[2][2] << endl;

    free_dynamic_array(double_arr);

    uchar** uchar_arr = (uchar **)dynamic_array(4, 5, sizeof(char));

    uchar* uchar_arr_1 = NULL;
    uchar_arr_1 = (uchar *) malloc(5*sizeof(uchar));
    memset(uchar_arr_1, 'a', 5*sizeof(uchar));
    uchar_arr[0] = uchar_arr_1;
    uchar_arr[1] = uchar_arr_1;
    uchar_arr[2] = uchar_arr_1;
    uchar_arr[3] = uchar_arr_1;

    cout << "UCHAR" << endl;
    cout << "(0, 0): " << uchar_arr[0][0] << endl;
    cout << "(1, 0): " << uchar_arr[1][0] << endl;
    cout << "(1, 1): " << uchar_arr[1][1] << endl;
    cout << "(1, 2): " << uchar_arr[1][2] << endl;
    cout << "(1, 3): " << uchar_arr[1][3] << endl;
    cout << "(1, 4): " << uchar_arr[1][4] << endl;
    cout << "(2, 2): " << uchar_arr[2][2] << endl;

    uchar* a = reshape_dynamic_array(4, 5, uchar_arr);

    Mat mat = Mat(4, 5, CV_8UC1, a);

    cout << "Mat :" << mat << endl;

    mat.release();

    cout << "Mat(c) :" << mat << endl;

    mat = Mat(1, 5, CV_8UC1, uchar_arr[1]);

    cout << "Mat(c) :" << mat << endl;

    free_dynamic_array(uchar_arr);


    uchar* data = (uchar *)malloc(sizeof(uchar)*5);
    memset(data, 'a', sizeof(uchar)*5);

    uchar** data_arr = (uchar **)dynamic_array(4, 5, sizeof(char));

    memcpy(data_arr[1], data, sizeof(uchar)*5);

    cout << "DATA" << endl;
    cout << "(1,0): " << data_arr[1][0] << endl;
    cout << "(1,2): " << data_arr[1][2] << endl;
    
    return 0;
}
