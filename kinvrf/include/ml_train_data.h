/*
 * Filename:      ml_train_data.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Nov 12 23:06:27 2013
 * Modified at:   Sun Nov 17 11:37:25 2013
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

        ///\enum DATAFORMAT
        ///\brief Determint the data comes from images or xml file.
        enum DATAFORMAT {
            IMAGE_DATA = 0,  ///< from image data
            XML_DATA   = 1   ///< from xml file
        };


        ///\fn
        ///\brief initialization
        void init();

        ///\fn
        ///\brief
        void get_data();

        ///\fn int get_data_format()
        ///\return A DATAFORMAT enum.
        ///\brief get the traning data format from settings.xml
        DATAFORMAT get_data_format();

        ///\fn string get_younger_data()
        ///\return A string value.
        ///\brief Get the data set xml file of younger person from settings.xml
        string get_younger_xml();

        ///\fn string get_elder_data()
        ///\return A string value.
        ///\brief Get the data set xml file of elder person from settings.xml
        string get_elder_xml();

        ///\fn string get_younger_mat_name()
        ///\return A string value.
        ///\brief Get the mat data name of younger person from settings.xml
        string get_younger_mat_name();

        ///\fn string get_younger_mat_name()
        ///\return A string value.
        ///\brief Get the mat data name of elder person from settings.xml
        string get_elder_mat_name();

        ///\fn
        ///\brief get paths from setting
        vector<string> get_paths_from_setting();

        Mat train_data_pos_;
        Mat train_data_neg_;

        vector<string> paths_;
        
    };  // class TrainData
    
}  // namespace kinvrf_ml

#endif  // KINVRF_ML_TRAIN_DATA_H
