/*
 * Filename:      image_reader.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:31:28 2013
 * Modified at:   Wed Oct 23 14:15:41 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

// corresponding header
#include "../../inlcude/image_reader.h"

// constructors
ImageReader::ImageReader() {
    // call the init()
    init();
}

explicit ImageReader::ImageReader(string path) {
    // image_path_ = path;
    
    // get the image by opencv api
    image_mat_ = imread(image_path);

    // check if the image is read successfully
    if (image_.empty()) {
        image_is_read_ = false;
    } else {
        image_is_read_ = true;
        // get image size
    }
}

explicit ImageReader::ImageReader(const ImageReader& other) {
    
    if(other == NULL) {
        // if other is null, call init() instead
        init();        
    } else {
        // get other's image path
        // image_path_ = other.image_path();
        // get other's image
        image_mat_ = other.image();
        // get other's flag
        image_is_read_ = other.image_is_read();
        // get image width
        image_width_ = other.image_width();
        // get image height
        image_height_ = other.image_height();
    }

}

explicit ImageReader::ImageReader(const Mat& mat) {
    if (mat == NULL) {
        init();
    } else {
        int width =;
        int height = ;
        // call init()
        init(mat, true, width, height);
    }
}

// string ImageReader::image_path() {
//     return image_is_read_ ? image_path : "";
// }

Mat ImageReader::image_mat() {
    return image_is_read_ ? image_mat_ : default_mat_; 
}

bool ImageReader::image_is_read() {
    return image_is_read_;
}

int ImageReader::image_width() {
    return image_width_;
}

int ImageReader::image_height() {
    return image_height_;
}

void IamgeReader::init() {
    // image_path_ = "";
    image_is_read_ = false;
    image_width_ = 0;
    image_height_ = 0;
}

void ImageReader::init(const Mat& mat, bool flag, int width, int height) {
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
const ImageReader::defaul_mat_(32, 32, CV_8UC1);
