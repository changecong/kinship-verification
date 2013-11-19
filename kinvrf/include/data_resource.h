/*
 * Filename:      data_resource.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 29 21:20:56 2013
 * Modified at:   Sun Nov 17 10:03:40 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   This file declares the class DATARES which is used to read data 
 *                from disk and generate a set of data that can be used for the project.
 *
 */

#ifndef KINVRF_TRAINING_DATA_H
#define KINVRF_TRAINING_DATA_H

#include "image_reader.h"  // class ImageReader
#include <opencv2/opencv.hpp>

using namespace cv;

///\namespace kinvrf_ml
///\brief Contains functions and classes which are defined for Machine Learning module of the project.  
namespace kinvrf_ml {

    ///\enum DATARES
    ///\brief Declares the type of data resources.
    enum DATARES {
        KINVRF_DATA_FROM_KINFACE_V2_IMAGE = 0,  ///< Raw images that from KinFace_V2 database
        KINVRF_DATA_FROM_KINFACE_V2_XML   = 1,  ///< xml files that generate from KinFace_V2 database 
        KINVRF_DATA_FROM_EXTERNAL_IMAGE   = 2,  ///< Images that from other resources
        KINVRF_DATA_FROM_EXTERNAL_XML     = 3,  ///< xml files that from other resources
        KINVRF_DATA_FROM_INTERNAL_SETTING = 4   ///< Resource is defined in the settings.xml
    };

    ///\enum SHIFTBY
    ///\brief Declares for the utility function Mat shift_data(size_t k, SHIFTBY by).
    ///\see Mat shift_data(size_t k, SHIFTBY by)
    enum SHIFTBY {
        KINVRF_BY_ROW = 0,  ///< shift by row
        KINVRF_BY_COL = 1   ///< shift by column
    };

    ///\class DataRes
    ///\brief Basicall, we may have multiple set of data that need to be used.\n
    ///\detail For each set of data, we put them into a different folder. Thus,
    ///        each folder will conrrespoding to a DataRes object.\n
    ///        For example:\n
    ///        res/img/child/       => DataRes child = DataRes(data_res, "res/img/child/");\n
    ///        res/img/youngparent/ => DataRes yparent = DataRes(data_res, "res/img/youngparent/");\n
    ///        res/img/oldparent/   => DataRes oldparent = DataRes(data_res, "res/img/oldparent/");\n
    class DataRes {

      public:
        ///\fn DataRes()
        ///\brief Default constructor, data resource is set in settings.xml. 
        ///       used when we only need one set of data.
        DataRes();

        ///\fn Data(const string& s)
        ///\param [in] s path of the directory of images or xml file.
        ///\brief Constructor that data resource with a spicific path name, 
        ///       useful when we need to get multiple sets of data.
        explicit DataRes(const string& s);

        ///\fn DataRes(DATARES data_res, const string& s)
        ///\param [in] data_res enum DATARES that declare the type of data resource.
        ///\param [in] s        data resource path.
        ///\brief Constructor that spicifies both data resource type and directory path. 
        ///       used when we have multiple sets of data with different type. like both image 
        ///       and xml file.
        DataRes(DATARES data_res, const string& s);

        ///\fn Data(const string& name)
        ///\param [in] filname The full path of the xml file.
        ///\param [in] matname The name of mat which store in the xml file.
        ///\param [in] nume DATARES which must be xml type.
        ///\brief Constructor that data resource from xml file with a spicific file name, 
        ///       useful when we need to get multiple sets of data.
       DataRes(const string& filename,
               const string& matname,
               DATARES data_res);

        ///\fn ~DataRes()
        ///\brief The distructor.
        ~DataRes();      

        ///\fn void image_data_path(const string &s);
        ///\param [in] s data resource path
        ///\brief Set the data resource path when data resource type is image.
        void data_path(const string &s);

        ///\fn Mat data_mat()
        ///\return a cv::Mat instance.
        ///\brief Get a the data comes from data resource after preprocess.
        Mat data_mat();

