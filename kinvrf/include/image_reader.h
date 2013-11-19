/*
 * Filename:      image_reader.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Oct 22 23:02:16 2013
 * Modified at:   Sat Nov 16 21:53:01 2013
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

///\namespace kinvrf_img
///\brief Contains functions and classes which are defined for Image module of the project.
namespace kinvrf_img {

    /// \class ImageReader
    /// \brief A Class that encapsulate the image and some pre-processing functions.
    class ImageReader {

      public:

        ///\fn ImageReader(string path)
        ///\param [in] path The path of image.
        ///\brief A constructor.
        explicit ImageReader(string path);
    
        ///\fn ImageReader(const ImageReader& other)
        ///\param [in] other An other ImageReader object.
        ///\brief The copy constructor.
        // explicit ImageReader(const ImageReader& other);

        ///\fn ImageReader(const Mat& mat)
        ///\param [in] mat A mat which contains the image.
        ///\brief A constructor.
        explicit ImageReader(const Mat& mat);

        ///\fn
        ///\brief set and get image_path_
        // void image_path(string path);
        // string image_path() const;

        /// \fn
        /// \brief set and get image_mat_
        // void image_mat(Mat image);

        ///\fn Mat image_mat()
        ///\return A cv::Mat instance.
        ///\brief Return the image.
        Mat image_mat();

        ///\fn Mat image_gray()
        ///\return A cv::Mat instance.
        ///\brief Return the gray scale image;
        Mat image_gray();

        ///\fn Mat image_crop(size_t x, size_t y, size_t w, size_t h)
        ///\param [in] x The x coordinate of left-top.
        ///\param [in] y The y coordinate of right-top.
        ///\param [in] w The width of the crop box.
        ///\param [in] h The height of the crop box.
        ///\brief Crop the image and return as a cv::Mat object.
        Mat image_crop(size_t x, size_t y, size_t w, size_t h);
    
        ///\fn uchar* image_data()
        ///\return A uchar pointer. 
        ///\brief Return the data part of the image only, abort the header part.
        uchar* image_data();

        ///\fn
        ///\brief set and get image
        // void image_is_read(bool flag);
    
        ///\fn bool image_is_read() const
        ///\return A boolean value.
        ///\brief Return a true when the image is read in successfully.
        bool image_is_read() const;

        ///\fn size_t image_width() const
        ///\return An unsigned integar.
        ///\brief Return the width of the image.
        size_t image_width() const;

        ///\fn size_t image_height() const
        ///\return An unsigned integar.
        ///\brief Return the height of the image.
        size_t image_height() const;

        ///\fn size_t image_size() const
        ///\return An unsigned integar.
        ///\brief Return the total number of pixels of the image, which equals to width x height.
        size_t image_size() const;

      private:

        ///\fn ImageReader()
        ///\brief Default constructor that declared as private.
        ImageReader();

        ///\fn void init()
        ///\brief Initialize by default values.
        void init();

        ///\fn void init(const Mat& mat, bool flag)
        ///\param [in] mat  A cv::Mat object which contains image data.
        ///\param [in[ flag A boolean value to show if the image is read successfully.
        ///\brief Initialization which is called when construct with an cv::Mat object.
        void init(const Mat& mat, bool flag);

        ///\fn void init(const Mat& mat, bool flag, size_t width, size_t height)
        ///\param [in] mat    A cv::Mat object which contains image data.
        ///\param [in] flag   A boolean value to show if the image is read successfully.
        ///\param [in] width  The image width.
        ///\param [in] height The image height.
        ///\brief Initialization which is called when construct with an other ImageReader object.
        void init(const Mat& mat, bool flag, size_t width, size_t height);

        // string image_path_;  ///< the path of image.
        Mat image_mat_;  ///< The image that image reader reads in.
        bool image_is_read_;  ///< A flag that used to set if the image is read successfully.
        size_t image_width_;  ///< The image width.
        size_t image_height_;  ///< The image height.
        size_t image_size_;  ///< Image width x heidht. 

        const Mat default_mat_;  ///< a default image when image_mat_ is not avialable.
    
    };  // class ImageReader

}  // namespace kinvrf_img

#endif  // KINVRF_IMAGE_READER_H
