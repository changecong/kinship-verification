/*
 * Filename:      util_data_inl.h
 * Copyright:     2013, Zhicong Chen
 * Version:       
 * Author:        Zhicong Chen <zhicong.chen@changecong.com>
 * Created at:    Tue Nov  5 22:24:51 2013
 * Modified at:   Wed Nov  6 13:57:44 2013
 * Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
 * Status:        Experimental, do not distribute.
 * Description:   
 *
 */

#ifndef KINVRF_UTIL_DATA_INL_H
#define KINVRF_UTIL_DATA_INL_H

#include <stdio.h>
#include <cstdlib>
#include <string.h>

namespace kinvrf_ml {

// 2 x 3
//                       *arr \       
// [I, I; E, E, E; E, E, E] = |I|[E, E, E]
//                            |I|[E, E, E]
//                      *head/

    // utility functions that used to get a dynamic 2d array
    
    ///\fn
    ///\brief used to generate a 2d array dynamically
    inline void** dynamic_array(size_t row, size_t col, size_t size) {

        // create a pointer
        void **arr;

        size_t array_size = sizeof(void *) * row + size * row * col;

        // allocate
        arr = (void **) malloc(array_size);

        if (NULL != arr) {
            
            void *head;  // head address of each row from the last
            head = (void *)arr + sizeof(void *) * row;
            
            // initialize to 0
            memset(arr, 0, array_size);

            while (row--) {
                arr[row] = head + size * row * col;
            }
        }

        return arr;
    }

    ///\fn
    ///\brief reduce the dimension of array to 1d
    template<typename T>
        inline T* reshape_dynamic_array(size_t src_row, 
                                       size_t src_col, 
                                       T** src_arr) {
        // gen a 1d array
        T* arr = NULL;
        arr = (T*)malloc(sizeof(T) * src_row * src_col);
        for (size_t i = 0; i < src_row; i++) {
            size_t offset = i * src_col * sizeof(T);
            memcpy(arr + offset, src_arr[i], src_col*sizeof(T));
        }

        return arr;
        
    }

    ///\fn
    ///\brief
    template<typename T>
    inline void free_dynamic_array(T **arr) {
        if (NULL != arr) {
            free(arr);
        }
    }

}  // namespace kinvrf_ml

#endif  // KINVRF_UTIL_DATA_INL_H
