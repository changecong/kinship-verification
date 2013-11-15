/*
 * Filename:      gabor.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov 13 19:10:53 2013
 * Modified at:   Thu Nov 14 15:33:24 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/gabor_filter.h"

namespace kinvrf_fltr{

    GaborFilter::GaborFilter(){}

    GaborFilter::~GaborFilter() {
        kernel_real_.release();
        kernel_imag_.release();
    }

    GaborFilter::GaborFilter(int orientation,
                             int scale,
                             double sigma,
                             double f,
                             double kmax,
                             size_t half,
                             int type) : 
        orientation_(orientation),
        scale_(scale),
        sigma_(sigma),
        f_(f),
        kmax_(kmax),
        half_(half),
        type_(type) {

        init();
    }

    Mat GaborFilter::kernel_real() {
        Mat ret_kernel_real;
        normalize(kernel_real_, ret_kernel_real, 0, 255, CV_MINMAX, CV_8U);
        return ret_kernel_real;
        // return kernel_real_;
    }

    Mat GaborFilter::kernel_imag() {
        Mat ret_kernel_imag;
        normalize(kernel_imag_, ret_kernel_imag, 0, 255, CV_MINMAX, CV_8U);

        return ret_kernel_imag;
        // return kernel_imag_;
    }

    void GaborFilter::init() {
        
        phi_ = orientation_ * CV_PI/8;

        k_ = kmax_/pow(f_, scale_);

        if(0 == half_) {
            double sigma = sigma_/k_;
            width_ = cvRound(sigma * 6 ) + 1;  // width need to be odd
        } else {
            width_ = 2 * half_ + 1;  // width need to be odd
        }

        // create the kernel
        kernel_real_.create(width_, width_, type_);
        kernel_imag_.create(width_, width_, type_);

        // get the kernal
        gabor_kernel(); 
    }
        

    void GaborFilter::gabor_kernel() {
        // example:
        // -2 -1 0 1 2

        double real;
        double imag;
        double preconstant = pow(k_, 2)/sigma_;
        double midconstant = preconstant/(-2 * sigma_);
        double postconstant = exp(pow(sigma_, 2)/(-2));
        int x, y;
        // it s complex
        for (int i = 0; i < width_; i++) {
            
            y = i - (width_ -1)/2;
            float* real_single_row = kernel_real_.ptr<float>(i);
            float* imag_single_row = kernel_imag_.ptr<float>(i);

            for (int j = 0; j < width_; j++) {
                
                x = j - (width_ - 1)/2;
               
                double first_part =preconstant * exp( ( pow(x, 2) + pow(y, 2) ) * midconstant );
                double second_part_real = cos(k_ * (cos(phi_)*x + sin(phi_)*y)) - postconstant;
                double second_part_imag = sin(k_ * (cos(phi_)*x + sin(phi_)*y));

                real = first_part * second_part_real;
                imag = first_part * second_part_imag;

                // // put into mat
                real_single_row[j] = (float)real;
                imag_single_row[j] = (float)imag;
            }
        }

        // now we have two kernels
        
    }

    void GaborFilter::convert_image(Mat& src, Mat& dst) {
        if (src.size() != dst.size()) {
            // TODO 
        }

        Mat real(dst.size(), CV_32FC1);
        Mat imag(dst.size(), CV_32FC1);

        filter2D(src, real, CV_32F, kernel_real_, Point((width_-1)/2, (width_-1)/2), 0, BORDER_DEFAULT);
        filter2D(src, imag, CV_32F, kernel_imag_, Point((width_-1)/2, (width_-1)/2), 0, BORDER_DEFAULT);
        cv::pow(real, 2.0, real);
        cv::pow(imag, 2.0, imag);

        Mat temp = real + imag;
        cv::pow(temp, 0.5, temp);

        // convert to 8UC1
        if (CV_8U == dst.depth()) {
            temp.convertTo(dst, CV_8UC1);
        } else {
            temp.assignTo(dst);
        }

    }


}  // namespace kinvrf_fltr
