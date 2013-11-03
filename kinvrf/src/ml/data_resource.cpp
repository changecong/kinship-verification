/*
 * Filename:      data_resource.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 13:27:28 2013
 * Modified at:   Sun Nov  3 01:20:53 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/training_data.h"
#include "include/util_get_resource.h"
#include "include/string_convert.h"  // number_to_string

using namespace kinvrf_res;
using namespace kinvrf_cvt;
using namespace std;

namespace kinvrf_ml { 

    // default constructor
    DataRes::DataRes() : 
        data_res_(KINVRF_DATA_FROM_INtERNAL_SETTING),
        image_number_(0),
        image_data_path_(""),
        image_name_prefix_(""),
        image_name_suffix_(""),
        image_type_suffix_("") {

    }

    // other constructor
    DataRes::DataRes(DATARES data_res) :
        data_res_(data_res) :
        image_number_(0),
        image_data_path_(""),
        image_name_prefix_(""),
        image_name_suffix_(""),
        image_type_suffix_("") {

    }

    // distructor
    DataRes::~DataRes(){}

    //
    void DataRes::image_data_path(const string& s) {
        image_data_path_ = s;
    }

    // private

    DATARES DataRes::get_data_method() {
        
        XMLRes* xml_resource = get_resource()->get_xml();

        // get corresponding setting "DataRescource"
        pair<string, string> type_value_pair = xml_resource->get_setting(
            KINVRF_XML_RESOURCE_SETTING_DATARESOURCE);

        if(){
            int method_setting = string_to_int(type_value_pair.second);
            // cast to DATARES
            return (DATARES) method_setting;
        } else {

            // cast to DATARES
            return KINVRF_DATA_FROM_KINSHIP_V2_IMAG;
        }
    }

    void DataRes::image_number() {

        XMLRes* xml_resource = get_resource()->get_xml();

        // get conrresponding setting "ImageDataNumbmer"
        pair<string, string> type_value_pair = xml_resource->get_setting(
            KINVRF_XML_RESOURCE_SETTING_IMAGEDATANUMBER);

        // if it is a number
        if(KINVRF_XML_RESOURCE_TYPE_NUMBER == type_value_pair.first) {
             
            int number_setting = string_to_int(type_value_pair.second); 
            image_number_ = number_setting;       
              
        } else {
            image_number_ = 0;
        }


    }

    // 
    void DataRes::get_date(DATARES data_res) {
        
        switch(data_res) {
        case KINVRF_DATA_FROM_KINSHIP_V2_IMAGE :
            // preparation
            string image_name = "";
            
            // 1. ge image number
            this->image_number();
            // 2. get images one by one
            for (int image_iter = 0; image_iter < image_number_; image_iter++) {
                // 3 assemble image name 
                // 3.1 get path prefix and suffix
                // this->image_data_path();
                this->image_name_prefix();
                this->image_name_suffix();
                this->image_type_suffix();
                // 3.2 add together
                image_name = image_data_path_ + image_name_prefix_
                    + string_to_number(image_iter)
                    + image_name_suffix_ + image_type_suffix_;

                // 4. get Image reader
            }
            break;
            

        }
    }

    void DataRes::image_data_path(){}
    void DataRes::image_name_prefix(){}
    void DataRes::image_name_suffix(){}
    void DataRes::image_type_suffix(){}

}  // namespace kinvrf_ml
