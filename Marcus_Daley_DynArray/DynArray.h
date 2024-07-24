/*
File:			DynArray.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A dynamically-allocated resizeable array (similar to std::vector)
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
#define LAB_1	1

// Individual unit test toggles
#define LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS			1
#define LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS			1
#define LAB1_BRACKET_OPERATOR						1
#define LAB1_SIZE_ACCESSOR							1
#define LAB1_CAPACITY_ACCESSOR						1
#define LAB1_RESERVE_EMPTY							1
#define LAB1_RESERVE_DOUBLE_CAPACITY				1
#define LAB1_RESERVE_LARGER_CAPACITY				1
#define LAB1_RESERVE_SMALLER_CAPACITY				1
#define LAB1_APPEND_NO_RESIZE						1
#define LAB1_APPEND_RESIZE							1
#define LAB1_CLEAR									1
#define LAB1_DESTRUCTOR								1
#define LAB1_ASSIGNMENT_OPERATOR					1
#define LAB1_COPY_CONSTRUCTOR						1

// Our implementation of a vector (simplified)
template<typename Type>
class DynArray {

	// Gives access to test code
	friend class UnitTests_Lab1;

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Type* mArray = reinterpret_cast<Type*>(-1);
	size_t mSize = -1;
	size_t mCapacity = -1;

public:

	DynArray(size_t _startingCap = 0)
	{
		if (_startingCap == 0)
		{
			mArray = nullptr;
			mSize = 0;
			mCapacity = 0;
		}
		else
		{
			mArray = new Type[_startingCap];
			mSize = 0 ;
			mCapacity= _startingCap;
		}
	};

	~DynArray()
	{
		// TODO: Implement this method
		delete[] mArray;
	}

	DynArray(const DynArray& _copy) {
		// TODO: Implement this method
		mSize = _copy.mSize;
		mCapacity = _copy.mCapacity;
		mArray = new Type[mCapacity];
		for (size_t i = 0; i < mSize; ++i)
		{
			mArray[i] = _copy.mArray[i];
		}
	}

	DynArray& operator=(const DynArray& _assign)
	{
		if (this != &_assign)
		{
			delete[] mArray;
			mSize = _assign.mSize;
			mCapacity = _assign.mCapacity;
			mArray = new Type[mCapacity];
			for (size_t i = 0; i < mSize; ++i)
			{
				mArray[i] = _assign.mArray[i];
			}
		}
		return *this;
	}

	void Clear()
	{
		delete[] mArray;
		mArray = nullptr;
		mSize = 0;
		mCapacity = 0;

	}

	Type& operator[](size_t _index)
	{
		return mArray[_index];
	}

	size_t Size() const {
	
		return mSize;
	}

	size_t Capacity() const 
	{
		return mCapacity;
	}

	void Append(const Type& _data)
	{
		if (mSize==mCapacity)
		{
			Reserve(mCapacity * 2);
		}
		mArray[mSize++] = _data;
	}

	void Reserve(size_t _newCapacity = 0)
	{
		if (_newCapacity==0)		//If 0 is passed in
		{
			_newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2;
		}
		if(_newCapacity>mCapacity)
		{
			Type* tempArray = new Type[_newCapacity];
			for (size_t i = 0; i < mSize; ++i)
			{
				tempArray[i] = mArray[i];		//Copy over any data that may be in the smaller array.
			}
			delete[] mArray;
			mArray = tempArray;
			mCapacity = _newCapacity;
		}
	}
};