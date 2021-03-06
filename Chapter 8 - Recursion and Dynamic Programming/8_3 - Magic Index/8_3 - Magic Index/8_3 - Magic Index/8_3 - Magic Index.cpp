// 8_3 - Magic Index.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>


int * randomSortedArray(int length) {
	int * randArray = new int[length];
	randArray[0] = rand();
	for (int i = 1; i < length; i++) {
		int randomInteger = (rand() % 10) + 1;
		randArray[i] = randArray[i - 1] + randomInteger;
	}
	return randArray;
}


/*
int kMagicIndex(int * sortedArray, int length, int k) 
{
	if (length == 0) {
		if (sortedArray[0] == k)
			return 0;
		else
			return -1000;
	}

	int checkIndex = length / 2;
	if (sortedArray[checkIndex] == checkIndex + k)
		return checkIndex;
	if (sortedArray[checkIndex] > checkIndex + k)
		return kMagicIndex(sortedArray, checkIndex, k);
	if (sortedArray[checkIndex] < checkIndex + k)
		return kMagicIndex(sortedArray + checkIndex + 1, length - checkIndex - 1, k + checkIndex + 1) + checkIndex + 1;
}

int magicIndex(int * sortedArray, int length)
{
	return kMagicIndex(sortedArray, length, 0);
}
*/

/*  Note, this is only guaranteed to work if the sorted array consists of DISTINCT integers.  Indeed, consider the hard-coded array below.
	Since A[5]<5, we'd like to conclude that the magic index is to the right of 5, but this conclusion may not be true.
	So, we'll need to rework this solution for the case where the integers may not be distinct.  
	Also, our solution is a bit messy, and can be simplified quite a bit by writing our method as  findMagicIndex(int myArray[], int start, int end), 
	and simply updating start and end as we go, instead of finding k-magic indices.  
	Also, this makes it easier to convey that no magic number exists by returning -1.
*/

int magicIndex(int sortedArray[], int startIndex, int endIndex)
{
	int midIndex = (startIndex + endIndex) / 2;
	// std::cout << startIndex << " " << midIndex << " " << endIndex << std::endl;
	if (sortedArray[midIndex] == midIndex)
		return midIndex;
	if (startIndex >= endIndex)
		return -1;
	if (sortedArray[midIndex] < midIndex)
		return magicIndex(sortedArray, midIndex+1, endIndex);
	if (sortedArray[midIndex] > midIndex)
		return magicIndex(sortedArray, startIndex, midIndex-1);
}

int magicIndex(int sortedArray[], int length)
{
	return magicIndex(sortedArray, 0, length - 1);
}





int main()
{
	int * myArray = randomSortedArray(15);
	for (int i = 0; i < 15; i++)
		std::cout << myArray[i] << ", ";
	std::cout << std::endl;

	int  myHardcodedArray[] = { -10, -5, 2, 2, 2, 6, 7, 8, 9, 12, 13 };
	int myHardcodedArrayLength = 10;
	std::cout << magicIndex(myHardcodedArray, myHardcodedArrayLength) << std::endl;

	for (int i = 0; i < myHardcodedArrayLength; i++)
		std::cout << myHardcodedArray[i] << ", ";
	std::cout << std::endl;


	
	
	
	return 0;
}

