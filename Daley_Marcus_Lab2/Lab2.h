/*
File:			Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::vector class
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
#define LAB_2	1

// Individual unit test toggles
#define LAB2_PALINDROME_NUMBER		1
#define LAB2_FILL_FILE				1
#define LAB2_FILL_ARRAY				1
#define LAB2_CLEAR					1
#define LAB2_SORT_ASCENDING			1
#define LAB2_SORT_DESCENDING		1
#define LAB2_BRACKETS				1
#define LAB2_CONTAINS_TRUE			1
#define LAB2_CONTAINS_FALSE			1
#define LAB2_MOVE_PALINDROMES		1


/************/
/* Includes */
/************/
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


inline int IsPalindromeNumber(unsigned int _num)
{
	unsigned int num = 0;
	unsigned int temp = _num;
	while (temp > 0)
	{
		num = num * 10 + (temp % 10);
		temp /= 10;
	}
	return (_num == num);
}

class DSA_Lab2
{
	friend class UnitTests_Lab2;	// Giving access to test code

private:

	std::vector<int> mValues;		// contains all of the values
	std::vector<int> mPalindromes;	// contains just the numbers that are palindromes (only used in MovePalindromes method)

public:

	void Fill(const char* _inputFilename) 
	{	
		std::ifstream binFile(_inputFilename, std::ios::binary);
		int numValues;
		
		
		binFile.read(reinterpret_cast<char*>(&numValues), 4);
		for (int i = 0; i < numValues; ++i)
		{
			int val;	
			binFile.read(reinterpret_cast<char*>(&val), 4);
			mValues.push_back(val);
		}
		binFile.close();
	}

	void Fill(const int* _arr, size_t _size) 
	{
		for (int i = 0; i < _size; ++i)
		{
			mValues.push_back(_arr[i]);
		}

	}

	void Clear()
	{
		
		mValues.clear();
		mValues.shrink_to_fit();

	}

	void Sort(bool _ascending) {
		// TODO: Implement this method
		if (_ascending)
		{
			std::sort(mValues.begin(), mValues.end());
		}
		else
		{
			std::sort(mValues.rbegin(), mValues.rend());
		}
	}

	int operator[](int _index) 
	{
		return mValues[_index];
	
	}

	bool Contains(int _val) const
	{
		for (int i = 0; i < mValues.size(); ++i)
		{
			if (mValues.at(i) == _val)
			{
				return true;
				break;
			}
		}
		return false;
	}

	void MovePalindromes()
	{
		for (int i = 0; i < mValues.size(); )
		{
			if (IsPalindromeNumber(mValues.at(i)))
			{
				mPalindromes.push_back(mValues.at(i));
				mValues.erase(mValues.begin() + i);
			}
			else
			{
				++i;
			}
		}
	}
};

