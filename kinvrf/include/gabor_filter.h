/*
 * Filename:      gabor_filter.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov 13 19:11:45 2013
 * Modified at:   Thu Nov 14 14:28:43 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_GABOR_FILTER_H 
#define KINVRF_GABOR_FILTER_H
#include <opencv2/opencv.hpp>

using namespace cv;

namespace kinvrf_fltr {

    class GaborFilter {

      public:

        ///\fn
        ///\brief disstructor
        ~GaborFilter();

        ///\fn
        ///\param
        ///       orientation : orientation * PI / 8
        ///       scale       : the scale
        ///       sigma       : the sigma, default is 2*pi
        ///       f           : frequence, default is sqrt(2)
        ///       kmax        : the kmax, default is pi/2
        ///       half        : width of window, 0 means does set manually
        ///       type        : type of image, default is 32bit 1 channel
        ///\brief constructor
        GaborFilter(int orientation, 
                    int scale, 
                    double sigma = 2*CV_PI, 
                    double f = sqrt(2),
                    double kmax = 0.5*CV_PI,
                    size_t half = 0,
                    int type = CV_32FC1);

        ///\fn
        ///\brief 
        void convert_image(Mat& src, Mat& dst);

        ///\fn
        ///\brief
        Mat kernel_real();
        
        ///\fn
        ///\brief
        Mat kernel_imag();

      private:

        ///\fn
        ///\brief constructor
        GaborFilter();

        ///\fn
        ///\brief
        void init();

        ///\fn
        ///\brief
        void gabor_kernel();


        double orientation_;
        int scale_;
        double sigma_;
        double f_;
        double kmax_;
        size_t half_;
        int type_;

        double phi_;
        size_t width_;
        double k_;

        Mat kernel_real_;
        Mat kernel_imag_;

    };  // class GaborFilter

}  // namespace kinvrf_fltr

#endif  // KINVRF_GABOR_FILTER_H
