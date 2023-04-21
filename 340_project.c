#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double blockSize();
double cacheSize(double byteSize);

#define arraySize 1000

char arrChars [arraySize][arraySize];
char arrChars2 [arraySize][arraySize];

int main() {
	double calcBlockSize = blockSize();
	printf("Block size is: %1f\n", calcBlockSize);
	
	double calcCacheSize = cacheSize(calcBlockSize);
	printf("Cache size is: %1f\n", calcCacheSize);
}

double blockSize(){
	int blockArray = 4;
	char myArray[blockArray][blockArray];
	
	for(int i = 0; i < blockArray; i++) {
		for(int j = 0; j < blockArray; j++) {
			myArray[i][j] += myArray[i][j];
		}
	}
	
	double blockResult = sizeof(myArray) * pow(2,2);
	double byteSize = blockResult;
	
	//printf("%f\n", byteSize);
	return byteSize;
}

double cacheSize(double byteSize) {
	int cacheArray = 128;
	char myArray[cacheArray][cacheArray];
	
	for(int i = 0; i < cacheArray; i++){
		for(int j = 0; j < cacheArray; j++){
			myArray[i][j] += myArray[i][j];
		}
	}
	
	double cacheResult = sizeof(myArray);
	double cacheByteSize = cacheResult;
	
	double cacheSize = cacheByteSize/byteSize;
	return cacheSize;
}

double calcTimeMemory(double timeArray[]) {
	//set -1 for errors
	double err = -1.00;
	
	int temp = 0;
	int temp2 = 0;
	
	struct timeSpec start, end;
	
	//getting time 
	for(int i = 0; i < arraySize; i++) {
		int randomArrX1 = rand() % arraySize;
		int randomArrY1 = rand() % arraySize;
		
		int randomArrX2 = rand() % arraySize;
		int randomArrY2 = rand() % arraySize;
		
		//first array
		temp += arrChars[randomArrX1][randomArrY1];
		
		//starting clock
		clock_gettime(CLOCK_REALTIME, &start);
		
		temp2 += arrChars2[randomArrX2][randomArrY2];
		
		//ending clock
		clock_gettime(CLOCK_REALTIME, &end);
		
		//calc time 
		long seconds = end.tv_sec - start.tv_sec;
		long nano = end.tv_nsec - start.tv_nsec;
		
		//1e-9 total second in nanosecond
		double totalTime = seconds + nano * 1e-9;
		
		//store in array
		timeArray[i] = totalTime;
	}
	
	
	//mode
	err = modeCalc(timeArray);
	return err;
}
