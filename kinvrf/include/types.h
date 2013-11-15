/*
 * Filename:      types.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov  6 10:56:38 2013
 * Modified at:   Thu Nov 14 22:06:21 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_TYPES_H
#define KINVRF_TYPES_H

#include <utility>  // pair
#include <cstring>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef pair<string, string> Setting_t;
typedef vector<Mat> Pca_t;

#endif  // KINVRF_TYPES_H
