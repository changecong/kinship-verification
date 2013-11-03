/*
 * Filename:      util_get_resource_inl.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Fri Nov  1 13:40:18 2013
 * Modified at:   Fri Nov  1 15:48:06 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   Provide some utility functions to get resource from /res folder
 *
 */

#ifndef KINVRF_UTIL_GET_RESOURCE_INL_H
#define KINVRF_UTIL_GET_RESOURCE_INL_H

#include "xml_resource.h"
// #include "data_resource.h"

using namespace kinvrf_xml;

namespace kinvrf_res {

   
    class Resource {
        
      public:
        ///\fn
        ///\brief
        Resource(){}
        ~Resource(){}

        ///\fn
        ///\brief
        inline XMLRes* get_xml() {
            return new XMLRes();
        }

        ///\fn
        ///\brief
        // inline TrainingData* get_data() {
        //     return new TrainingData();
        // }
        
    };  // class Resource
    
    ///\fn
    ///\brief used to get resource
    inline Resource* get_resource() {
        return new Resource();
    }


}  // namespace kinvrf_res

#endif  // KINVRF_UTIL_GET_RESOURCE_INL_H
