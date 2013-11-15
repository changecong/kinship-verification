all: ../../build/obj/xml_resource.o

../../build/obj/xml_resource.o: xml_resource.cpp ../../include/xml_resource.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c xml_resource.cpp -o ../../build/obj/xml_resource.o