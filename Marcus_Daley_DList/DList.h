/*
File:			DList.h\
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A doubly-linked list (similar to std::list)
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
#define LAB_3	1

// Individual unit test toggles			
#define LAB3_CTOR						1
#define LAB3_NODE_CTOR_DEFAULT			1
#define LAB3_NODE_CTOR					1
#define LAB3_ADDHEAD_EMPTY				1
#define LAB3_ADDHEAD					1
#define LAB3_ADDTAIL_EMPTY				1
#define LAB3_ADDTAIL					1
#define LAB3_CLEAR						1
#define LAB3_DTOR						1
#define LAB3_ITER_BEGIN					1
#define LAB3_ITER_END					1
#define LAB3_ITER_INCREMENT_PRE			1
#define LAB3_ITER_INCREMENT_POST		1
#define LAB3_ITER_DECREMENT_PRE			1
#define LAB3_ITER_DECREMENT_POST		1
#define LAB3_ITER_DEREFERENCE			1
#define LAB3_INSERT_EMPTY				1
#define LAB3_INSERT_HEAD				1
#define LAB3_INSERT_MIDDLE				1
#define LAB3_ERASE_EMPTY				1
#define LAB3_ERASE_HEAD					1
#define LAB3_ERASE_TAIL					1
#define LAB3_ERASE_MIDDLE				1
#define LAB3_ASSIGNMENT_OP				1
#define LAB3_COPY_CTOR					1

template<typename Type>
class DList {

	friend class UnitTests_Lab3;	// Giving access to test code

	struct Node {
		// NOTE: Values set to -1 for unit test purposes
		Type data;
		Node* next = reinterpret_cast<Node*>(-1);
		Node* prev = reinterpret_cast<Node*>(-1);

	
		Node(const Type& _data, Node* _next = nullptr, Node* _prev = nullptr) 
		{
			data = _data;
			next = _next;
			prev = _prev;
			
		}
	};

public:

	class Iterator {
	public:

		Node* mCurr = reinterpret_cast<Node*>(-1);

		Iterator& operator++() 
		{
			if(mCurr!= nullptr)
			{
				mCurr = mCurr->next;
			}
			return *this;

		
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			if (mCurr != nullptr)
			{
				mCurr = mCurr->next;
			}
			return temp;
			
		}

		Iterator& operator--()
		{
			
			if (mCurr != nullptr)
			{
				mCurr = mCurr->prev;
			}
			return *this;
		}

		Iterator operator--(int) 
		{
			Iterator temp = *this;
			if (mCurr != nullptr)
			{
				mCurr = mCurr->prev;
			}
			return temp;
			
		}

		Type& operator*()
		{
			return mCurr->data;
		}

	
		bool operator != (const Iterator& _iter) const 
		{
			return mCurr != _iter.mCurr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mHead = reinterpret_cast<Node*>(-1);
	Node* mTail = reinterpret_cast<Node*>(-1);
	size_t mSize = -1;

public:

	DList() 
	{
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;	
	}

	~DList()
	{
		Clear();
		
	}

	DList(const DList& _copy)
	{
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;
		Node* newNode;
		Node* current = _copy.mHead;
		while (current != nullptr)
		{
			Node* newNode = new Node(current->data);
			if (mHead == nullptr)
			{
				mHead = newNode;
				mTail = newNode;
			}
			else
			{
				mTail->next = newNode;
				newNode->prev = mTail;
				mTail = newNode;
			}
			current = current->next;
			mSize++;
		}

	};

	DList& operator=(const DList& _assign)
	{
		if (this != &_assign)
		{
			Clear();		//Clear any existing data

			Node* otherListNode = _assign.mHead;
			while (otherListNode != nullptr)
			{
				AddTail(otherListNode->data);
				otherListNode = otherListNode->next;

			}
		}
		return *this;
	};

	void AddHead(const Type& _data) {
		Node* newNode = new Node(_data);
		if (mHead == nullptr)
		{
			mHead = newNode;
			mTail = newNode;
			mSize++;

		}
		else
		{
			newNode->next = mHead;
			newNode->prev = nullptr;
			mHead->prev = newNode;
			mHead = newNode;
			mSize++;
		}

	};

	void AddTail(const Type& _data)
	{
		Node* newNode = new Node(_data);
		//If list is empty, set both head and tail to the new node
		if (mHead == nullptr)
		{
			mHead = newNode;
			mTail = newNode;
		}
		else
		{
			mTail->next = newNode;
			newNode->prev = mTail;
			mTail = newNode;
		}
		mSize++;
	};

	void Clear()
	{
		Node* current = mHead;
		if (current != nullptr)
		{
			while (current != nullptr)
			{
				Node* next = current->next;		//Store the next node
				
				delete current;	//Delete the current node
				current = next;	//Move to the next node
			}
		}
		//Reset pointers
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;
	}

	Iterator Insert(Iterator& _iter, const Type& _data)
	{
		Node* newNode = new Node(_data);

		if (!_iter.mCurr)
		{
			if (!mHead)
			{
				mHead = newNode;
				mTail = newNode;
			}
			else
			{
				newNode->next = mHead;
				mHead->prev = newNode;
				mHead = newNode;
			}
			mSize++;
		}
		else
		{
			if (_iter.mCurr == mHead)
			{
				newNode->next = mHead;
				mHead->prev = newNode;
				mHead = newNode;
			}
			else
			{
				Node* beforeNode = _iter.mCurr->prev;
				Node* afterNode = _iter.mCurr;
				if (beforeNode)
				{
					beforeNode->next = newNode;
				}
				else
				{
					mHead = newNode;
				}
				newNode->prev = beforeNode;
				newNode->next = afterNode;
				afterNode->prev = newNode;
				
			}mSize++;
		}
		_iter.mCurr = newNode;
		return _iter;
	};
	

	Iterator Erase(Iterator& _iter)
	{
		if (_iter.mCurr == nullptr)
		{
			return _iter;
		}
		Node* prevNode = _iter.mCurr->prev;
		Node* nextNode = _iter.mCurr->next;
		if (_iter.mCurr == mHead)		//If _iter points to the head of the list
		{
			mHead = nextNode;		//Update mHead to point to the next node
			if (nextNode != nullptr)
			{
				nextNode->prev = nullptr;
			}
		}
		else   //Or update thr next pointer of the previous node to
		{
			prevNode->next = nextNode;
			if (nextNode != nullptr)
			{
				nextNode->prev = prevNode;
			}
		}
		if (_iter.mCurr == mTail)
		{
			mTail = prevNode;
		}
		delete _iter.mCurr;
		mSize--;
		_iter.mCurr = nextNode;
		return _iter;
	};

	Iterator Begin() const 
	{
		return Iterator(mHead);
		
	}

	Iterator End() const
	{
		return Iterator(nullptr);
		
	}
};