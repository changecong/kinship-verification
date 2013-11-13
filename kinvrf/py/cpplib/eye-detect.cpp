/*
 * Filename:      eye-detect.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Mon Nov 11 23:41:02 2013
 * Modified at:   Tue Nov 12 20:03:42 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/face_detector.h"
#include "include/image_reader.h"
#include "include/string_convert.h"
#include <cstring>
#include <opencv2/opencv.hpp>

using namespace kinvrf_img;
using namespace kinvrf_scvt;
using namespace std;
using namespace cv;

extern "C" {

    int eye_detect(char* image_path, char* external_path) {
    
        string path0 = image_path;
        string path1 = external_path;
        vector<Mat> faces;
        int i = 0;

        FaceDetector* fd = new FaceDetector(path0);

        fd->external_path(path1);

        faces = fd->corrected_faces();

        for(vector<Mat>::const_iterator face = faces.begin();

            face != faces.end(); face++) {
            imwrite(path1+number_to_string(i++)+".jpg", *face);
        }

        return faces.size();

    }

    int family_member(char* image_path) {
        string path0 = image_path;
        FaceDetector* fd = new FaceDetector(path0);
        return  fd->face_number();
    }

    char* image_crop(char* image_path, char* external_path,
                    int x, int y, int w, int h, int id) {

        string path0 = image_path;
        string path1 = external_path;
        ImageReader* ir = new ImageReader(path0);

        Mat face = ir->image_crop(x, y, w, h);
        Mat face100x127;
        face100x127.create(127, 100,  CV_8UC1);
        
        // resize
        resize(face,  // src image 
               face100x127,  // dis image
               face100x127.size(),  // size
               0,  // scale of x 
               0,  // scale of y
               // INTER_NEAREST
               INTER_LINEAR
               // INTER_CUBIC
               // INTER_AREA
               // INTER_LANCZOS4
            );

        string path = path1+number_to_string(id)+".jpg";
        imwrite(path, face100x127);
        
        char* ret = new char[path.length()+1];
        strcpy(ret, path.c_str());
        return ret;
    }
}
