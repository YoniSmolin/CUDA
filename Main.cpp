/*
 * Main.cpp -- an example program that calls a CUDA filter
 */

#include "Filter.h"

#include <iostream>

#define ROWS 512
#define COLS 1024

using namespace std;

int main( int argc, char** argv )
{
	uchar threshold = (uchar) 100;

	// Generate a ramp 8-bit single channle image
	uchar inImage[ROWS*COLS];
	for(int row = 0; row < ROWS; row++)
		for(int col = 0; col < COLS; col++)
			inImage[row*COLS + col] = (uchar) ((col/(float)COLS) * 255);
	
	// Filter out small and large values - CPU
	uchar outImageCPU[ROWS*COLS];
	for(int row = 0; row < ROWS; row++)
		for(int col = 0; col < COLS; col++)
		{
			int index = row*COLS + col;
			outImageCPU[index] = (inImage[index] < threshold) ? inImage[index] : 0;
		}
	
	// Filter out small and large values - GPU
	uchar outImageGPU[ROWS*COLS];
	FilterGPU(inImage, outImageGPU, ROWS, COLS, threshold); 

	// Compare results
	bool areEqual = true;
	for(int row = 0; row < ROWS; row++)
		for(int col = 0; col < COLS; col++)
		{
			int index = row*COLS + col;
			areEqual = areEqual && outImageGPU[index] == outImageCPU[index];
		}

	cout << "GPU and CPU results are" << (areEqual ? " " : " not ") << "equal" << endl;

	return 0;
}

