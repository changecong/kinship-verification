######################################################################
## Filename:      version.sh
## Copyright:     2013, Zhicong Chen
## Version:       v1.0.0
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Tue Oct 22 21:47:44 2013
## Modified at:   Wed Nov  6 23:51:35 2013
## Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
## Status:        Experimental, do not distribute.
## Description:   This is a bash code used to automatically generate
##                a version.h file used the version number from git
##
#####################################################################

#!/bin/bash
rm -f include/version.h # remove old version.h
# git the git commit list, sort then write to config.git-hash
git rev-list HEAD | sort > config.git-hash
# use wc to count the number of lines of config.git-hash
# use awk to assign is to variable LOCALVER
LOCALVER=`wc -l config.git-hash | awk '{print $1}'`
if [ $LOCALVER \> 1 ] ; then
    VER=`git rev-list origin/master | sort | join config.git-hash - | wc -l | awk '{print $1}'`
    if [ $VER != $LOCALVER ] ; then
	VER="$VER+$(($LOCALVER-$VER))"
    fi
    # if git status | grep -q "modified:" ; then
    # 	VER="$(VER)M"
    # fi
    VER_GIT="$(git rev-list HEAD -n 1 | cut -c 1-7)"
    VER_PRE=33  # number that before a major version or minor version update 
    REVERSION=$(($VER-$VER_PRE))   
    GIT_VERSION=$VER_GIT
else
    GIT_VERSION=
    VER="x"
fi
# remove temporary file
rm -f config.git-hash

MAJOR_VERSION=0
MINOR_VERSION=3  # data module partly done

# generate a new version.h
cat res/template/version.h.template | sed "s/\MMAJOR_VERSION/$MAJOR_VERSION/g" | sed "s/\MMINOR_VERSION/$MINOR_VERSION/g" | sed "s/\MGIT_VERSION/$GIT_VERSION/g" |sed "s/\MREVERSION/$REVERSION/g" > include/version.h

echo "new version.h generated"