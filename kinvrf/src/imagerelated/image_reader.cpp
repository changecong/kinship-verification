/*
 * Filename:      image_reader.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:31:28 2013
 * Modified at:   Wed Oct 23 01:55:44 2013
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
    image_path_ = path;
    
    // get the image by opencv api
    image_ = imread(image_path);

    // check if the image is read successfully
    if (image_.empty()) {
        image_is_read_ = false;
    } else {
        image_is_read_ = true;
    }
}

explicit ImageReader::ImageReader(const ImageReader &other) {
    
    // get other's image path
    image_path_ = other.image_path();
    // get other's image
    image_ = other.image();
    // get other's flag
    image_is_read_ = other.image_is_read();

}

void IamgeReader::init() {
    image_path_ = "";
    image_is_read_ = false;
}

string ImageReader::image_path() {
    return image_is_read_ ? image_path : "";
}

Mat ImageReader::image() {
    return image_is_read_ ? image : image; 
}

bool ImageReader::image_is_read() {
    return image_is_read_;
}
