# Description:
#             This is a simple Makefile to compile PANDA in c++
# Authors:
#             Kimberley Glass, Marouen Ben Guebila 05/2019

gpuPANDA: gpuPANDA.cu
	nvcc -arch=sm_52 -O3 -o gpuPANDA gpuPANDA.cu
	
clean:
	rm *.o *.gcno *.gcda *.pairs
