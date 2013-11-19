/*
 * Filename:      face_detector.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Sun Nov 10 11:27:32 2013
 * Modified at:   Sun Nov 17 17:26:34 2013
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

///\namespace kinvrf_img
///\brief Contains functions and classes which are defined for Image module of the project
namespace kinvrf_img {

    ///\class FaceDetector
    ///\brief A class that used to detect faces from image.
    class FaceDetector {

      public:

        ///\fn FaceDetector(const string& path)
        ///\param [in] path the path of image from which detects faces.
        ///\brief Constructor
        explicit FaceDetector(const string& path);

        ///\fn ~FaceDetector()
        ///\brief Disctructor
        ~FaceDetector();

        ///\fn Mat image()
        ///\return a cv::Mat instance.
        ///\brief Return the original image read in.
        Mat image();

        ///\fn vector<Mat> corrected_faces()
        ///\return a vector of cv::Mat instances.
        ///\brief return faces that has beed corrected for next step usage. 
        vector<Mat> corrected_faces();

        ///\fn vector<Mat> detected_faces()
        ///\return a vector of cv::Mat instances.
        ///\brief not all faces detected can be corrected.
        vector<Mat> detected_faces();

        ///\fn vector<Mat> detected_faces()
        ///\return a vector of cv::Mat instances.
        ///\brief Write faces in to the path;.
        int detected_faces(const string& path);

        ///\fn void external_path(const string& path)
        ///\param [in] path the image path.
        ///\brief Manually change the image path after construction.
        void external_path(const string& path);

        ///\fn int face_number()
        ///\return An intager number.
        ///\brief Return the number of faces that has been detected.
        int face_number();

      private:

        ///\fn void init(const string& path)
        ///\param [in] path the image path.
        ///\brief Initialization, during the initilization, basic face detection occurs.
        void init(const string& path);

        ///\fn FaceDetector()
        ///\brief default constructor that is declared as private.
        FaceDetector();

        ///\fn vector<Rect> face_detect()
        ///\return A vector of cv::Rect instances.
        ///\brief Detects faces from image, return the area for each face in the original image.
        vector<Rect> face_detect();

        ///\fn vector<Mat> face_split()
        ///\return A vector of cv::Mat instances.
        ///\brief Split each detected face into different cv::Mat
        vector<Mat> face_split();

        ///\fn vector<Rect> eyes_detect(Mat* face)
        ///\param [in] face a pointer of a cv::Mat face instance.
        ///\return A vector of cv::Rect instances.
        ///\brief Return the area of eyes for each face.
        vector<Rect> eyes_detect(Mat* face);

        ///\fn void face_correct(Mat* face)
        ///\param [in] face a pointer of a cv::Mat face instance.
        ///\brief Correct each face by the position of eyes detected.
        void face_correct(Mat* face);

        ///\fn double scale_from_setting()
        ///\return A double value.
        ///\brief Get scale for face detection from settings.xml
        double scale_from_setting();

        ///\fn string face_cascade_classifier_from_setting()
        ///\return A std::string value.
        ///\brief Get the cascade classifier of face detection from settings.xml.
        string face_cascade_classifier_from_setting();

        ///\fn string eyes_cascade_classifier_from_setting()
        ///\return A std::string value.
        ///\brief Get the first choice cascade classifier of eyes detection from settings.xml.
        string eyes_cascade_classifier_from_setting();
        
        ///\fn eyes_cascade_classifier_back_up_from_setting()
        ///\return A std::string value.
        ///\brief Get the second choice cascade classifier of eyes detection from settings.xml.
        string eyes_cascade_classifier_back_up_from_setting();

        ///\fn show_faces()
        ///\brief Show faces one by one, only used for Manually test
        void show_faces();

        ///\fn raw_faces()
        ///\brief Since the images we used to detect faces usually are resize by the scale we set. 
        ///       We need to Map the area of each face back to the original size
        void raw_faces();

        ///\fn eye_faces()
        ///\brief After doing the face correction, the face may be enlarged or rotated, 
        ///       there are extra image area that ensure no blank in the corrected face image. 
        ///       Thus the image used for eyes detection would be resized.
        void eye_faces();

        ///\fn string string_setting(const string name)
        ///\param [in] name the name attribute of the settings.
        ///\return A string value.
        ///\brief Utility function that used to get string settings from settings.xml.
        string string_setting(const string name);

        ///\fn double number_setting(const string name)
        ///\param [in] name the name attribute of the settings.
        ///\return A double value.
        ///\brief Utility function that used to get number settings from settings.xml.
        double number_setting(const string name); 

        ImageReader* image_reader_;  ///< ImageReader object.
        Mat image_;  ///< Original image. 

        vector<Rect> faces_;  ///< Vector that used to store faces corresponding to the small image.
        vector<Rect> raw_faces_;  ///< Vector that used to store faces corresponding to the original image.
        vector<Rect> eye_faces_;  ///< Vector that used to store faces that used to detect eyes.

        vector<Mat> faces_mat_;  ///< All faces detected.
        vector<Mat> corrected_faces_;  ///< All valid faces after correction.

        double scale_;  ///< The scale used to resize the image, default is 1.3, get from settings.xml

        size_t image_width_;  ///< Image width (original).
        size_t image_height_;  ///< Image height (original).

        string face_cascade_classifier_path_;  ///< Path of face classifier, get from settings.xml.
        string eyes_cascade_classifier_path_;  ///< Path of eyes classifier, get from settings.xml.

        string external_path_;  ///< Path that set from server.

        int face_number_;  /// Number of faces detected.

    };  // class FaceDetector

}  // namespace kinvrf_img

#endif  // KINVRF_FACE_DETECTOR_H
