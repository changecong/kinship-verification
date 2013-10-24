/*
 * Filename:      image_reader.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:02:16 2013
 * Modified at:   Wed Oct 23 22:51:57 2013
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

    /// \fn
    /// \brief set and get image
    // void image_is_read(bool flag);
    bool image_is_read() const;

    /// \fn
    /// \brief get image width
    int image_width() const;

    /// \fn
    /// \brief get image height
    int image_height() const;

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
    void init(const Mat& mat, bool flag, int width, int height);

    // string image_path_;  ///< the path of image
    Mat image_mat_;  ///< the image that image reader reads in
    bool image_is_read_;  ///< a flag that used to set if the image is read successfully
    int image_width_;  ///< image width
    int image_height_;  ///< image height

    const Mat default_mat_;  ///< a default image displaied when image_mat_ is not avialable
};

#endif  // KINVRF_IMAGE_READER_H
