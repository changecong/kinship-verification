all: knn-test knn-test.o

knn-test: knn-test.o ../../build/obj/*.o
	g++ -ggdb -std=c++11 `pkg-config --cflags opencv ` -I../../ -o knn-test knn-test.o ../../build/obj/ml_data.o ../../build/obj/image_reader.o ../../build/obj/xml_resource.o ../../build/obj/tinyxml2.o ../../build/obj/gabor.o ../../build/obj/ml_knn.o `pkg-config --libs opencv`

knn-test.o: knn-test.cpp 
	g++ -ggdb -std=c++11 `pkg-config --cflags opencv ` -I../../ -c knn-test.cpp -o knn-test.o