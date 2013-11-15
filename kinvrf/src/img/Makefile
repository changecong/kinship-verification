all: ../../build/obj/face_detector.o ../../build/obj/image_reader.o

../../build/obj/face_detector.o: face_detector.cpp ../../include/face_detector.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c face_detector.cpp -o ../../build/obj/face_detector.o

../../build/obj/image_reader.o: image_reader.cpp ../../include/image_reader.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c image_reader.cpp -o ../../build/obj/image_reader.o