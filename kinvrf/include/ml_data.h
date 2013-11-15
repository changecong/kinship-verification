/*
 * Filename:      ml_data.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov  6 10:42:43 2013
 * Modified at:   Wed Nov 13 13:56:50 2013
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

        Data(){};
        
      private:

        ///\fn
        ///\brief
        virtual void get_data() = 0;

        // methods that used for data processing

    };  // class Data

}  // kinvrf_ml

#endif  // KINVRF_ML_DATA_H
