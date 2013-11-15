all: ../../build/obj/ml_data.o

../../build/obj/ml_data.o: ml_data.cpp ../../include/data_resource.h ../../include/ml_data.h ../../include/ml_test_data.h ../../include/ml_train_data.h ../../include/string_convert.h ../../include/util_data_inl.h
	g++ -fPIC -ggdb -std=c++11 -I../../ `pkg-config --cflags opencv ` -c ml_data.cpp -o ../../build/obj/ml_data.o

