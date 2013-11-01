/*
 * Filename:      ml_knn.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 20:40:13 2013
 * Modified at:   Tue Oct 29 21:01:06 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/ml_knn.h";



// namespace
namespace kinvrf_ml {

    void MlKNN::knn_classifier(int k, ImageReader* ir, TrainData* td) {

        if(NULL == *ir || !ir->image_is_read()) {
            // if ir is null or image hasn't been read
            // do something
        }

        // get image reader
        ImageReader* image_reader = *ir;
        // get matrix frome image reader
        Mat image_mat = image_reader->image_mat();

    }



}  // namespace kinvrf_ml
