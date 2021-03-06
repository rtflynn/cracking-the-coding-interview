// 8_7 - Perms no Dups.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

/*
std::vector<std::string> allPermsOfGivenString(std::string ourString)
{
	std::vector<std::string> allPerms;
	if (ourString.length() <= 1) {
		allPerms.push_back(ourString);
		std::cout << "Blah" << std::endl;
		return allPerms;
	}


	char first = ourString.front();
	std::string suffix = ourString.erase(0, 1);

	std::cout << suffix << " and here we are " << std::endl;


	std::vector<std::string> allPermsOfSuffix = allPermsOfGivenString(suffix);
	for (unsigned int i = 0; i < suffix.length(); i++)
	{
		for (unsigned int j = 0; j < allPermsOfSuffix.size(); j++)
			allPerms.push_back((allPermsOfSuffix[j]).insert(i, 1,  first));   

		std::cout << "la de da" << std::endl;

			//allPerms.push_back(allPermsOfSuffix[j].insert(i, first));
	}

	std::cout << "huh" << std::endl ;
	return allPerms;

}

*/

std::vector<std::string> insertCharInAllLocationsInAllStrings(char someChar, std::vector<std::string>  someStrings, unsigned int currentStringLength);


std::vector<std::string> allPermsOfGivenString(std::string ourString)
{	
	std::vector<std::string> currentVectorOfStrings;
	unsigned int ourStringLength = ourString.length();
	if (ourStringLength == 0)
		return currentVectorOfStrings;
	char firstChar = ourString.front();
	std::string suffix = ourString.erase(0, 1);

	std::vector<std::string> previousVectorOfStrings = allPermsOfGivenString(suffix);
	currentVectorOfStrings = insertCharInAllLocationsInAllStrings(firstChar, previousVectorOfStrings, ourStringLength-1);




	return currentVectorOfStrings;
}

std::vector<std::string> insertCharInAllLocationsInAllStrings(char someChar, std::vector<std::string>  someStrings, unsigned int currentStringLength)
{
	std::vector<std::string> result;
	for (unsigned int i = 0; i <= currentStringLength; i++)
	{
		std::vector<std::string> tempVectorOfStrings = someStrings;
		for (unsigned int j = 0; j < tempVectorOfStrings.size(); j++)
		{
			tempVectorOfStrings[j].insert(i, 1, someChar);
		}
		result.insert(result.end(), tempVectorOfStrings.begin(), tempVectorOfStrings.end());
	}
	

	return result;
}






int main()
{
	std::string myString = "derp";
	std::vector<std::string> myVectorOfStrings = allPermsOfGivenString(myString);
	for (unsigned int i = 0; i < myVectorOfStrings.size(); i++)
		std::cout << myVectorOfStrings[i] << ", ";
	std::cout << std::endl;

	std::cout << myString.front();
	std::cout << myString.erase(0, 1);
	

    return 0;
}

