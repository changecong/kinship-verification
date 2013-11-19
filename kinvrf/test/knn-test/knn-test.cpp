/*
 * Filename:      knn-test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov  6 15:24:09 2013
 * Modified at:   Sun Nov 17 14:55:07 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/ml_test_data.h"
#include "include/ml_train_data.h"
#include "include/ml_knn.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace kinvrf_ml;
using namespace cv;

int main() {

    // // DataRes dr;
    kinvrf_ml::TrainData trainData = kinvrf_ml::TrainData();

    // Mat temp_pos = trainData->train_data_pos();
    
    // cout << temp_pos.cols << endl;

    // Mat temp_neg = trainData->train_data_neg();
    
    // cout << temp_neg.cols << endl;

    // // 
    string path0 = "../../res/img/KinFace_V2/01_part/38L1.bmp";
    string path1 = "../../res/img/KinFace_V2/03_part/";
    string path2 = "L1.bmp";

    int is = 0;
    int isnot = 0;

    for (int i = 0; i < 200; ++i) {

        string path3 = path1 + to_string(i) + path2;
        TestData testData = TestData(path0, path3);

        // imshow("test", testData->test_data_one());
        // waitKey();

        // cout << testData->test_data_one().cols << endl;

        // // imshow("test", testData->test_data_two());
        // // waitKey();

        // cout << testData->test_data_two().cols << endl;

        // test DataRes
    
        // string path = "../../res/img/KinFace_V2/02_part/";

        // DataRes* dr = new DataRes(path);
    
        // dr->gen_eigen_vectors();

        // test
        MlKNN* knn = new MlKNN();

        knn->classifier(21, testData, trainData);

        bool ret = knn->is_positive();

        if (ret) {
            // cout << "True" << endl;
            is++;
        } else {
            // cout << "False" << endl;
            isnot++;
        }

    }

    cout << "true: " << is << endl;
    cout << "false: " << isnot << endl;

    return 0;
}

