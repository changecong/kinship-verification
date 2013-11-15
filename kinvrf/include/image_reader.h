/*
 * Filename:      image_reader.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:02:16 2013
 * Modified at:   Thu Nov 14 15:45:17 2013
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
#include "types.h"

// namespaces
using namespace cv;
using namespace std;

namespace kinvrf_img {

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
    // explicit ImageReader(const ImageReader& other);

    /// \fn
    /// \brief
    explicit ImageReader(const Mat& mat);

    /// \fn
    /// \brief set and get image_path_
    // void image_path(string path);
    // string image_path() const;

    /// \fn
    /// \brief set and get image_mat_
    // void image_mat(Mat image);
    Mat image_mat();

    ///\fn
    ///\brief return a gray scale image;
    Mat image_gray();

    ///\fn
    ///\brief crop the image
    Mat image_crop(size_t x, size_t y, size_t w, size_t h);
    
    /// \fn
    /// \brief
    uchar* image_data();

    /// \fn
    /// \brief set and get image
    // void image_is_read(bool flag);
    bool image_is_read() const;

    /// \fn
    /// \brief get image width
    size_t image_width() const;

    /// \fn
    /// \brief get image height
    size_t image_height() const;

    /// \fn
    /// \brief
    size_t image_size() const;

  private:
    // some helper functions

    /// \fn init()
    /// \brief
    void init();

    /// \fn
    /// \brief
    void init(const Mat& mat, bool flag);

    /// \fn init()
    /// \brief
    void init(const Mat& mat, bool flag, size_t width, size_t height);

    // string image_path_;  ///< the path of image
    Mat image_mat_;  ///< the image that image reader reads in
    bool image_is_read_;  ///< a flag that used to set if the image is read successfully
    size_t image_width_;  ///< image width
    size_t image_height_;  ///< image height
    size_t image_size_;  ///< image width x heidht; 

    const Mat default_mat_;  ///< a default image displaied when image_mat_ is not avialable
};

}  // namespace kinvrf_img

#endif  // KINVRF_IMAGE_READER_H
