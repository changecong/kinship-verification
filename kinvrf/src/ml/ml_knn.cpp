/*
 * Filename:      ml_knn.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 20:40:13 2013
 * Modified at:   Sun Nov 17 22:01:19 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/ml_knn.h"

#include <algorithm>  // std::max 
#include <vector>  // std::vector
#include <iostream>  // std::cout, std::endl

using namespace std;

// namespace
namespace kinvrf_ml {
    

    // before use classifier, the test data need to be proecessed just like trainning data
    // these two kinds of data are basically same, but we get them by different ways.
    void MlKNN::classifier(int k, TestData& test_data, kinvrf_ml::TrainData& train_data) {

        test_data_one_ = test_data.test_data_one();  // child - old parent
        // test_data_two_ = test_data.test_data_two();
        

        train_data_pos_ = train_data.train_data_pos();  // child - young parent
        train_data_neg_ = train_data.train_data_neg();

        // do knn
        neg_percent_ = knn(15, test_data_one_);
        // neg_percent_ = knn(31, test_data_two_);
    }

    double MlKNN::neg_percent() {
        return neg_percent_;
    }

    bool MlKNN::is_positive() {
        if(neg_percent_ < 0) {
            //Todo error
        }
        
        // printf("neg_percent_: %f\n", neg_percent_);

        if(neg_percent_ >= 0.50) {
            return false;
        } else {
            return true;
        }
    }


    double MlKNN::knn(int k, Mat& data) {
        Mat test_data = data;
        vector<pair<double, int>> sums;  // pos label 0, neg label 1

        // for positive data
        for (size_t i = 0; i < train_data_pos_.rows; i++) {
            
            Mat row = Mat(1, train_data_pos_.cols, CV_32FC1, train_data_pos_.ptr<double>(i));
            // calculation
            Mat diff = test_data - row;
            Mat pow2 = diff.mul(diff);
            
            double sum = 0;
            MatConstIterator_<double> it = pow2.begin<double>();
            MatConstIterator_<double> it_end = pow2.end<double>();
            for(; it != it_end; ++it) {
                sum += *it;
                // printf("sum: %f\n", sum);
            }

            sums.push_back(make_pair(sum, 0));
        }

        
        // for negative data
        for (size_t i = 0; i < train_data_neg_.rows; i++) {

            Mat row = Mat(1, train_data_neg_.cols, CV_32FC1, train_data_neg_.ptr<double>(i));
            // calculation
            Mat diff = test_data - row;
            Mat pow2 = diff.mul(diff);
            double sum = 0;
            MatConstIterator_<double> it = pow2.begin<double>(), it_end = pow2.end<double>();
            for(; it != it_end; ++it) {
                sum += *it;
                // printf("sum: %f\n", sum);
            }

            sums.push_back(make_pair(sum, 1));
        }

        // sort the sums
        std::sort(sums.begin(), sums.end(), kinvrf_ml::sort_by);

        // compare with each train data
        double neg = 0;
        for (int i = 0; i < k; ++i) {
            // printf("sum: %d\n", sums[i].second);
            neg += sums[i].second; 
        }

        // return the result
        return (double)(neg/k);
    }

    bool sort_by(const pair<double, int>& arg0,
                 const pair<double, int>& arg1) {
        
        return arg0.first < arg1.first;  // ASC
    }
            

}  // namespace kinvrf_ml
