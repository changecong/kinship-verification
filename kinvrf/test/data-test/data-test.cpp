/*
 * Filename:      data-test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov  6 15:24:09 2013
 * Modified at:   Sun Nov 17 11:43:49 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/ml_test_data.h"
#include "include/ml_train_data.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace kinvrf_ml;
using namespace cv;

int main() {

    // // DataRes dr;
    kinvrf_ml::TrainData* trainData = new kinvrf_ml::TrainData();

    Mat temp_pos = trainData->train_data_pos();
    
    cout << temp_pos.cols << endl;

    Mat temp_neg = trainData->train_data_neg();
    
    cout << temp_neg.cols << endl;

    // // 
    string path0 = "../../py/static/upload/person/41644d01/0.jpg";
    string path1 = "../../py/static/upload/person/41644d01/1.jpg";
    TestData* testData = new TestData(path0, path1);

    // imshow("test", testData->test_data_one());
    // waitKey();

    cout << testData->test_data_one().cols << endl;

    // imshow("test", testData->test_data_two());
    // waitKey();

    cout << testData->test_data_two().cols << endl;

    // test DataRes
    
    // string path = "../../res/img/KinFace_V2/02_part/";

    // DataRes* dr = new DataRes(path);
    
    // dr->gen_eigen_vectors();

    return 0;
}

