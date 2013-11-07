/*
 * Filename:      change_log.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Wed Nov  6 23:55:39 2013
 * Modified at:   Thu Nov  7 00:53:11 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/version.h"
#include <fstream>  // std::fstream
#include <assert.h>  // assert

using namespace std;

int main(int argc, char** argv) {

    assert(argc >= 2);

    // read the change_log file
    fstream fs ("../change_log.txt", fstream::in | fstream::out | fstream::app);

    if (fs) {

        

        fs << "== " << (int)MAJOR_VERSION_NUMBER << "."
           << (int)MINOR_VERSION_NUMBER << "."
           << (int)REVERSION_NUMBER << " ==" << endl;

        for (int i = 1; i < argc; i++) {
            fs << argv[i] << endl;
        }

        fs << endl;

    }

    // i/o operations here

    fs.close();


    return 0;
}
