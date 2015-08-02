default: Filter

Filter: Filter.o Main.cpp
	nvcc -g Main.cpp Filter.o --pre-include Filter.h -o Filter 

Filter.o: Filter.h Filter.cu
	nvcc -g -c Filter.cu 
