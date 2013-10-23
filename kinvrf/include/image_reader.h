/*
 * Filename:      image_reader.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:02:16 2013
 * Modified at:   Wed Oct 23 01:47:58 2013
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

  public:
    /// \fn
    /// \brief
    ImageReader();

    /// \fn
    /// \brief
    explicit ImageReader(string path);
    
    /// \fn
    /// \brief a copy constructor
    explicit ImageReader(const ImageReader &other);

    /// \fn
    /// \brief set and get image_path_
    // void image_path(string path);
    string image_path();

    /// \fn
    /// \brief set and get image
    // void image(Mat image);
    Mat image();

    /// \fn
    /// \brief set and get image
    // void image_is_read(bool flag);
    bool image_is_read();
    

  private:
    /// \fn init()
    /// \brief
    void init();

    string image_path_;  ///< the path of image
    Mat image_;  ///< the image that image reader reads in
    bool image_is_read_;  ///< a flag that used to set if the image is read successfully
};

#endif KINVRF_IMAGE_READER_H
