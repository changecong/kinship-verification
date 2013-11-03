/*
 * Filename:      define_strings.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 14:40:58 2013
 * Modified at:   Sun Nov  3 01:38:33 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_DEFINE_STRINGS_H
#define KINVRF_DEFINE_STRINGS_H

/*
 * XML FILE RELATED
 */
///////////////////////////////////
//  <?xml version="1.0"?>
//  <storage>
//    <!-- strings -->
//    <string name=""></string>
//
//    <!-- numbers -->
//    <number name=""></number>
//  </storage>
////////////////////////////////////

const string KINVRF_XML_RESOURCE_STORAGE = "storage";
const string KINVRF_XML_RESOURCE_STRING = "string";
const string KINVRF_XML_RESOURCE_NUMBER = "number";
const string KINVRF_XML_RESOURCE_NAME = "name";

///////////////////////////////////
//  <?xml version="1.0"?>
//  <settings>
//    <setting type="string" name=""></setting>
//    <setting type="number" name=""></setting>
//  </settings>
////////////////////////////////////

const string KINVRF_XML_RESOURCE_SETTINGS = "settings";
const string KINVRF_XML_RESOURCE_SETTING = "setting";
const string KINVRF_XML_RESOURCE_TYPE = "type";
const string KINVRF_XML_RESOURCE_TYPE_NUMBER = "number";
const string KINVRF_XML_RESOURCE_TYPE_STRING = "string";

/*
 * NAME ATTRIBUTES -- STRINGS
 */


/*
 * NAME ATTRIBUTES -- NUMBERS
 */


/*
 * NAME ATTRIBUTES -- SETTINGS
 */
const string KINVRF_XML_RESOURCE_SETTING_DATARESOURCE = "DataResource";

#endif  // KINVRF_DEFINE_STRING_H
