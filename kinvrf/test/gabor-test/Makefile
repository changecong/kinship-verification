all: gabor-test gabor-test.o

gabor-test: gabor-test.o ../../build/obj/image_reader.o ../../build/obj/gabor.o
	g++ -ggdb `pkg-config --cflags opencv ` -I../../ -o gabor-test gabor-test.o ../../build/obj/image_reader.o ../../build/obj/gabor.o `pkg-config --libs opencv`

gabor-test.o: gabor-test.cpp 
	g++ -ggdb `pkg-config --cflags opencv ` -I../../ -c gabor-test.cpp -o gabor-test.o
