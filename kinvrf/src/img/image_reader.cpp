/*
 * Filename:      image_reader.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:31:28 2013
 * Modified at:   Wed Nov  6 22:26:17 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

// corresponding header
#include "include/image_reader.h"

namespace kinvrf_img {
// constructors
    ImageReader::ImageReader() :
        default_mat_(32, 32, CV_8UC1) {
        // call the init()
        init();
    }

    ImageReader::ImageReader(string path) :
        default_mat_(32, 32, CV_8UC1) {
        // image_path_ = path;
    
        // get the image by opencv api
        image_mat_ = imread(path);

        // check if the image is read successfully
        if (image_mat_.empty()) {
            image_is_read_ = false;
        } else {
            image_is_read_ = true;
            // get image size
            image_width_ = image_mat_.cols;
            image_height_ = image_mat_.rows;
        }
    }

// explicit ImageReader::ImageReader(const ImageReader& other) : 
// default_mat_(32, 32, CV_8UC1) {
    
//     // if(other == NULL) {
//     if(false)
//         // if other is null, call init() instead
//         init();        
//     } else {
//         const Mat& mat = other.image_mat();
//         init(mat, other.image_is_read(), 
//              other.image_width(), other.image_height());
//     }

// }

    ImageReader::ImageReader(const Mat& mat) : 
        default_mat_(32, 32, CV_8UC1) {
        if (mat.empty()) {
            init();
        } else {
            // call init()
            init(mat, true);
        }
    }

// string ImageReader::image_path() {
//     return image_is_read_ ? image_path : "";
// }

    Mat ImageReader::image_mat() {
        return image_is_read_ ? image_mat_ : default_mat_; 
    }

    uchar* ImageReader::image_data() {
        uchar* image_data = NULL;
        if (image_is_read_) {
            image_data = image_mat_.data;
        }

        return image_data;
    }

    bool ImageReader::image_is_read() const{
        return image_is_read_;
    }

    size_t ImageReader::image_width() const {
        return image_width_;
    }

    size_t ImageReader::image_height() const {
        return image_height_;
    }

    size_t ImageReader::image_size() const {
        return image_height_ * image_width_;
    }

    void ImageReader::init() {
        image_is_read_ = false;
        image_width_ = 0;
        image_height_ = 0;
    }

    void ImageReader::init(const Mat& mat, bool flag) {
        // get the matrix
        image_mat_ = mat;
        // get the boolean flag
        image_is_read_ = flag;
        // get the width
        image_width_ = mat.cols;
        // get the height
        image_height_ = mat.rows;
    }

    void ImageReader::init(const Mat& mat, bool flag, size_t width, size_t height) {
        // get the mat
        image_mat_ = mat;
        // get the flag
        image_is_read_ = flag;
        // get the width
        image_width_ = width;
        // get the height
        image_height_ = height;
    }

// create a 32x32 8-bit single channel image as default
// const Mat ImageReader::defaul_mat_ = new Mat(32, 32, CV_8UC1);
}  // namespace kinvrf_img
