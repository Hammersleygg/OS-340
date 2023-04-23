#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double blockSize();
double cacheSize(double byteSize);

#define arraySize 1000

char arrChars [arraySize][arraySize];
char arrChars2 [arraySize][arraySize];
double calcTimeMemory(double array[]);

int main() {
	double timeArray[arraySize];


	double calcBlockSize = blockSize();
	printf("Block size is: %1f\n", calcBlockSize);
	
	double calcCacheSize = cacheSize(calcBlockSize);
	printf("Cache size is: %1f\n", calcCacheSize);
	
	double modeMainMem = calcTimeMemory(timeArray);
	printf("Maim memory reference takes %f nanoseconds\n", modeMainMem * 1000000000);
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
	//set as -1 if errors
	double mode = -1.00;
	
	int temp = 0;
	int temp2 = 0;
	
	//struct for time
	struct timespec start, end;
	
	//getting time
	for(int i = 0; i < arraySize; i++){
		//initialize random index 
		int randomArrX1 = rand() % arraySize;
		int randomArrY1 = rand() % arraySize;
		
		int randomArrX2 = rand() % arraySize;
		int randomArrY2 = rand() % arraySize;
		
		//first array
		temp += arrChars[randomArrX1][randomArrY1];
		
		//start clock
		clock_gettime(CLOCK_REALTIME, &start);
		temp2 += arrChars2[randomArrX2][randomArrY2];
		clock_gettime(CLOCK_REALTIME, &end);
		
		//calculate amount of time
		long seconds = end.tv_sec - start.tv_sec;
		long nanoseconds = end.tv_nsec - start.tv_nsec;
		
		//1e-9 total seconds in nanoseconds
		double time_taken = seconds + nanoseconds * 1e-9;
		
		//store in array
		timeArray[i] = time_taken;
	}
	
	//find mode of times for a maim memory reference
	mode = modeCalc(timeArray);
	//return the mode, if error, then -1 will be return
	return mode;	
}

double modeCalc(double timeArray[]){
	//if error, -2
	double mode = -2.00;
	
	//counter
	int count = 0;
	
	//mode
	for(int i = 0; i < arraySize; i++) {
		int counter = 0;
		for(int j = 0; j < arraySize; j++) {
			if(timeArray[i] == timeArray[j]) {
				counter++;
			}
			if(counter > count) {
				mode = timeArray[i];
				count = counter;
			}
		}
	}
	return mode;
}
