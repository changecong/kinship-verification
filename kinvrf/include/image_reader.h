/*
 * Filename:      image_reader.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:02:16 2013
 * Modified at:   Tue Oct 22 23:34:48 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   This is a class that read image in before processing. 
 *                Functions of this class will obtain some feature ahead. 
 *
 */

#ifndef KINVRF_IMAGE_READER_H
#define KINVRF_IMAGE_READER_H

// sys
#include <string>
// external includes
#include <opencv2/opencv.hpp>
// internal includes

// namespaces
using namespace cv;
using namespace std;

/// \class ImageReader
/// \brief
class ImageReader {

    /// \fn
    /// \brief
    void ImageReader();

    /// \fn
    /// \brief
    explicit void ImageReader(string path);
    
    /// \fn
    /// \brief
    explicit void ImageReader(ImageReader imageReader);

    /// \fn init()
    /// \brief
    void init();
};

#endif KINVRF_IMAGE_READER_H
