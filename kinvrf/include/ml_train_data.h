/*
 * Filename:      ml_train_data.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Nov 12 23:06:27 2013
 * Modified at:   Wed Nov 13 13:59:34 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_ML_TRAIN_DATA_H
#define KINVRF_ML_TRAIN_DATA_H

#include "ml_data.h"  // class Data opencv

using namespace cv;

namespace kinvrf_ml {

    class TrainData : public Data {

      public:

        ///\fn
        ///\brief
        TrainData();

        ///\fn
        ///\brief
        Mat train_data_pos();

        ///\fn
        ///\brief
        Mat train_data_neg();

      private:

        ///\fn
        ///\brief initialization
        void init();

        ///\fn
        ///\brief
        void get_data();

        ///\fn
        ///\brief get paths from setting
        vector<string> get_paths_from_setting();

        Mat train_data_pos_;
        Mat train_data_neg_;

        vector<string> paths_;
        
    };  // class TrainData
    
}  // namespace kinvrf_ml

#endif  // KINVRF_ML_TRAIN_DATA_H
