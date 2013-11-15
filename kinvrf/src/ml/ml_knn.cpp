/*
 * Filename:      ml_knn.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 20:40:13 2013
 * Modified at:   Wed Nov 13 18:00:26 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/ml_knn.h"
#include "include/ml_test_data_h"  // class TestData
#include "include/ml_train_data_h"  // class TrainData

// namespace
namespace kinvrf_ml {
    

    // before use classifier, the test data need to be proecessed just like trainning data
    // these two kinds of data are basically same, but we get them by different ways.
    void MlKNN::classifier(int k, TestData* test_data, TrainData* train_data) {

        test_data_one_ = test_data->test_data_one();
        test_data_two_ = test_data->test_data_two();

        test_data_pos_ = train_data->train_data_pos();
        test_data_neg_ = train_data->train_data_neg();

        // for test data one
        

        // for test data two
    }

    void 

    double MlKNN::knn(k, Mat* data) {
        Mat test_data = *data;
        int i = train_data_pos_.rows;
        vector<double> sums;

        for ()

        // compare with each train data
    }



}  // namespace kinvrf_ml
