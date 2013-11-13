all: libeyedetect.so

libeyedetect.so: eye-detect.o ../../build/lib/face_detector.o ../../build/lib/tinyxml2.o ../../build/lib/xml_resource.o ../../build/lib/ml_data.o ../../build/lib/image_reader.o
	g++ -ggdb -std=c++11 `pkg-config --cflags opencv` -shared -Wl,-soname,libeyedetect.so,--no-undefined -o libeyedetect.so eye-detect.o ../../build/lib/face_detector.o ../../build/lib/tinyxml2.o ../../build/lib/xml_resource.o ../../build/lib/ml_data.o ../../build/lib/image_reader.o -I/usr/include/python2.7 -I/usr/lib/python2.7/config `pkg-config --libs opencv`

eye-detect.o: eye-detect.cpp
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c eye-detect.cpp -o eye-detect.o