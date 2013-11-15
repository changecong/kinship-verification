/*
 * Filename:      ml_knn.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 17:17:07 2013
 * Modified at:   Wed Nov 13 18:00:13 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_ML_KNN_H
#define KINVRF_ML_KNN_H

#include "image_reader.h"

namespace kinvrf_ml {

///\class
///\brief a class that contain static function used to perform knn verification
    class MlKNN {

    public:
    
        MlKNN(){};
        ~MlKNN(){};
    
        ///\fn
        ///\brief used to classify
        ///\param k: k nearest neighbor
        ///       ir: ImageReader object contains image information
        ///       td: The training data
        static void classifier(int k, TestData* test_data,
                                   TrainData* train_data);

    private:

        // helper methods
        void init();

        void knn(int k, Mat* data);

        Mat test_data_one_;
        Mat test_data_two_;
        Mat train_data_pos_;
        Mat train_data_neg_;

        int row_number_;  ///< the row number of training data
    

    };

}  // namespace kinvrf_ml

#endif  // KINVRF_ML_KNN_H
