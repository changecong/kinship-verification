/*
 * Filename:      xml_resource.cpp
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Thu Oct 31 12:09:05 2013
 * Modified at:   Sun Nov 17 17:57:29 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

// local include
#include "include/xml_resource.h"
// system
//
#include "include/string_convert.h"  // constant string and converter

namespace kinvrf_xml {

    const string KINVRF_XML_RESOURCE_STRING_XML = "../res/xml/string.xml";
    // const string KINVRF_XML_RESOURCE_STRING_XML = "../../res/xml/string.xml";
    const string KINVRF_XML_RESOURCE_SETTINGS_XML = "../res/xml/settings.xml";
    // const string KINVRF_XML_RESOURCE_SETTINGS_XML = "../../res/xml/settings.xml";

    XMLRes* XML_res() {
        return new XMLRes();
    }

    XMLRes::XMLRes() {

        init();

        // if string_map is empty, fill it
        if(string_map_.empty()) {   
            
            // fill string_map_
            fill_string_map();
        }

        if(number_map_.empty()) {

            fill_number_map();
        }
    }

    //
    string XMLRes::get_string(string name) {
        
        // if string_map is empty, fill it
        if(string_map_.empty()) {
            init();
            fill_string_map();
        }

        return string_map_.find(name)->second;
        
    }

    //
    double XMLRes::get_number(string name) {

        // if string_map is empty, fill it
        if(number_map_.empty()) {
            init();
            fill_number_map();
        }

        return number_map_.find(name)->second;

    }

    //
    pair<string, string> XMLRes::get_setting(string name) {
        return find_setting(name);
    }

    // private
    void XMLRes::init() {

        // load xml file
        bool load_ok = doc_.LoadFile(kinvrf_scvt::string_to_char(
                                         KINVRF_XML_RESOURCE_STRING_XML));
        
        if(!load_ok) {
            // if load file error
            // do something
        }
    }

    // fill string into map once it is called
    void XMLRes::fill_string_map() {
        
        // traversal all element in xml file
        // put <name, value> pair into map
     
        // if(doc_ != NULL) {
        if(true) {
            // get the <allstrings></allstrings> tag
            XMLElement *storage_node = doc_.FirstChildElement(
                kinvrf_scvt::string_to_char(
                    KINVRF_XML_RESOURCE_STORAGE));   

            XMLElement *string_node = storage_node->FirstChildElement(
                kinvrf_scvt::string_to_char(
                    KINVRF_XML_RESOURCE_STRING));

            pair< map<string, string>::iterator, bool> is_conflict; 

            while(string_node != NULL) {
                
                // get strings
                string name_attribute_string = string_node->Attribute(
                    kinvrf_scvt::string_to_char(
                        KINVRF_XML_RESOURCE_NAME));
                
                string string_tag_value = string_node->GetText();
                
                // put into map
                is_conflict = string_map_.insert(pair<string, string>(name_attribute_string,
                                                                      string_tag_value));
                
                if (false == is_conflict.second) {  // there is same name
                    // do something
                }

                // specify <string> tag so that we can add comments in the xml file
                string_node = string_node->NextSiblingElement(
                    kinvrf_scvt::string_to_char(
                        KINVRF_XML_RESOURCE_STRING));
            }    
        }
    }

    // fill string into map once it is called
    void XMLRes::fill_number_map() {
        
        // traversal all element in xml file
        // put <name, value> pair into map
     
        // if(doc_ != NULL) {
        if(true) {
            // get the <allstrings></allstrings> tag
            XMLElement *storage_node = doc_.FirstChildElement(
                kinvrf_scvt::string_to_char(
                    KINVRF_XML_RESOURCE_STORAGE));   

            XMLElement *number_node = storage_node->FirstChildElement(
                kinvrf_scvt::string_to_char(
                    KINVRF_XML_RESOURCE_NUMBER));
            
            pair< map<string, double>::iterator, bool> is_conflict; 

            while(number_node != NULL) {
                
                // get strings
                string name_attribute_string = number_node->Attribute(
                    kinvrf_scvt::string_to_char(
                        KINVRF_XML_RESOURCE_NAME));
                
                string number_tag_value = number_node->GetText();

                // convert string to double
                double number_tag_value_double = kinvrf_scvt::string_to_double(
                    number_tag_value);
                
                // put into map
                is_conflict = number_map_.insert(pair<string, double>(
                                                     name_attribute_string,
                                                     number_tag_value_double));
                
                if (false == is_conflict.second) {  // there is same name
                    // do something
                }

                // specify <string> tag so that we can add comments in the xml file
                number_node = number_node->NextSiblingElement(
                    kinvrf_scvt::string_to_char(
                        KINVRF_XML_RESOURCE_NUMBER));
            }    
        }
    }

    //
    pair<string, string> XMLRes::find_setting(string name) {

        XMLDocument settings_doc;

        // load xml file
        bool load_ok = settings_doc.LoadFile(kinvrf_scvt::string_to_char(
                                                 KINVRF_XML_RESOURCE_SETTINGS_XML));
        
        if(!load_ok) {
            // if load file error
            // do something
        }

        XMLElement *settings_node = settings_doc.FirstChildElement(
            kinvrf_scvt::string_to_char(
                KINVRF_XML_RESOURCE_SETTINGS));   

        XMLElement *setting_node = settings_node->FirstChildElement(
            kinvrf_scvt::string_to_char(
                KINVRF_XML_RESOURCE_SETTING));

        while(setting_node != NULL) {
                

            
            // get strings
            string name_attribute_string = setting_node->Attribute(
                kinvrf_scvt::string_to_char(
                    KINVRF_XML_RESOURCE_NAME));

            if(name == name_attribute_string) {
                break;
            }
                
            setting_node = setting_node->NextSiblingElement(
                kinvrf_scvt::string_to_char(
                    KINVRF_XML_RESOURCE_SETTING));
        }

        string setting_tag_value = "";

        if (NULL != setting_node->GetText()) {

            setting_tag_value = setting_node->GetText();

        } else {
            setting_tag_value = "";
        }

        // get setting type string or number
        string type_attribute_string = setting_node->Attribute(
            kinvrf_scvt::string_to_char(
                KINVRF_XML_RESOURCE_TYPE));

        pair<string, string> type_value_pair (type_attribute_string,
                                              setting_tag_value);

        return type_value_pair;

    }

    map<string, string> XMLRes::string_map_;
    map<string, double> XMLRes::number_map_;

}  // namespace kinvrf_xml
