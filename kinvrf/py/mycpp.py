######################################################################
## Filename:      mycpp.py
## Copyright:     2013, Zhicong Chen
## Version:       
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Mon Nov 11 23:00:09 2013
## Modified at:   Sun Nov 17 21:43:45 2013
## Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
## Status:        Experimental, do not distribute.
## Description:   
##
#####################################################################

from ctypes import *
lib = cdll.LoadLibrary('./cpplib/libeyedetect.so')
lib.image_crop.restype = c_char_p

def eyedetect(path0, path1):
    num = c_int()
    return lib.eye_detect(path0, path1, byref(num)), num.value

def familymember(path0):

    return lib.family_member(path0)

def crop(path0, path1, x, y, w, h, id):

    url = lib.image_crop(path0, path1, x, y, w, h, id)
    return url

def iskin(path0, path1):
    print path0
    print path1
    path0=path0.encode()    
    path1=path1.encode()    
    return lib.iskin(path0, path1)
