/*
File:			DSA_Lab6.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::unordered_map class
Notes:			Property of Full Sail University 2406
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Main toggle
#define LAB_6	1

// Individual unit test toggles
#define LAB6_POPULATE_LETTER_VALUES	1
#define LAB6_GET_LETTER_VALUE		1
#define LAB6_GET_WORD_VALUE			1
#define LAB6_CREATE_PAIR			1
#define LAB6_LOAD_FILE				1
#define LAB6_FIND_WORD_SCORE		1

/************/
/* Includes */
/************/
#include <string>
#include <fstream>
#include <unordered_map>

class DSA_Lab6 {

	friend class UnitTests_Lab6;	// Giving access to test code

	// Data members
	int mLetterValues[26] = { -1 };
	std::unordered_map<std::string, int> mScrabbleMap;

public:

	void PopulateLetterValues(const int* _letterValues)
	{
		for (int i = 0; i < 26; ++i)
		{
			mLetterValues[i] = _letterValues[i];
		}

	}

	int GetLetterValue(char _letter) const 
	{
		return mLetterValues[_letter - 'A'];

	}

	int GetWordValue(const std::string& _word) const
	{
		int total = 0;
		for (auto iter = _word.begin(); iter != _word.end(); ++iter)
		
			total += GetLetterValue(*iter);
			return total;
		
	}

	std::pair<std::string, int> CreatePair(const std::string& _word) const
	{
		return std::pair<std::string, int>(_word, GetWordValue(_word));

	}

	void LoadWords(const char* _filename)
	{
		std::ifstream fin(_filename);
		while (!fin.eof())
		{
			std::string file;
			std::getline(fin, file);
			mScrabbleMap.insert(CreatePair(file));
		}
		fin.close();

	}

	int FindValueInMap(const std::string& _word) 
	{
		auto iter = mScrabbleMap.find(_word);
		if (iter != mScrabbleMap.end())
		{
			return iter->second;
		}
		else
		{
			return -1;
		}

	}
};
