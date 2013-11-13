######################################################################
## Filename:      myos.py
## Copyright:     2013, Zhicong Chen
## Version:       
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Tue Nov 12 12:14:48 2013
## Modified at:   Tue Nov 12 12:15:41 2013
## Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
## Status:        Experimental, do not distribute.
## Description:   
##
#####################################################################

import os

def mkdir(path):
        
    path=path.strip()
    path=path.rstrip("\\")
    
    isExists=os.path.exists(path)
    
    if not isExists:
        print path + ' success'
        os.makedirs(path)
        return True
    else:
        print path + ' exists'
        return False
