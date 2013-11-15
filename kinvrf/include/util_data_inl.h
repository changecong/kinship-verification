/*
 * Filename:      util_data_inl.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Nov  5 22:24:51 2013
 * Modified at:   Thu Nov 14 23:23:43 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_UTIL_DATA_INL_H
#define KINVRF_UTIL_DATA_INL_H

#include <stdio.h>
#include <cstdlib>
#include <string.h>

#include "string_convert.h"
#include "include/util_get_resource.h"
#include "types.h"
#include "image_reader.h"

using namespace kinvrf_scvt;
using namespace kinvrf_res;
using namespace kinvrf_img;

namespace kinvrf_ml {

// 2 x 3
//                       *arr \       
// [I, I; E, E, E; E, E, E] = |I|[E, E, E]
//                            |I|[E, E, E]
//                      *head/

    // utility functions that used to get a dynamic 2d array
    
    ///\fn
    ///\brief used to generate a 2d array dynamically
    inline void** dynamic_array(size_t row, size_t col, size_t size) {

        // create a pointer
        void **arr;

        size_t array_size = sizeof(void *) * row + size * row * col;

        // allocate
        arr = (void **) malloc(array_size);

        if (NULL != arr) {
            
            void *head;  // head address of each row from the last
            head = (void *)arr + sizeof(void *) * row;
            
            // initialize to 0
            memset(arr, 0, array_size);

            while (row--) {
                arr[row] = head + size * row * col;
            }
        }

        return arr;
    }

    ///\fn
    ///\brief reduce the dimension of array to 1d
    template<typename T>
        inline T* reshape_dynamic_array(size_t src_row, 
                                       size_t src_col, 
                                       T** src_arr) {
        // gen a 1d array
        T* arr = NULL;
        arr = (T*)malloc(sizeof(T) * src_row * src_col);
        for (size_t i = 0; i < src_row; i++) {
            size_t offset = i * src_col * sizeof(T);
            memcpy(arr + offset, src_arr[i], src_col*sizeof(T));
        }

        return arr;
        
    }


    inline string string_setting(const string name) {

        XMLRes* xml_resource = get_resource()->get_xml();

        // get setting ImageDataPath
        Setting_t setting = xml_resource->get_setting(name);

        if(KINVRF_XML_RESOURCE_TYPE_STRING == setting.first) {
            return setting.second;
        } 
        
        return "";
    }

    inline int int_setting(const string name) {

        XMLRes* xml_resource = get_resource()->get_xml();

        // get setting ImageDataPath
        Setting_t setting = xml_resource->get_setting(name);

        if(KINVRF_XML_RESOURCE_TYPE_NUMBER == setting.first) {
            return string_to_int(setting.second);
        } 
        
        return 0;
    }

    ///\fn
    ///\brief
    template<typename T>
    inline void free_dynamic_array(T **arr) {
        if (NULL != arr) {
            free(arr);
        }
    }

    ///\fn
    ///\brief
    uchar* image_pre_process(int orientation, 
                             int scale, 
                             ImageReader* ir, 
                             size_t& length);


    ///\fn
    ///\brief all mat file are write into a same path with differen name
    inline void save_mat(Mat& mat, const string& filename, const string& matname) {
        
        // check if the name is a vilad xml file name
 
        // get path from setting

        String path = string_setting(KINVRF_XML_RESOURCE_SETTING_MATFILESTORAGEPATH);

        FileStorage fs(path + filename, FileStorage::WRITE);
        
        fs << matname << mat;
        
        fs.release();
    }

    inline Mat read_mat(const string& filename, const string& matname) {

        String path = string_setting(KINVRF_XML_RESOURCE_SETTING_MATFILESTORAGEPATH);

        FileStorage fs( path + filename, FileStorage::READ);  

        Mat mat;  

        fs[matname] >> mat;

        return mat;

    }
    
    inline Pca_t pca_subspace_feature(Mat& gabor_feature) {
        
        Pca_t pca_vector;

        int max_components = int_setting(KINVRF_XML_RESOURCE_SETTING_PCAMAXCOMPONENTS);

        PCA pca(gabor_feature, Mat(), CV_PCA_DATA_AS_ROW, max_components);

        Mat subspace_feature = pca.project(gabor_feature);
        pca_vector.push_back(subspace_feature);

        // write into a xml file

        Mat eigen_values = pca.eigenvalues;
        pca_vector.push_back(eigen_values);
        
        Mat eigen_vectors = pca.eigenvectors;
        pca_vector.push_back(eigen_vectors);
        

        return pca_vector;

    }


}  // namespace kinvrf_ml

#endif  // KINVRF_UTIL_DATA_INL_H
