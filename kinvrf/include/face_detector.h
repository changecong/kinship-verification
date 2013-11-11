/*
 * Filename:      face_detector.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Sun Nov 10 11:27:32 2013
 * Modified at:   Sun Nov 10 22:19:39 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   This is a face detector class, use opencv APIs
 *                1. detect each face
 *                2. split each face from image
 *                3. make each face look straight forward
 *                4. set each image to 100x127 then save
 *      
 */

#ifndef KINVRF_FACE_DETECTOR_H
#define KINVRF_FACE_DETECTOR_H

// external
#include <opencv2/opencv.hpp>
#include <cstring>
#include <vector>
// internal
#include "image_reader.h"  // class ImageReader

using namespace cv;
using namespace std;

namespace kinvrf_img {

    class FaceDetector {

      public:

        ///\fn
        ///\brief constructor
        explicit FaceDetector(const string& path);

        ///\fn
        ///\brief disctructor
        ~FaceDetector();

        ///\fn
        ///\brief
        Mat image();

        ///\fn
        ///\brief
        void eyes();

      private:

        ///\fn
        ///\brief
        void init(const string& path);

        ///\fn
        ///\brief constructor
        FaceDetector();

        ///\fn
        ///\brief detect face from image
        vector<Rect> face_detect();

        ///\fn
        ///\brief split each detected face into different mats
        vector<Mat> face_split();

        ///\fn
        ///\brief find eyes of each face
        vector<Rect> eyes_detect(Mat* face);

        ///\fn
        ///\brief correct each face
        void face_correct(Mat* face);

        ///\fn
        ///\brief get scale from settings
        double scale_from_setting();

        ///\fn
        ///\brief
        string face_cascade_classifier_from_setting();

        ///\fn
        ///\brief
        string eyes_cascade_classifier_from_setting();
        
        ///\fn
        ///\brief
        string eyes_cascade_classifier_back_up_from_setting();

        ///\fn
        ///\brief only used for manually test
        void show_faces();

        ///\fn
        ///\brief map faces_ to raw_faces_
        void raw_faces();

        ///\fn
        ///\brief map raw_faces_ to eye_faces_
        void eye_faces();

        ///\fn
        ///\brief
        string string_setting(const string name);

        ///\fn
        ///\brief
        double number_setting(const string name); 

        ImageReader* image_reader_;  ///< image reader object
        Mat image_;  ///< image
        vector<Rect> faces_;  ///< vector that used to store faces corresponding to the small image
        vector<Rect> raw_faces_;
        vector<Rect> eye_faces_;

        vector<Mat> faces_mat_;

        double scale_;  // the scale used to resize the image, default is 1.3

        size_t image_width_;
        size_t image_height_;

        string face_cascade_classifier_path_;  // face classifier
        string eyes_cascade_classifier_path_;  // eyes classifier 

        int face_number_;

    };

}  // namespace kinvrf_img

#endif  // KINVRF_FACE_DETECTOR_H
