/*
 * Filename:      string_convert_inl.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 10:54:37 2013
 * Modified at:   Sun Nov  3 00:08:47 2013
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

using namespace std;

namespace kinvrf_scvt {

    // string to number
/*
    ///\fn string_to_double()
    ///\brief convert from string to double, it is the standard way in C++ 98
    inline double string_to_double(const string& s)
    {
        std::istringstream i(s);
        double x;
        if (!(i >> x))
            return 0;
        return x;
    } 
*/
    
    ///\fn string_to_double()
    ///\brief
    inline double string_to_double(const string& s) {
        return stod(s);
    }

    inline double string_to_int(const string& s) {
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
    inline template <typename TNumber> string number_to_string(
        TNumber number) {
        
        // call std::to_string
        return to_string(number);  
    }

}  // namespcae kinvrf_scvt

#endif  // KINVRF_STRING_CONVERT_INL_H
