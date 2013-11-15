all: data-test data-test.o

data-test: data-test.o ../../build/obj/ml_data.o ../../build/obj/image_reader.o ../../build/obj/xml_resource.o ../../build/obj/tinyxml2.o ../../build/obj/gabor.o
	g++ -ggdb -std=c++11 `pkg-config --cflags opencv ` -I../../ -o data-test date-test.o ../../build/obj/ml_data.o ../../build/obj/image_reader.o ../../build/obj/xml_resource.o ../../build/obj/tinyxml2.o ../../build/obj/gabor.o `pkg-config --libs opencv`

data-test.o: data-test.cpp 
	g++ -ggdb -std=c++11 `pkg-config --cflags opencv ` -I../../ -c data-test.cpp -o date-test.o
