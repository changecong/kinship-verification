/*
 * Filename:      xml_test.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 11:18:45 2013
 * Modified at:   Fri Nov  1 11:25:47 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#include "include/xml_resource.h"
#include <iostream>

using namespace std;
using namespace kinvrf_xml;


int main() {
    
    cout << XML_res()->get_string("hello") << endl;
    cout << XML_res()->get_number("zeropointone") << endl;

    return 0;
}
