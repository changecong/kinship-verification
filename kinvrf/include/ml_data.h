/*
 * Filename:      ml_data.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov  6 10:42:43 2013
 * Modified at:   Sat Nov 16 21:58:40 2013
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

///\namespace kinvrf_ml
///\brief Contains functions and classes which are defined for Machine Learning module of the project.
namespace kinvrf_ml {

    ///\class Data
    ///\brief A base class abstract the data part of the project.
    class Data {

      public:

        ///\fn Data();
        ///\brief The constructor.
        Data(){};
        
      private:

        ///\fn virtual void get_data() = 0
        ///\brief A pure virtual function which must be defined by the derived classes. 
        virtual void get_data() = 0;

        // methods that used for data processing

    };  // class Data

}  // kinvrf_ml

#endif  // KINVRF_ML_DATA_H
