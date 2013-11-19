######################################################################
## Filename:      index.py
## Copyright:     2013, Zhicong Chen
## Version:       
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Mon Nov 11 11:34:15 2013
## Modified at:   Sun Nov 17 22:21:41 2013
## Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
## Status:        Experimental, do not distribute.
## Description:   
##
#####################################################################

import web
import mydb
import myos
import mycpp

'''
for class index
'''
image_url = "static/upload/default.jpg"
enable= ["", "disabled"]
lastid = 0;
submitted = 0;
'''
for class faceconfirm
'''
persons_url = []
small_faces_url = []
persons_path = ''
facenum = 0;

# globals = {} 
# declare where templates are
render = web.template.render('templates/', base='base')

urls = (
    '/', 'Index',
    '/faceconfirm', 'FaceConfirm',
    '/ageconfirm', 'AgeConfirm',
    '/result', 'Result'
    )

'''
This class used to return the index page of the website, in which
there are picture updata and face selected functionality.
'''
class Index:


    def GET(self):

        global submitted, image_url, enable

        if not submitted == 0:
            # reset all 
            global lastid

            image_url = "static/upload/default.jpg"
            enable= ["", "disabled"]
            lastid = 0;
            submitted = 0;

            global persons_url, small_faces_url, persons_path, facenum

            persons_url = []
            small_faces_url = []
            persons_path = ''
            facenum = 0;

        

        url = image_url
        return render.index(url, enable)

    def POST(self):
        import time
        import hashlib
        import os

        x = web.input(myfile={})
        filedir = 'static/upload/family/' 
        if 'myfile' in x: 

            image = x.myfile.file.read()

            filepath = x.myfile.filename.replace('\\','/') 
            filename = filepath.split('/')[-1] 
            fileext = filename.split('.', 1)[-1]
            
            # create a new folder
            foldername = filedir

            myos.mkdir(foldername)

            # generate a new name
            filename = hashlib.new("md5", image).hexdigest()

            fullpath = foldername + filename[0:8] + '.' + fileext
            
            global image_url
            global lastid
            # check if the file exists
            # return false if not exist
            if not os.path.isfile(fullpath):
                print filepath
                if fileext.lower() in ['jpg','bmp', 'png']:
                    
                    fout = open(fullpath,'w')
                    fout.write(image) 
                    fout.close() 

                    # write into database
                    lastid = mydb.new_family(fullpath)
                    
                    image_url = fullpath

            else:
                print "this file exist."
                # find its f_id from database
                lastid = mydb.find_family_by_url(fullpath)[0]['f_id']

                image_url = fullpath

            # call c++ code to process the image.
            
        print "lastid(index): " + str(lastid)

        global enable
        enable[0] = 'disabled'
        enable[1] = ''
        
        raise web.seeother('/')

'''
this class is used to open the page to confirm the faces
'''
class FaceConfirm:


    def GET(self):

        global submitted
        
        submitted = 1

        global persons_url, small_faces_url
        global facenum
        global persons_path
        global image_url
        
        persons_url = []
        small_faces_url = []

        # call c++ to process the image.
        # pass image_url in, generate faces

        print "lastid(faceconfirm): " + str(lastid)
               
        filename = image_url.split('/')[-1] 
        filenameprefix = filename.split('.', 1)[0]

        path = "static/upload/person/"
        myos.mkdir(path)
        path = "static/upload/person/" + filenameprefix + "/"
        success = myos.mkdir(path)
        # for small image
        smallsuccess = myos.mkdir(path+'small/')

        persons_path = path

        if success:

            facenum, smallnum = mycpp.eyedetect(image_url, path)
            print "eyes face number: " + str(facenum)
            # write image into data base
            for i in range(facenum):
                mydb.new_person(path+str(i)+'.jpg', lastid)

            # write small image into data base
            for j in range(smallnum):
                mydb.new_small_face(path+'small/'+str(j)+'.jpg', lastid)


        # read from database
        familynumbers = mydb.get_family_numbers(lastid)
        print familynumbers
        for person in familynumbers:
            persons_url.append(person['p_url'])

        # read small images from data
        smallfaces = mydb.get_family_small_faces(lastid)
        print smallfaces
        for face in smallfaces:
            small_faces_url.append(face['s_url'])

        # print self.persons_url
        # pass all to template        

        return render.faceconfirm(image_url, persons_url, small_faces_url)

    def POST(self):

        
        global persons_url
        global facenum
        global persons_path
        global image_url
        
        x = web.input()
        print x
        
        if 'x' in x: px = int(x['x']);
        if 'y' in x: py = int(x['y']);
        if 'w' in x: pw = int(x['w']);
        if 'h' in x: ph = int(x['h']);

        newimgurl = mycpp.crop(image_url, persons_path, px, py, pw, ph, facenum)
        facenum += 1
        print "face number: " + str(facenum)

        global lastid
        mydb.new_person(newimgurl, lastid)

        # get the submit and the do the cut by c++
        raise web.seeother('/faceconfirm')

class AgeConfirm:

    def GET(self):

        #get the post
        info = web.input(checkbox=[])
        # print info
        if 'checkbox' in info:
            faces = info['checkbox']
            

        return render.ageconfirm(faces)

        

    def POST(self):
        
        print "hello"

class Result:
    

    def GET(self):
        #get the post
        info = web.input(olderradio=[], images=[])
        older = []
        images = []

        if 'olderradio' in info:
            older = info['olderradio']
            
        if 'images' in info:
            images = info['images']

        print older
        print images

        old = older[0]
        if old == 'dontknow':
            # do something
            print "hello"
        else:
            i = images.index(old)
            images.remove(old)
            young = images[0]

            print young
            print old
            # pass into cpp code

            iskin = mycpp.iskin(young, old)

        if iskin : 
            print "true"
        else:
            print "false"

        return render.result(iskin, young, old)

if __name__ == '__main__':
    app = web.application(urls, globals())
    app.run()
