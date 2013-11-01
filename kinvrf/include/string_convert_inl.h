/*
 * Filename:      string_convert_inl.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 10:54:37 2013
 * Modified at:   Fri Nov  1 11:13:44 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_STRING_CONVERT_INL_H
#define KINVRF_STRING_CONVERT_INL_H

#include <sstream>
#include <string>

namespace kinvrf_scvt {

    ///\fn string_to_double()
    ///\brief convert from string to double
    inline double string_to_double(const std::string& s)
    {
        std::istringstream i(s);
        double x;
        if (!(i >> x))
            return 0;
        return x;
    } 

    ///\fn string_to_char
    ///\brief convert frome string to char*
    inline const char* string_to_char(const string str) {
        return str.c_str();
    }

}  // namespcae kinvrf_scvt

#endif  // KINVRF_STRING_CONVERT_INL_H
