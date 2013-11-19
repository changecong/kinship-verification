/*
 * Filename:      gen_training_data.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Sat Nov 16 23:12:13 2013
 * Modified at:   Sun Nov 17 14:27:05 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/data_resource.h"  // class TrainData
#include "include/util_data_inl.h"  // string_setting()
#include <iostream>  // cout endl

using namespace kinvrf_ml;
using namespace std;

int main(int argv, char** argc) {

    string path = string_setting(
        KINVRF_XML_RESOURCE_SETTING_IMAGEDATAPATH);

    DataRes* dr = new DataRes(path);

    cout << "Eigen vectors generating" << endl;    

    dr->gen_eigen_vectors();

    // Cout << "Feature value generating" << endl;

    // dr->gen_feature_data();

    cout << "Done" << endl;

    return 0;
}


