/*
 * Filename:      data_resource.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 21:20:56 2013
 * Modified at:   Wed Nov  6 22:49:21 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   For each image, we use one single channel and set the size to 
 *                100px X 127px. In the data basic we use, we have 200 image for
 *                each kind of data, thus in order to store all this data, we
 *                need to allocate a size of 200 x 100 x 127 x 4 Bytes = 10160000 Bytes
 *                = 9921.875 KByte = 9 MBytes
 *
 */

#ifndef KINVRF_TRAINING_DATA_H
#define KINVRF_TRAINING_DATA_H

#include "image_reader.h"
#include <opencv2/opencv.hpp>

using namespace cv;

namespace kinvrf_ml {

    enum DATARES {
        KINVRF_DATA_FROM_KINSHIP_V2_IMAGE = 0,
        KINVRF_DATA_FROM_KINSHIP_V2_TEXT  = 1,
        KINVRF_DATA_FROM_EXTERNAL_IMAGE   = 2,
        KINVRF_DATA_FROM_EXTERNAL_TEXT    = 3,
        KINVRF_DATA_FROM_INTERNAL_SETTING = 4
    };

    ///\class DataRes
    ///\brief Basicall, we may have multiple set of data that need to be used.
    ///       For each set of data, we put them into a different folder. Thus,
    ///       each folder will conrrespoding to a DataRes object.
    ///       For example:
    ///       res/img/child/       => DataRes child = DataRes(data_res, 
    ///                                                       "res/img/child/");
    ///       res/img/youngparent/ => DataRes yparent = DataRes(data_res, 
    ///                                                         "res/img/youngparent/");
    ///       res/img/oldparent/   => DataRes oldparent = DataRes(data_res,
    ///                                                           "res/img/oldparent/");

    class DataRes {

      public:
        ///\fn
        ///\brief default constructor, the data come from settings 
        ///       in xml file.
        DataRes();

        ///\fn
        ///\brief
        explicit DataRes(const string& s);

        ///\fn
        ///\brief specify where the data comes from
        DataRes(DATARES data_res, const string& s);

        ///\fn
        ///\brief the distructor
        ~DataRes();      

        ///\fn
        ///\brief set the data path
        void image_data_path(const string &s);

        ///\fn
        ///\brief
        Mat data_mat();

        ///\fn
        ///\brief re-generate the matrix after changing the path or other options
        void renew();

        
      private:

        ///\fn
        ///\brief get the method from settings
        DATARES get_data_method();

        ///\fn
        ///\brief
        void get_data(DATARES data_res);

        void get_data_from_image();

        // helper functions
        ///\fn
        ///\brief get image number from settings
        void image_number();

        ///\fn
        ///\brief get image data path from settings
        ///       like: "../../res/img/"
        void image_data_path();

        ///\fn
        ///\brief get image name prefix from settings
        ///       like: "child"
        void image_name_prefix();

        ///\fn
        ///\brief
        void image_name_suffix();

        ///\fn
        ///\brief
        void image_type_suffix();

        ///\fn
        ///\brief
        string string_setting(const string name);


        DATARES data_res_;

        // used when method is set to 
        // KINVRF_DATA_FROM_KINSHIP_V2_IMAGE
        //              or
        // KINVRF_DATA_FROM_EXTERNAL_IMAGE
        int image_number_;  ///< if image, need to know the image number
        string image_data_path_;
        string image_name_prefix_;  ///< get from string.xml
        string image_name_suffix_;  ///< get from string.xml
        string image_type_suffix_;  ///< get from setting.xml and string.xml

        // need an array, dynamitally allocated


        
        Mat data_mat_;  ///< used to store data;       

    };  // class DataRes

}  // namespace kinvrf_ml

#endif  // KINVRF_TRAINING_DATA_H
