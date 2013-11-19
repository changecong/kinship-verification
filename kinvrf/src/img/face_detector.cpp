/*
 * Filename:      face_detector.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Sun Nov 10 11:27:01 2013
 * Modified at:   Sun Nov 17 18:04:01 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/face_detector.h"
#include "include/types.h"  // Setting_t
#include "include/string_convert.h"  // number_to_string
#include "include/util_get_resource.h"

using namespace kinvrf_res;
using namespace kinvrf_scvt;

namespace kinvrf_img {

    // public

    FaceDetector::FaceDetector(const string& path) :
        scale_(1.3),
        face_cascade_classifier_path_("haarcascade_frontalface_alt.xml"),
        eyes_cascade_classifier_path_("haarcascade_eye.xml"),
        external_path_("./"),
        face_number_(0) {

        init(path);        
    }

    FaceDetector::~FaceDetector(){}

    Mat FaceDetector::image() {

        show_faces();
        return image_;
    }

    vector<Mat> FaceDetector::corrected_faces() {
        
         for (vector<Mat>::const_iterator face = faces_mat_.begin();
              face != faces_mat_.end(); face++) {

             Mat face_mat = *face;

             face_correct(&face_mat);

         }

         return corrected_faces_;
    }

    vector<Mat> FaceDetector::detected_faces() {
        
        vector<Mat> face_vec;

        for (vector<Rect>::const_iterator face = raw_faces_.begin();
             face != raw_faces_.end(); face++) {
            
            Mat one_face = image_(*face);
            // resize face to 70x70
            Mat small = Mat(70,70,CV_8UC1);
            resize(one_face,  // src image 
               small,  // dis image
               small.size(),  // size
               0,  // scale of x 
               0,  // scale of y
               // INTER_NEAREST
               INTER_LINEAR
               // INTER_CUBIC
               // INTER_AREA
               // INTER_LANCZOS4
            );

            // imshow("why", small);
            // waitKey();

            face_vec.push_back(small);

        }

        return face_vec;
    }

    int FaceDetector::detected_faces(const string& path) {
        
        vector<Mat> face_vec = detected_faces();
        string small_face_path = path;
        int i = 0;
        for (vector<Mat>::const_iterator face = face_vec.begin();
             face != face_vec.end(); face++, i++) {
            
            imwrite(small_face_path + number_to_string(i) + ".jpg",
                    *face);
        }

        return face_number();
    }

    void FaceDetector::external_path(const string& path) {
        external_path_ = path;
    }

    int FaceDetector::face_number() {
        return faces_.size();
    }

    // private:

    void FaceDetector::init(const string& path) {
        image_reader_ = new ImageReader(path);

        // get scale_ from setting
        // if null, keep default
        scale_ = scale_from_setting();
        face_cascade_classifier_path_ = face_cascade_classifier_from_setting();
        eyes_cascade_classifier_path_ = eyes_cascade_classifier_from_setting();

        if(!image_reader_->image_is_read()) {
            // TODO a warning in log
        }
        
        image_ = image_reader_->image_mat();
        image_width_ = image_reader_->image_width();
        image_height_ = image_reader_->image_height();

        // detect face
        faces_ = face_detect();

        // split each face detected from image
        // set each face to straight
        faces_mat_ = face_split();
    }

    FaceDetector::FaceDetector(){}

    vector<Rect> FaceDetector::face_detect() {
        
        if(!image_reader_->image_is_read()) {
            // TODO
        }

        // convert the image into a single channel gray image
        Mat image_gray;  // single gray image
        Mat image_small;  // image with lower resolution
        image_small.create(cvRound(image_height_/scale_),
                           cvRound(image_width_/scale_),
                           CV_8UC1);

        // convert to gray image
        cvtColor(image_, image_gray, CV_BGR2GRAY);
        resize(image_gray,  // src image 
               image_small,  // dis image
               image_small.size(),  // size
               0,  // scale of x 
               0,  // scale of y
               // INTER_NEAREST
               INTER_LINEAR
               // INTER_CUBIC
               // INTER_AREA
               // INTER_LANCZOS4
            );

        // equalize histogram
        equalizeHist(image_small, image_small); 

        // face detection
        CascadeClassifier face_cascade;

        if(!face_cascade.load(face_cascade_classifier_path_)) {
            // TODO error to log
        }

        face_cascade.detectMultiScale(
            image_small,
            faces_,
            1.1,
            3,
            0 | CV_HAAR_SCALE_IMAGE,
            Size(30, 30));  // now the face is in the faces_

        face_number_ = faces_.size();  // get the number of faces

        // re scale
        raw_faces();

    }

    vector<Mat> FaceDetector::face_split() {

        if(0 == face_number_) {
            // TODO Warning
        }

        vector<Mat> faces;

        for (vector<Rect>::const_iterator face = eye_faces_.begin();
             face != eye_faces_.end(); face++) {

            Mat image_ROI;

            image_ROI = image_(*face);

            faces.push_back(image_ROI);
        }

        return faces;
        
    }

    vector<Rect> FaceDetector::eyes_detect(Mat* face) {

        double scale = 1.1;

        if (face->empty()) {
            // TODO Warning
        }

        if (face->rows > 200) {
            scale = scale_;
        }

        // convert the image into a single channel gray image
        Mat face_gray;  // single gray image
        Mat face_small;  // image with lower resolution
        face_small.create(cvRound(face->rows/scale),
                          cvRound(face->cols/scale),
                          CV_8UC1);

        // convert to gray image
        cvtColor(*face, face_gray, CV_BGR2GRAY);
        
        resize(face_gray,  // src image 
               face_small,  // dis image
               face_small.size(),  // size
               0,  // scale of x 
               0,  // scale of y
               // INTER_NEAREST
               INTER_LINEAR
               // INTER_CUBIC
               // INTER_AREA
               // INTER_LANCZOS4
            );

        // equalize histogram
        equalizeHist(face_small, face_small); 
             
        // face detection
        CascadeClassifier eyes_cascade;

        if(!eyes_cascade.load(eyes_cascade_classifier_path_)) {
            // TODO error to log
        }  

        vector<Rect> eyes;

        eyes_cascade.detectMultiScale(
            face_small,
            eyes,
            1.1,
            3,
            0 | CV_HAAR_SCALE_IMAGE,
            Size(30, 30));  // now the eyes is in the eyes
             
        if( 2 != eyes.size()) {
            
            printf("Second try ... \n");

            // change a classifier
            // face detection
            CascadeClassifier eyes_cascade_backup;
            string backup = eyes_cascade_classifier_back_up_from_setting();

            if(!eyes_cascade_backup.load(backup)) {
                // TODO error to log
            }  

            eyes_cascade_backup.detectMultiScale(
                face_small,
                eyes,
                1.1,
                3,
                0 | CV_HAAR_SCALE_IMAGE,
                Size(30, 30));  // now the eyes is in the eyes

            if(2 != eyes.size()) {
                // TODO
            }
        }
             
        for (vector<Rect>::iterator eye = eyes.begin();
             eye != eyes.end(); eye++) {
            
            eye->x = cvRound(eye->x * scale);
            eye->y = cvRound(eye->y * scale);

            eye->width = cvRound(eye->width * scale);
            eye->height = cvRound(eye->height * scale);

 /*           // test
            rectangle(*face,
                      Point(eye->x, eye->y),
                      Point(eye->x+eye->width, eye->y+eye->height),
                      Scalar(255,0,0));  // blue
 */            
        }

        // imshow("eyes", *face);
        // waitKey();

        return eyes;
    }
    
    void FaceDetector::face_correct(Mat* face) {

        // restrict face with 100x127
        // int i = 0;
        
        // eyes
        vector<Rect> eyes = eyes_detect(face);
        Rect left_eye;
        Rect right_eye;
        Point2f eyes_center;

        const double DESIRED_RIGHT_EYE_X = 1.0f-0.22;
        const double DESIRED_RIGHT_EYE_y = 0.30;
        const double DESIRED_LEFT_EYE_X = 0.22;  
        const double DESIRED_LEFT_EYE_Y = 0.30;  
        
        const int DESIRED_FACE_WIDTH = 100;
        const int DESIRED_FACE_HEIGHT = 127;
       
        if( 2 == eyes.size()) {
            if (eyes[0].x < eyes[1].x) {
                left_eye = eyes[0];
                right_eye = eyes[1];
            } else {
                left_eye = eyes[1];
                right_eye = eyes[0];
            }

            // get eye center
            eyes_center.x = (left_eye.x + left_eye.width/2 + 
                             right_eye.x + right_eye.width/2) * 0.5f;
            eyes_center.y = (left_eye.y + left_eye.height/2 +
                             right_eye.y + right_eye.height/2) * 0.5f;

            double dx = right_eye.x - left_eye.x;
            double dy = right_eye.y - left_eye.y;

            double eyes_lenght = sqrt(dx*dx + dy*dy);  // length between eyes 

            double eyes_angle = atan2(dy, dx)*180.0/CV_PI;


            double desired_length = (DESIRED_RIGHT_EYE_X - DESIRED_LEFT_EYE_X);
            double scale = desired_length * DESIRED_FACE_WIDTH / eyes_lenght;

            printf("scale: %f\n", scale);

            Mat rotation_mat = getRotationMatrix2D(eyes_center, eyes_angle, scale);

            double ex = DESIRED_FACE_WIDTH * 0.5f - eyes_center.x;
            double ey = DESIRED_FACE_HEIGHT * DESIRED_LEFT_EYE_Y - eyes_center.y;

            printf("ex: %f\n", ex);
            printf("ey: %f\n", ey);

            rotation_mat.at<double>(0, 2) += ex;
            rotation_mat.at<double>(1, 2) += ey;

            Mat warped_mat = Mat(DESIRED_FACE_HEIGHT,
                                 DESIRED_FACE_WIDTH,
                                 CV_8UC1,
                                 Scalar(128));
            
            warpAffine(*face, warped_mat, rotation_mat, warped_mat.size());
            printf("%d\n", (int)eyes.size());

           
            // imwrite(external_path_ + number_to_string(i) + ".jpg", warped_mat);
            

            /// for test
            // imshow("face", warped_mat);
            // waitKey();

            // i++;

            corrected_faces_.push_back(warped_mat);

        } else {
            printf("%d\n", (int)eyes.size());
            // the faces can not be correct automatically, need the user to do
            // it manually
        }
        

    }

    double FaceDetector::scale_from_setting() {
        double temp = number_setting(KINVRF_XML_RESOURCE_SETTING_IMAGESCALE);
        
        if (0.0 == temp) {
            return scale_;
        } else {
            return temp;
        }

    }

    string FaceDetector::face_cascade_classifier_from_setting() {

        String temp = string_setting(
            KINVRF_XML_RESOURCE_SETTING_FACECASCADECLASSIFIERPATH);

        if ("" == temp) {
            return face_cascade_classifier_path_;
        } else {
            return temp;
        }
    }

    string FaceDetector::eyes_cascade_classifier_from_setting() {

        String temp = string_setting(
            KINVRF_XML_RESOURCE_SETTING_EYESCASCADECLASSIFIERPATH);

        if ("" == temp) {
            return eyes_cascade_classifier_path_;
        } else {
            return temp;
        }
    }
    
    string FaceDetector::eyes_cascade_classifier_back_up_from_setting() {
        
        String temp = string_setting(
            KINVRF_XML_RESOURCE_SETTING_EYESCASCADECLASSIFIERBACKUPPATH);
        
        return temp;
        
    }

    void FaceDetector::show_faces() {

        for (vector<Rect>::const_iterator face = raw_faces_.begin();
             face != raw_faces_.end(); face++) {
            
            Point left_top;
            Point right_bottom;

            left_top.x = face->x;
            left_top.y = face->y;

            right_bottom.x = face->x + face->width;
            right_bottom.y = face->y + face->height;

            rectangle(image_,
                      left_top,
                      right_bottom,
                      Scalar(255,0,0));  // blue
        }
    }

    void FaceDetector::raw_faces() {

        raw_faces_ = faces_;

        for (vector<Rect>::iterator face = raw_faces_.begin();
             face != raw_faces_.end(); face++) {
            
            face->x = cvRound(face->x * scale_);
            face->y = cvRound(face->y * scale_);

            face->width = cvRound(face->width * scale_);
            face->height = cvRound(face->height * scale_);
            
        }

        eye_faces();
    }

    void FaceDetector::eye_faces() {

        double scale = 1.2;
        eye_faces_ = raw_faces_;

        for (vector<Rect>::iterator face = eye_faces_.begin();
             face != eye_faces_.end(); face++) {
           
            face->x = cvRound(face->x - (face->width * (scale - 1)/2));
            face->x = (face->x < 0) ? 0 : face->x;
            face->y = cvRound(face->y - (face->height* (scale - 1)/2));
            face->y = (face->y < 0) ? 0 : face->y;

            face->width = cvRound(face->width * scale);
            if((face->x + face->width) > image_.cols) {
                face->width = image_.cols - face->x;
            }
            face->height = cvRound(face->height * scale);
            if((face->y + face->height) > image_.rows) {
                face->height = image_.rows - face->y;
            }

        }
    }

    string FaceDetector::string_setting(const string name) {

        XMLRes* xml_resource = get_resource()->get_xml();

        // get setting ImageDataPath
        Setting_t setting = xml_resource->get_setting(name);

        if(KINVRF_XML_RESOURCE_TYPE_STRING == setting.first) {
            return setting.second;
        } 
        
        return "";
    }

    double FaceDetector::number_setting(const string name) {

        XMLRes* xml_resource = get_resource()->get_xml();

        // get setting ImageDataPath
        Setting_t setting = xml_resource->get_setting(name);

        if(KINVRF_XML_RESOURCE_TYPE_NUMBER == setting.first) {
            return string_to_double(setting.second);
        } 
        
        return 0.0;
    }

}  // namespace kinvrf_img
