/*
 * Filename:      image-reader-test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Oct 23 16:04:29 2013
 * Modified at:   Wed Oct 23 23:29:01 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   This file is used to test the functionality of class
 *                ImageReader
 *
 */

// include tested header
#include "include/image_reader.h"
// system includes
#include <string>
#include <stdio.h>

using namespace std;

int main() {
    
    string imagename("../lena.jpg");
    // generate an emapty ImageReader
    ImageReader* ir_empty = new ImageReader();
    // generate a new ImageReader by file name
    ImageReader* ir_file = new ImageReader(imagename);
    // generate a new ImageReader by other ImageReader
    ImageReader* ir_other = new ImageReader(*ir_file);
    
    Mat mat_file = ir_file->image_mat();
    // generate a new ImageReader by a mat
    ImageReader* ir_mat = new ImageReader(mat_file);

    printf("width: %d, height: %d", ir_mat->image_width(), ir_mat->image_height());

    return 0;
}
