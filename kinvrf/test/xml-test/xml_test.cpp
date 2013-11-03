/*
 * Filename:      xml_test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 11:18:45 2013
 * Modified at:   Fri Nov  1 15:46:43 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/util_get_resource.h"
#include <iostream>

using namespace std;
using namespace kinvrf_res;


int main() {
    
    cout << "string test: " << get_resource()->get_xml()->get_string("hello") << endl;
    cout << "number test: " << get_resource()->get_xml()->get_number("zeropointone") << endl;
    cout << "settings test: " << get_resource()->get_xml()->get_setting("settoone") << endl;

    return 0;
}
