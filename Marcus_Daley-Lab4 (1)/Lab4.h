/*
File:			DSA_Lab4.h	
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::list class
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
#define LAB_4	1

// Individual unit test toggles
#define LAB4_QUEUE_ADD			1
#define LAB4_STACK_ADD			1
#define LAB4_QUEUE_REMOVE		1
#define LAB4_STACK_REMOVE		1
#define LAB4_INSERT_ITER		1
#define LAB4_INSERT_INDEX		1
#define LAB4_REMOVE_DECIMAL		1

/************/
/* Includes */
/************/
#include <list>

class DSA_Lab4 {

	friend class UnitTests_Lab4;	// Giving access to test code

	// Data members
	std::list<float> mList;

public:
	void QueueOrderingAdd(const float* _arr, int _size)
	{
		mList.clear();
		for (size_t i = 0; i < _size; ++i)
		{
			mList.push_back(_arr[i]);
		}
	}
	

	void StackOrderingAdd(const float* _arr, size_t _size) 
	{
		// TODO: Implement this method
		size_t son = _size - 1;
		for (int i = 0; i < _size; i++)
		{
			mList.push_back(_arr[son]);
			son--;
		}
	}

	float QueueOrderingRemove() 
	{
		std::list<float>::iterator iter = mList.begin();
		float temp = *iter;
		mList.remove(*iter);
		return temp;
		
	}

	float StackOrderingRemove() 
	{
		std::list<float>::iterator iter = mList.begin();
		float temp = *iter;
		mList.remove(*iter);
		return temp;
	}

	void Insert(int _index, float _val)
	{
		int temp = 0;
		for (int i = 0; i < _index; i++)
		{
			temp++;
		}
		std::list<float>::iterator iter = mList.begin();
		std::advance(iter, _index);
		mList.insert(iter, _val);
		
	}

	void Insert(std::list<float>::iterator _iter, float _val) {
		mList.insert(_iter, _val);
		
	}

	int RemoveDecimalGreater(float _decimal) 
	{
		int count = 0;
		float decimalNum = _decimal - (int)_decimal;	//Get the Decimal part of _decimal
		for (auto rip = mList.begin(); rip != mList.end();)
		{
			float listDecimalNum = *rip - (int)*rip;  //Get the Decimal part of the lis value
			if (listDecimalNum > decimalNum)
			{
				rip = mList.erase(rip);
				count++;
			}
			else
			{
				++rip;
			}
		}
		return count;
		
	}
 	
};