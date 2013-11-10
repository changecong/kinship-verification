/*
 * Filename:      ml_knn.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 20:40:13 2013
 * Modified at:   Thu Nov  7 22:00:48 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/ml_knn.h";



// namespace
namespace kinvrf_ml {

    // before use classifier, the test data need to be proecessed just like trainning data
    // these two kinds of data are basically same, but we get them by different ways.
    void MlKNN::knn_classifier(int k, Data* test_data, Data* training_data) {

        if(NULL == *ir || !ir->image_is_read()) {
            // if ir is null or image hasn't been read
            // do something
        }

        // get image reader
        ImageReader* image_reader = *ir;
        // get matrix frome image reader
        Mat image_mat = image_reader->image_mat();

        //////////// knn steps /////////////////
        
        // 1. get the data number and feature number from training data
        // data number: row number = number of images
        // feature number: column number = number or pixels in each image


        // 2. calculate the sum(Fn - Tn)^2 with each row of tranning data

        // 3. get the k smallest (nearest) ones

        // 4. see who has more

    }



}  // namespace kinvrf_ml
