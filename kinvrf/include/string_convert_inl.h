/*
 * Filename:      string_convert_inl.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 10:54:37 2013
 * Modified at:   Wed Nov 13 12:18:47 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   use some new C++ 11 feature
 *                stoi, stol, stoll convert to integral types,
 *                stof, stod, stold to floating-point values.
 *
 */

#ifndef KINVRF_STRING_CONVERT_INL_H
#define KINVRF_STRING_CONVERT_INL_H

#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace kinvrf_scvt {

    inline double string_to_double(const string& s);
    inline int string_to_int(const string& s);
    template <typename T> inline string number_to_string(T number);
    inline vector<string> string_split(string& src_str, const string& split_str);
    inline string string_trim(const string& src_str);

    // string to number

    /* ///\fn string_to_double() */
    /* ///\brief convert from string to double, it is the standard way in C++ 98 */
    /* inline double string_to_double(const string& s) */
    /* { */
    /*     std::istringstream i(s); */
    /*     double x; */
    /*     if (!(i >> x)) */
    /*         return 0; */
    /*     return x; */
    /* }  */
    
    ///\fn string_to_double()
    ///\brief
    inline double string_to_double(const string& s) {
        return stod(s);
    }

    /* inline int string_to_int(const string& s) { */
    /*     return (int)string_to_double(s); */
    /* } */

    inline int string_to_int(const string& s) {
        return stoi(s);
    }

    ///\fn string_to_char
    ///\brief convert frome string to char*
    inline const char* string_to_char(const string str) {
        return str.c_str();
    }

    // number to string
    
    ///\fn
    ///\brief this function use C++ 11 fucntions
    template <typename T> 
        inline string number_to_string(
        T number) {
        
        // call std::to_string
        return to_string(number);  
    }

    ///\fn
    ///\brief split string by 
    inline vector<string> string_split(string& src_str, const string& split_str) {
        
        vector<string> result;
        string::size_type pos_1, pos_2;
        
        pos_2 = src_str.find(split_str);
        pos_1 = 0;

        while(string::npos != pos_2) {
            result.push_back(string_trim(src_str.substr(pos_1, pos_2 - pos_1)));

            pos_1 = pos_2 + 1;
            pos_2 = src_str.find(' ', pos_1);
        }

        result.push_back(string_trim(src_str.substr(pos_1)));

        return result;
    }

    ///\fn
    ///\brief trim
    inline string string_trim(const string& src_str) {
        if (src_str.empty())   
        {  
            return src_str;  
        }  
  
        string result = src_str;

        result.erase(0, result.find_first_not_of(" "));  
        result.erase(result.find_last_not_of(" ") + 1);  
    
        return result;          
    }

}  // namespcae kinvrf_scvt

#endif  // KINVRF_STRING_CONVERT_INL_H
