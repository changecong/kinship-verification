all: ../../build/lib/face_detector.o ../../build/lib/image_reader.o

../../build/lib/face_detector.o: face_detector.cpp ../../include/face_detector.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c face_detector.cpp -o ../../build/lib/face_detector.o

../../build/lib/image_reader.o: image_reader.cpp ../../include/image_reader.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c image_reader.cpp -o ../../build/lib/image_reader.o