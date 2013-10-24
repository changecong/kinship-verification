######################################################################
## Filename:      version.sh
## Copyright:     2013, Zhicong Chen
## Version:       v1.0.0
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Tue Oct 22 21:47:44 2013
## Modified at:   Wed Oct 23 23:38:41 2013
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
    REVERSION=$VER
    GIT_VERSION=$VER_GIT
else
    GIT_VERSION=
    VER="x"
fi
# remove temporary file
rm -f config.git-hash
# generate a new version.h
cat version.h.template | sed "s/\MGIT_VERSION/$GIT_VERSION/g" |sed "s/\MREVERSION/$REVERSION/g" > include/version.h

echo "new version.h generated"