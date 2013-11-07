/*
 * Filename:      ml_data.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 13:27:28 2013
 * Modified at:   Wed Nov  6 22:46:28 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/util_get_resource.h"
#include "include/ml_data.h"  // class DataRes
                              // dynamic_array
#include "include/string_convert.h"  // number_to_string
#include "include/types.h"  // Setting_t
#include "include/image_reader.h"  // class ImageReader

#include <cstring>

using namespace kinvrf_res;
using namespace kinvrf_scvt;
using namespace kinvrf_img;
using namespace std;

namespace kinvrf_ml { 

    // default constructor reads data by settings
    DataRes::DataRes() : 
        data_res_(KINVRF_DATA_FROM_INTERNAL_SETTING),
        image_number_(0),
        image_name_prefix_(""),
        image_name_suffix_(""),
        image_type_suffix_("") {
        
        image_data_path();
        if("" != image_data_path_) {

            get_data(get_data_method());
        }
        
    }

    // read data from vilid path s
    DataRes::DataRes(const string& s) : 
        data_res_(KINVRF_DATA_FROM_INTERNAL_SETTING),
        image_number_(0),
        image_data_path_(s),
        image_name_prefix_(""),
        image_name_suffix_(""),
        image_type_suffix_("") {
        
        get_data(data_res_);
    }


    // read data from vilid path s by method data_res
    DataRes::DataRes(DATARES data_res, const string& s) :
        data_res_(data_res),
        image_number_(0),
        image_data_path_(s),
        image_name_prefix_(""),
        image_name_suffix_(""),
        image_type_suffix_("") {
        
        get_data(data_res_);
    }

    // distructor
    DataRes::~DataRes(){}

    // set image_dat_path_
    void DataRes::image_data_path(const string& s) {
        image_data_path_ = s;
    }

    // get data_mat_
    Mat DataRes::data_mat() {
        if (data_mat_.empty()) {

            // TODO: (me) throw exception
        }
        
        return data_mat_;
    }

    // explicitly re-generate the data
    void DataRes::renew() {
        data_mat_.release();

        get_data(data_res_);
    }

    // private

    // 
    void DataRes::get_data(DATARES data_res) {
        
        switch(data_res) {
        case KINVRF_DATA_FROM_KINSHIP_V2_IMAGE :

            get_data_from_image();
            
            break;

        case KINVRF_DATA_FROM_KINSHIP_V2_TEXT :

            get_data_from_text();
            // read from text files
            break;

        case KINVRF_DATA_FROM_EXTERNAL_IMAGE :

            get_data_from_image();
            // read from external images
            break;

        case KINVRF_DATA_FROM_EXTERNAL_TEXT :
            
            // read from external text
            break;

        default :
            
            break;
        }
    }

    DATARES DataRes::get_data_method() {
        
        XMLRes* xml_resource = get_resource()->get_xml();

        // get corresponding setting "DataRescource"
        Setting_t setting = xml_resource->get_setting(
            KINVRF_XML_RESOURCE_SETTING_DATARESOURCE);

        if( KINVRF_XML_RESOURCE_TYPE_NUMBER == setting.first) {
            int method_setting = string_to_int(setting.second);
            // cast to DATARES
            return (DATARES) method_setting;
        } else {

            // cast to DATARES
            return KINVRF_DATA_FROM_KINSHIP_V2_IMAGE;
        }
    }

    void DataRes::get_data_from_image() {
        // preparation
        string image_name = "";
        // |000|[Image_000]
        // |001|[Image_001]
        // ...    ...
        // [200][Image_200]
        uchar** all_data = NULL;  // row = image_number_, col = image.cows * image.cols
        size_t row_length = 0;
        image_name_prefix();
        image_name_suffix();
        image_type_suffix();

        // 1. ge image number
        image_number();
        // 2. get images one by one
        for (int image_iter = 0; image_iter < image_number_; image_iter++) {
            // 3 assemble image name 
            // 3.1 get path prefix and suffix
 
            // 3.2 add together
            // "../../res/img/child/child-0-face.bmp"
            // "../../res/img/child/child-1-face.bmp"
            image_name = image_data_path_ + image_name_prefix_
                + number_to_string(image_iter)
                + image_name_suffix_ + image_type_suffix_;

            // 4. get Image reader
            ImageReader* image_reader = new ImageReader(image_name);

            if (!image_reader->image_is_read()) {
                // TODO: (me) throw an exception
                    
                break;
            }
            // 5. while it is done, reshape the mat
            // if(image_reader->image_is_read()) {
            //     // 5.1 reshap
            //     Mat image_matrix_2d = image_reader->image_mat();
            //     Mat image_matrix_1d = image_matrix_2d.reshape(1);
            // }

            // // 5.2 get the size of new matrix, which is the lenght of each row
            // int row_length = image_matrix_1d.cols;
                
            // // 6. generate a new Array;
            // uchar* row_data = image_matrix_1d.data;
                

            if(0 == image_iter) {

                row_length = image_reader->image_size();
                    
                // initial a dynamic array
                all_data = (uchar**)dynamic_array(image_number_, 
                                                  row_length, 
                                                  sizeof(uchar));
            } else {
                if (image_reader->image_size() != row_length) {
                    // TODO: (me) throw an exception
                    break;
                }
            }

            uchar* row_data = (uchar *)image_reader->image_data();

            // only for test
            if (row_data == NULL) {
                cout << "row_data is NULL" << endl;
            }
                
            memcpy(all_data[image_iter], row_data, sizeof(char) * row_length);
            
        }
        // now we hava all data, put it into data_mat
        uchar* all_data_1d = reshape_dynamic_array(image_number_,
                                                   row_length,
                                                   all_data);
        data_mat_ = Mat(image_number_, 
                        row_length,
                        CV_8UC1,  // 8-bit single channel
                        all_data_1d);  //

        free_dynamic_array(all_data);

    }

    void DataRes::image_number() {

        XMLRes* xml_resource = get_resource()->get_xml();

        // get conrresponding setting "ImageDataNumbmer"
        Setting_t setting = xml_resource->get_setting(
            KINVRF_XML_RESOURCE_SETTING_IMAGEDATANUMBER);

        // if it is a number
        if(KINVRF_XML_RESOURCE_TYPE_NUMBER == setting.first) {
             
            int number_setting = string_to_int(setting.second); 
            image_number_ = number_setting;       
              
        } else {
            image_number_ = 0;
        }
    }

    void DataRes::image_data_path() {
        image_data_path_ = string_setting(KINVRF_XML_RESOURCE_SETTING_IMAGEDATAPATH);
    }

    void DataRes::image_name_prefix(){
        image_name_prefix_ = string_setting(KINVRF_XML_RESOURCE_SETTING_IMAGENAMEPREFIX);
    }
    void DataRes::image_name_suffix(){
        image_name_suffix_ = string_setting(KINVRF_XML_RESOURCE_SETTING_IMAGENAMESUFFIX);
    }
    void DataRes::image_type_suffix(){
        image_type_suffix_ = string_setting(KINVRF_XML_RESOURCE_SETTING_IMAGETYPESUFFIX);
    }

    string DataRes::string_setting(const string name) {

        XMLRes* xml_resource = get_resource()->get_xml();

        // get setting ImageDataPath
        Setting_t setting = xml_resource->get_setting(name);

        if(KINVRF_XML_RESOURCE_TYPE_STRING == setting.first) {
            return setting.second;
        } 
        
        return "";
    }

}  // namespace kinvrf_ml
