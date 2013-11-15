/*
 * Filename:      ml_data.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 13:27:28 2013
 * Modified at:   Thu Nov 14 23:07:51 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/util_get_resource.h"
#include "include/ml_data.h"  // class DataRes
                              // dynamic_array
#include "include/ml_test_data.h"  // class TestData
#include "include/ml_train_data.h"  // class TrainData

#include "include/string_convert.h"  // number_to_string
#include "include/types.h"  // Setting_t
#include "include/image_reader.h"  // class ImageReader

#include "include/gabor_filter.h"  // class GaborFilter

#include <cstring>

using namespace kinvrf_res;
using namespace kinvrf_scvt;
using namespace kinvrf_img;
using namespace kinvrf_fltr;
using namespace std;

namespace kinvrf_ml { 

    ////////////////////
    // Data
    ////////////////////
   

    ///////////////////
    // TestData
    // TestData is a class that used to contain test data
    ///////////////////
    //
    TestData::TestData(){}

    //
    TestData::TestData(const string& path_one,
                       const string& path_two) :
        Data(),
        image_one_(path_one),
        image_two_(path_two) {

        init();
    }

    //
    Mat TestData::test_data_one() {
        return test_data_one_;
    }

    //
    Mat TestData::test_data_two() {
        return test_data_two_;
    }

    //
    void TestData::init() {
        get_data();
    }

    //
    void TestData::get_data() {
        if(image_one_.empty() || image_two_.empty()) {
            // TODO
        }

        // get two images
        ImageReader* image_reader_one = new ImageReader(image_one_);
        ImageReader* image_reader_two = new ImageReader(image_two_);

        // do some math
        if((image_reader_one->image_width() != image_reader_two->image_width()) ||
           (image_reader_one->image_height() != image_reader_two->image_height())) {
            // TODO            
        }

        // diff of two mat
        Mat diff_one_two = image_reader_one->image_mat() - image_reader_two->image_mat();
        Mat diff_two_one = image_reader_two->image_mat() - image_reader_one->image_mat();

        // gray
        cvtColor(diff_one_two, diff_one_two, CV_BGR2GRAY);
        cvtColor(diff_two_one, diff_two_one, CV_BGR2GRAY);

        // equalize histogram
        equalizeHist(diff_one_two, diff_one_two); 
        equalizeHist(diff_two_one, diff_two_one); 
        

        // TODO
        // do some process
        //

        test_data_one_ = diff_one_two.reshape(0, 1);
        test_data_two_ = diff_two_one.reshape(0, 1);
    }

    ////////////////////
    // TrainData
    ////////////////////
    TrainData::TrainData() {
        init();
    }

    //
    Mat TrainData::train_data_pos() {
        return train_data_pos_;
    }

    Mat TrainData::train_data_neg() {
        return train_data_neg_;
    }

    //
    void TrainData::init() {
        // get strings
        paths_ = get_paths_from_setting();

        // get data
        get_data();
    }

    //
    void TrainData::get_data() {

        if(paths_.empty()) {
            // TODO warning
        }

        if(paths_.size() > 2) {
            // TODO warning
        }
        
        // get each set of data from differen path
        // usually the data should be 1 or 2 sets
        switch(paths_.size()) {
        
        case 1: {
            string path = paths_[0];
            // get data from data resource
            DataRes* data_resource = new DataRes(path);
            train_data_pos_ = data_resource->data_mat();
            
            break;
        }
        case 2: {
            vector<DataRes*> raw_data;
            for(vector<string>::const_iterator path = paths_.begin();
                path != paths_.end(); path++) {

                string temp = *path;

                // get data from data resource
                DataRes* data_resource = new DataRes(temp);
                raw_data.push_back(data_resource);
            }
            
            Mat data_one_pos = raw_data[0]->data_mat();
            Mat data_two = raw_data[1]->data_mat();
            // generate positive data
            // child - young parent
            train_data_pos_ = data_one_pos - data_two;

            // generate negative data
            // shif the data
            Mat data_one_neg = raw_data[0]->shift_data(1, KINVRF_BY_ROW);
            train_data_neg_ = data_one_neg - data_two;
            
            break;
        }

        default:
            // TODO WARNING
            break;
        }        
    }

    vector<string> TrainData::get_paths_from_setting() {

        vector<string> path;
        string path_setting;

        XMLRes* xml_resource = get_resource()->get_xml();

        // get setting ImageDataPath
        Setting_t setting = xml_resource->get_setting(
            KINVRF_XML_RESOURCE_SETTING_TRAININGDATARESOURCEPATH);
        
        if(KINVRF_XML_RESOURCE_TYPE_STRING == setting.first) {
            
            path_setting = setting.second;
            
            // process the path string
            path = string_split(path_setting, ";");
        } 

        return path;
    
    }
    
    ///////////////////
    // DataRes
    // DataRes is a class that used to get training data.
    //////////////////

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

    //
    void DataRes::gen_eigen_vectors() {
        if(data_eigen_vectors_.empty()) {
            // TODO
        }
        
        // get the file name from settings
        string filename = string_setting(
            KINVRF_XML_RESOURCE_SETTING_MATFILESTORAGENAME);
        
        string matname = string_setting(
            KINVRF_XML_RESOURCE_SETTING_MATNAME);
        
        // write into a xml file
        save_mat(data_eigen_vectors_, filename, matname);
        
    }

    // 
    void DataRes::gen_feature_data() {
        
        if(data_mat_.empty()) {
            // TODO
        }
        
        // get the file name from settings
        string filename = string_setting(
            KINVRF_XML_RESOURCE_SETTING_MATFILESTORAGENAME);
        
        string matname = string_setting(
            KINVRF_XML_RESOURCE_SETTING_MATNAME);
        
        // write into a xml file
        save_mat(data_mat_, filename, matname);        
    }



    // private

    // 
    void DataRes::get_data(DATARES data_res) {
        
        switch(data_res) {
        case KINVRF_DATA_FROM_KINSHIP_V2_IMAGE :

            get_data_from_image();
            
            break;

        case KINVRF_DATA_FROM_KINSHIP_V2_TEXT :

            // get_data_from_text();
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
            DATARES res = get_data_method();
            get_data(res);
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
                cerr << "ERROR: " << image_name << ": no such a directory or file." << endl;    
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
                
            uchar* row_data = NULL;

            ///////////// Gabor Filter ///////////////
            // scale : 0, 1, 2
            // orientation : 0, 1, 2, 3, 4, 5, 6, 7
            //////////////////////////////////////////
            
            row_data = image_pre_process(8, 3, image_reader, row_length); 

            if(0 == image_iter) {

                // initial a dynamic array
                all_data = (uchar**)dynamic_array(image_number_, 
                                                  row_length, 
                                                  sizeof(uchar));
            }            

            // only for test
            if (row_data == NULL) {
                cout << "row_data is NULL" << endl;
            }
                
            memcpy(all_data[image_iter], row_data, sizeof(char) * row_length);
            
        }
        // now we hava all data, put it into a temporary mat
        uchar* all_data_1d = reshape_dynamic_array(image_number_,
                                                   row_length,
                                                   all_data);

        Mat gabor_feature;
        gabor_feature = Mat(image_number_, 
                        row_length,
                        CV_8UC1,  // 8-bit single channel
                        all_data_1d);  //

        free_dynamic_array(all_data);

        //////////////////////// PCA /////////////////////////
        //
        //////////////////////////////////////////////////////

        Pca_t subspace_feature = pca_subspace_feature(gabor_feature);
        
        data_eigen_values_ = subspace_feature[1];
        data_eigen_vectors_ = subspace_feature[2];
        
        data_mat_ = subspace_feature[0];
    }

    void DataRes::get_data_from_xml() {

        // data_mat_ = read_mat(filename, matname);
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

    Mat DataRes::shift_data(size_t k, SHIFTBY by) {

        Mat data_mat = data_mat_;
        
        switch((int)by) {

        case KINVRF_BY_ROW: {
            
            size_t data_width = data_mat.cols;
            size_t data_height = data_mat.rows;

            k = k%data_height;
            if(0 == k) {
                break;
            }

            // Mat temp(k, row_length, U8C1);
            
            // back up
            Rect shift(0, data_height - k, data_width, k);

            Mat temp = data_mat(shift);

            // shift
            int i = data_height - k - 1;
            while(i >= 0) {
                data_mat.row(i).copyTo(data_mat.row(i+k));
                i--;
            }

            // make up
            i = 0;
            while(i < k) {
                temp.row(i).copyTo(data_mat.row(i));
                
                i++;
            }
            
            break;
        }
        case KINVRF_BY_COL:
            
            break;
        default:
            break;

            return data_mat;
        }

    }

    /////////////////////////////////////////////
    /// utility functions
    /////////////////////////////////////////////

    uchar* image_pre_process(int orientation, int scale, 
                             ImageReader* ir, size_t &length) {
        
        Mat src = ir->image_gray();
        int down_sample = 6;
        int small_width = cvRound(src.cols/down_sample);
        int small_height = cvRound(src.rows/down_sample);
        // resize the image into 1/6
        Mat small(small_width, small_height, CV_8UC1);
        length = orientation * scale * small_width * small_height;

        uchar* gabor_feature = (uchar*)malloc(sizeof(uchar)*length);
        memset(gabor_feature, 0, sizeof(uchar)*length);

        for (int i = 0; i < scale; i++) {
            
            for (int j = 0; j < orientation; j++) {
                    
                // Gabor Filter
                
                Mat dst(src.size(), CV_8UC1);

                GaborFilter gabor_filter = GaborFilter(j, i);
                
                gabor_filter.convert_image(src, dst);
                
                // down sample
                resize(dst,  // src image 
                       small,  // dis image
                       small.size(),  // size
                       0,  // scale of x 
                       0,  // scale of y
                       // INTER_NEAREST
                       INTER_LINEAR
                       // INTER_CUBIC
                       // INTER_AREA
                       // INTER_LANCZOS4
                    );
                
                equalizeHist(small, small); 
                
                // get data
                uchar* data = small.data;
                // set data into gabor_feature;
                memcpy(gabor_feature + (i*orientation + j)* small_width * small_height,
                       data, sizeof(uchar) * small_width * small_height);
                // // free(data);
            }
        }

        return gabor_feature;
    }

}  // namespace kinvrf_ml
