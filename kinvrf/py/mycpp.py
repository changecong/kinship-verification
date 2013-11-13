######################################################################
## Filename:      mycpp.py
## Copyright:     2013, Zhicong Chen
## Version:       
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Mon Nov 11 23:00:09 2013
## Modified at:   Tue Nov 12 19:59:18 2013
## Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
## Status:        Experimental, do not distribute.
## Description:   
##
#####################################################################

from ctypes import *
lib = cdll.LoadLibrary('./cpplib/libeyedetect.so')
lib.image_crop.restype = c_char_p

def eyedetect(path0, path1):

    return lib.eye_detect(path0, path1)

def familymember(path0):

    return lib.family_member(path0)

def crop(path0, path1, x, y, w, h, id):

    url = lib.image_crop(path0, path1, x, y, w, h, id)
    return url
