all: ../../build/obj/ml_data.o ../../build/obj/ml_knn.o ../../build/obj/main/gen_training_data.o ../../build/bin/gen_training_data

../../build/obj/ml_data.o: ml_data.cpp ../../include/*.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c ml_data.cpp -o ../../build/obj/ml_data.o

../../build/obj/ml_knn.o: ml_knn.cpp ../../include/*.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c ml_knn.cpp -o ../../build/obj/ml_knn.o

../../build/obj/main/gen_training_data.o: gen_training_data.cpp ../../include/data_resource.h ../../include/util_data_inl.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c gen_training_data.cpp -o ../../build/obj/main/gen_training_data.o

../../build/bin/gen_training_data: ../../build/obj/main/gen_training_data.o ../../build/obj/*.o
	g++ -ggdb -std=c++11 `pkg-config --cflags opencv ` -I../../ -o ../../build/bin/gen_training_data ../../build/obj/main/gen_training_data.o ../../build/obj/ml_data.o ../../build/obj/image_reader.o ../../build/obj/xml_resource.o ../../build/obj/tinyxml2.o ../../build/obj/gabor.o `pkg-config --libs opencv`