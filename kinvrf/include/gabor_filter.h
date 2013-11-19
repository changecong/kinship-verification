/*
 * Filename:      gabor_filter.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov 13 19:11:45 2013
 * Modified at:   Sat Nov 16 21:28:34 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_GABOR_FILTER_H 
#define KINVRF_GABOR_FILTER_H

#include <opencv2/opencv.hpp>

using namespace cv;

///\namespace kinvrf_fltr
///\brief Contains functions and classes which are defined for Filter module of the project.
namespace kinvrf_fltr {

    ///\class GaborFilter
    ///\brief A class that define a Gabor Filter used to obtain image feature. 
    class GaborFilter {

      public:

        ///\fn ~GaborFilter()
        ///\brief Distructor
        ~GaborFilter();

        ///\fn GaborFilter(int orientation, int scale, double sigma = 2*CV_PI, 
        ///                double f = sqrt(2), double kmax = 0.5*CV_PI,
        ///                size_t half = 0, int type = CV_32FC1)
        ///\param [in] orientation The orientation of the kernel, phi = orientation * PI / 8.
        ///\param [in] scale       The scale.
        ///\param [in] sigma       The sigma, default is 2*pi.
        ///\param [in] f           The Frequence, default is sqrt(2).
        ///\param [in] kmax        The kmax, default is pi/2.
        ///\param [in] half        Half of the width of window, 0 means being set manually.
        ///\param [in] type        Type of image, default is 32-bit 1 channel, CV_32FC1.
        ///\brief The constructor used to initialize the parameters of Gabor kernel.
        GaborFilter(int orientation, 
                    int scale, 
                    double sigma = 2*CV_PI, 
                    double f = sqrt(2),
                    double kmax = 0.5*CV_PI,
                    size_t half = 0,
                    int type = CV_32FC1);

        ///\fn void convert_image(Mat& src, Mat& dst)
        ///\param [in] src The source image that will be converted.
        ///\param [out] dst The destination image which is the convertion result.
        ///\brief 
        void convert_image(Mat& src, Mat& dst);

        ///\fn Mat kernel_real()
        ///\return A cv::Mat instance.
        ///\brief Return the real part of the gabor kernel.
        Mat kernel_real();
        
        ///\fn Mat kernel_imag()
        ///\return A cv::Mat instance.
        ///\brief Raturn the imaginary part of the gabor kernel.
        Mat kernel_imag();

      private:

        ///\fn GaborFilter()
        ///\brief Default constructor which is declared as private.
        GaborFilter();

        ///\fn void init()
        ///\brief Initialize parameter for kernel calculation.
        void init();

        ///\fn void gabor_kernel()
        ///\brief Implement the Gabor function of Gabor kernel
        void gabor_kernel();


        double orientation_;  ///< The orientation.
        int scale_;           ///< The scale
        double sigma_;        ///< The sigma
        double f_;            ///< the frequence.
        double kmax_;         ///< The Kmax.
        size_t half_;         ///< Half of the window width.
        int type_;            ///< The type of source image.

        double phi_;          ///< The Phi.
        size_t width_;        ///< The window width.
        double k_;            ///< The Kv.

        Mat kernel_real_;     ///< The real part of gabor kernel.
        Mat kernel_imag_;     ///< The imaginary part of gabor kernel.

    };  // class GaborFilter

}  // namespace kinvrf_fltr

#endif  // KINVRF_GABOR_FILTER_H
