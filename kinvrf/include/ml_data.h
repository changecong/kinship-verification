/*
 * Filename:      ml_data.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov  6 10:42:43 2013
 * Modified at:   Tue Nov 12 00:02:47 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_ML_DATA_H
#define KINVRF_ML_DATA_H

#include "util_data_inl.h"
#include "data_resource.h"
#include <opencv2/opencv.hpp>  // Mat

using namespace cv;

namespace kinvrf_ml {

    // declare an abstract class which is Data
    class Data {

      public:

        Data();

        ///\fn
        ///\brief
        Mat data_mat();
        
      private:

        ///\fn
        ///\brief
        virtual void get_data() = 0;

        Mat data_mat_;

    };  // class Data

}  // kinvrf_ml

#endif  // KINVRF_ML_DATA_H
