/*
 * Filename:      ml_knn.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 17:17:07 2013
 * Modified at:   Sun Nov 17 12:40:10 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_ML_KNN_H
#define KINVRF_ML_KNN_H

#include "image_reader.h"

///\namespace kinvrf_ml
///\brief Contains functions and classes which are defined for Machine Learning module of the project.
namespace kinvrf_ml {

    ///\class MlKNN
    ///\brief A class that used to perform knn verification.
    class MlKNN {

    public:
        
        ///\fn MlKNN()
        ///\brief The constructor.
        MlKNN() : 
            neg_percent_(-1.0) {};

        ///\fn ~MlKNN()
        ///\brief The distructor.
        ~MlKNN(){};
    
        ///\fn void classifier(int k, TestData* test_data, TrainData* train_data);
        ///\param [in] k          The number of the nearest neighbors.
        ///\param [in] test_data  An TestData object pointer which contains the test data.
        ///\param [in] train_data An TrainData object pointer wihch contains the training data.
        ///\brief Used to classify by KNN.
        void classifier(int k, TestData* test_data,
                        TrainData* train_data);

        ///\fn
        bool is_positive();

    private:

        ///\fn void init()
        void init();

        ///\fn void knn(int k, Mat& data)
        void knn(int k, Mat& data);

        ///\fn bool MlKNN::sort_by(pair<double, int>& arg0, pair<double, int>& arg1)
        ///\brief A helper funtion for sorting
        bool MlKNN::sort_by(pair<double, int>& arg0, pair<double, int>& arg1);

        Mat test_data_one_;   ///< First set of test data.
        Mat test_data_two_;   ///< Second set of test data.
        Mat train_data_pos_;  ///< The positive training data.
        Mat train_data_neg_;  ///< The negative training data.

        int row_number_;  ///< The row number of training data.

        double neg_percent_;

    };  // class MlKNN

}  // namespace kinvrf_ml

#endif  // KINVRF_ML_KNN_H