        ///\fn void renew()
        ///\brief Re-generate the matrix after changing the path or other options.
        void renew();

        ///\fn Mat shift_data(size_t k, SHIFTBY by)
        ///\param [in] k  k rows(or columns) that need to be shifted. k must be >= 0
        ///\param [in] by enume SHIFTBY that spicific shift by row or column
        ///\return a cv::Mat instance.
        ///\brief shift data by row or col.
        ///\see SHIFTBY
        Mat shift_data(size_t k, SHIFTBY by);

        ///\fn void gen_eigen_vectors()
        ///\brief Store eigen vectors of the data, which comes from data resource, into a xml file. 
        ///       The xml file name and directory are defined in settings.xml
        void gen_eigen_vectors();

        ///\fn void gen_feature_data()
        ///\brief Store the matrix of features of the data, which comes from data resource, into a xml file. 
        ///       The xml file name and directory are defined in settings.xml 
        void gen_feature_data();

        
      private:

        ///\fn DATARES get_data_method()
        ///\return enum DATARES
        ///\brief Get data resource type from settings.xml
        ///\see DATARES
        DATARES get_data_method();

        ///\fn void get_data(DATARES data_res)
        ///\param [in] data_res enum DATARES that spicifies the data resource type.
        ///\brief Get data from data resource.
        void get_data(DATARES data_res);

        ///\fn void get_data_from_image()
        ///\brief Called when data comes from image, includes KinFace_V2 database image and other external image. 
        void get_data_from_image();

        ///\fn void get_data_from_xml()
        ///\brief Read data in from xml files.
        void get_data_from_xml();

        ///\fn void image_number()
        ///\brief Get the number of images that need to be read from settings.xml.
        void image_number();

        ///\fn data_path()
        ///\brief Get the path of data directory from settings.xml. Used for both image data and xml files.
        void data_path();

        ///\fn void image_name_prefix()
        ///\brief Get image name prefix from settings.\n 
        ///       Image nane consists of four distinct parts.\n
        ///       image_name = <b>image_name_prefix</b> + image_index + image_name_suffix + image_type_suffix.\n
        ///       <b>child</b>-10-face.bmp
        void image_name_prefix();

        ///\fn void image_name_suffix()
        ///\brief Get image name suffix from settings.\n 
        ///       Image nane consists of four distinct parts.\n
        ///       image_name = image_name_prefix + image_index + <b>image_name_suffix</b> + image_type_suffix.\n
        ///       child-10-<b>face</b>.bmp
        void image_name_suffix();

        ///\fn void image_type_suffix()
        ///\brief Get image type suffix from settings.\n 
        ///       Image nane consists of four distinct parts.\n
        ///       image_name = image_name_prefix + image_index + image_name_suffix + <b>image_type_suffix</b>.\n
        ///       child-10-face.<b>bmp</b>
        void image_type_suffix();


        // member variables
        DATARES data_res_;  ///< Data resource type.

        string data_path_;  ///< the path of data (images and xml files).

        // used when Data resource type is set to 
        // KINVRF_DATA_FROM_KINFACE_V2_IMAGE or KINVRF_DATA_FROM_EXTERNAL_IMAGE
        int image_number_;  ///< The number of images that need to be read in.        
        string image_name_prefix_;  ///< get from string.xml
        string image_name_suffix_;  ///< get from string.xml
        string image_type_suffix_;  ///< get from setting.xml and string.xml

        // used when Data resource type is set to 
        // KINVRF_DATA_FROM_KINFACE_V2_XML or KINVRF_DATA_FROM_EXTERNAL_XML
        string filename_;  ///< the full path of xml file.
        string matname_;   ///< the mat name in xml file.

        Mat data_eigen_values_;  ///< eigen values
        Mat data_eigen_vectors_;  ///< eigen vectors
        Mat data_mat_;  ///< used to store feature data;       

    };  // class DataRes

}  // namespace kinvrf_ml

#endif  // KINVRF_TRAINING_DATA_H
