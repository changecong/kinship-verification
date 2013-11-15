all: ../../build/obj/gabor.o

../../build/obj/gabor.o: gabor.cpp ../../include/gabor_filter.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c gabor.cpp -o ../../build/obj/gabor.o