/*
 * Filename:      xml_resource.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Thu Oct 31 12:08:58 2013
 * Modified at:   Fri Nov  1 00:31:14 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_XML_RESOURCE_H
#define KINVRF_XML_RESOURCE_H

// system include
#include <string>
#include <map>
// local
#include "tinyxml2.h"

// namespace
using namespace std;
using namespace tinyxml2;

namespace kinvrf_xml {

    class XMLRes;

    XMLRes* XML_res();

    ///\class XMLRes
    ///\brief a class that used to get string from xml files. so that do not need to
    ///       re-compile the source code each time string contents are changed.
    ///       usage:
    ///           XML_res().get_string(string_name);
    ///           XML_res().get_int(int_name);
    ///       While names are attributes of xml element
    class XMLRes {

      public:

        ///\fn
        ///\brief
        XMLRes();
        ~XMLRes(){}

        ///\fn get_string()
        ///\brief
        string get_string(string name);

        ///\fn get_int()
        double get_number(string name);

      private:
        
        // some helper methods
        // used for initialization
        void init();

        ///\fn 
        ///\brief
        void fill_string_map();
        
        ///\fn
        ///\brief
        void fill_number_map();


        XMLDocument doc_;
        static map<string, string> string_map_;
        static map<string, double> number_map_;

    };  // class XMLRes

}  // namespace kinvrf_xml

#endif  //KINVRF_XML_RESOURCE_H
