#include "stdafx.h"
#include <cstddef>
#include <iostream>

/*
Draw Line:  A monochrome screen is stored as a single array of bytes, allowing eight consecutive pixels to be stored
in one byte.  The screen has width w, where w is divisible by 8 (That is, no byte will be split across rows).  The 
height of the screen, of course, can be derived from the length of the array and the width.  Implement a function
that draws a horizontal line from (x1, y) to (x2, y).

The method signature should look something like:
drawLine(byte[] screen, int width, int x1, int x2, int y)
*/


/*
Note:  This is prettty messy and may not be correct.  Moving on because the amount of time it would take to be sure
that this works in all edge cases, etc, would not be worth it.  This is a simple problem but has lots of places to make
off-by-one errors and other simple errors.  Would be different if I had a Screen class to run tests with, but implementing
my own introduces the possibility that both the DrawLine and the Screen implementations have errors, etc.  Just not worth
the time - I've been through this already with the OLC engine.
*/



char beginChars[8] { 255, 127, 65, 31, 15, 7, 3, 1};
char endChars[8]{ 128, 192, 224, 240, 248, 252, 254, 255 };
char fullByte = 255;


char onesFromBeginToEnd(int begin, int end)
{
	if ((begin > end) or (begin < 0) or (end > 7))
		return 0;
	unsigned total = 0;
	unsigned currentPlace = 128;
	for (int i = 0; i <= 7; i++)
	{
		if ((i >= begin) and (i <= end))
			total += currentPlace;
		currentPlace = currentPlace >> 1;
	}
	return static_cast<char>(total);
}


void drawLine(char screen[], int width, int x1, int x2, int y, int height)
{
	if ((x1 > x2) or (x1 < 0) or (x2 > width) or (y < 0) or (y >= height))
	{
		std::cout << x1 << " " << x2 << " " << width << " " << y << " " << height << std::endl;
		std::cout << "derp" << std::endl;
		return;
	}
		

	int startBit = (y * width + x1);
	int endBit = (y * width + x2);

	int startByte = startBit / 8;
	int endByte = endBit / 8;

	int onesStart = x1 % 8;
	int onesEnd = x2 % 8;

	if (((x2 - x1) == (onesEnd - onesStart)))	// Our line fits entirely within one byte
	{
		screen[startByte] = onesFromBeginToEnd(onesStart, onesEnd);
	}
	else {
		screen[startByte] = beginChars[onesStart];
		for (int i = startByte + 1; i < endByte; i++)
			screen[i] = fullByte;
		screen[endByte] = endChars[onesEnd];
	}

	/*
	for (int x = 0; x < width / 8; x++)
	{
		for (int y = 0; y < height; y++)
		{
			std::cout << screen[int(width / 8 * y + x)] << " ";
		}
		std::cout << std::endl;
	}
	*/


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width / 8; x++)
		{
			std::cout << screen[int(width / 8 * y + x)] << " ";
		}
		std::cout << std::endl;
	}

}



int main()
{
	const int width = 160;
	const int height = 30;
	char ourScreen[8 * width*height];
	std::fill(ourScreen, ourScreen + sizeof(ourScreen), 64);
	
	drawLine(ourScreen, width, 13, 87, 4, height);




    return 0;
}

