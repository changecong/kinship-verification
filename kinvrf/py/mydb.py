######################################################################
## Filename:      mydb.py
## Copyright:     2013, Zhicong Chen
## Version:       
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Mon Nov 11 14:54:09 2013
## Modified at:   Tue Nov 12 13:03:35 2013
## Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
## Status:        Experimental, do not distribute.
## Description:   
##
#####################################################################

import web

db = web.database(dbn='mysql', user='kinvrf', pw='kinvrf', db='kinvrfDB')
'''
|========|       |========|        |==============|
|t_family|<------|t_person|<-------|   t_kinship  |
|========|       |========|<-------|==============|
|    f_id|       |    p_id|        |          k_id|
|--------|       |--------|        |--------------|
|   f_url|       |   p_url|        |        p_id_1|
|--------|       |--------|        |--------------|
|  f_name|       |  p_name|        |        p_id_2|
|--------|       |--------|        |--------------|
|  f_time|       |p_gender|        |k_relationship|
|--------|       |--------|        |--------------|
                 |    f_id|
                 |--------|

'''
family = 't_family'
person = 't_person'
kinship = 't_kinship'

# put the new upload image into the database, set family name to empty
def new_family(path):
    id = db.insert(family, f_url=path)
    return id

# update the family name
def update_family_name(id, name):
    db.update(family, where='f_id = $id', f_name=name)

# find the photo by url
def find_family_by_url(url):
    return db.select(family, what='f_id', where='f_url=$url', vars=dict(url=url), limit=1)

# put images into person table
def new_person(path, f_id):
    id = db.insert(person, p_url=path, f_id=f_id)
    return id

# get all image with a family
def get_family_numbers(id):
    return db.select(person, what='p_url', where='f_id=$id', vars=dict(id=id))
