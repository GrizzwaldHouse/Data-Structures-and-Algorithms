/*
File:			BST.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A binary search tree
Notes:			Property of Full Sail University 2406
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>

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
#define LAB_7	1

// Individual unit test toggles
#define BST_CTOR								1
#define BST_NODE_CTOR							1
#define BST_PUSH_EMPTY							1
#define BST_PUSH_LEFT							1
#define BST_PUSH_RIGHT							1
#define BST_CLEAR								1
#define BST_DTOR								1
#define BST_CONTAINS_FOUND						1
#define BST_CONTAINS_NOTFOUND					1
#define BST_REMOVE_CASE0_ROOT					1
#define BST_REMOVE_CASE0_LEFT					1
#define BST_REMOVE_CASE0_RIGHT					1
#define BST_REMOVE_CASE1_ROOT_LEFT				1
#define BST_REMOVE_CASE1_ROOT_RIGHT				1
#define BST_REMOVE_CASE1_LEFT_LEFT				1
#define BST_REMOVE_CASE1_LEFT_RIGHT				1
#define BST_REMOVE_CASE1_RIGHT_LEFT				1
#define BST_REMOVE_CASE1_RIGHT_RIGHT			1
#define BST_REMOVE_CASE2_CASE0					1
#define BST_REMOVE_CASE2_CASE1					1
#define BST_REMOVE_CASE0						1
#define BST_REMOVE_CASE1						1
#define BST_REMOVE_CASE2						1
#define BST_REMOVE_NOT_FOUND					1
#define BST_IN_ORDER_TRAVERSAL					1
#define BST_ASSIGNMENT_OP						1
#define BST_COPY_CTOR							1


// Templated binary search tree
template<typename Type>
class BST {

	friend class UnitTests_Lab7;	// Giving access to test code

	struct Node {
		Type data;					
		Node* left, * right;		
		Node* parent;				

		Node(const Type& _data, Node* _parent = nullptr)
		{
			data = _data;
			parent = _parent;
			left = nullptr;
			right = nullptr;
		}

		
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mRoot = reinterpret_cast<Node*>(-1);	

public:

	BST() {
		mRoot = nullptr;	

	}

	~BST() 
	{
		Clear(mRoot);

	}

	BST(const BST& _copy)
	{
		mRoot = nullptr;
		Copy(_copy.mRoot);
	}

	BST& operator=(const BST& _assign) {
		if (this != &_assign) 
		{
			Clear();
			Copy(_assign.mRoot);
		}
		return *this;
	}

private:
	// Recursive helper method for use with Rule of 3
	void Copy(const Node* _curr)
	{
		
		if (_curr != nullptr)
		{
			Push(_curr->data);
			Copy(_curr->left);
			Copy(_curr->right);
		}
			
	}

public:

	void Clear() 
	{
		Clear(mRoot);
		mRoot = nullptr;
	}

private:

	// Recursive helper method for use with Clear
	void Clear(Node* _curr)
	{
		if (_curr != nullptr)
		{
			Clear(_curr->left);
			Clear(_curr->right);
			delete _curr;
		}
	}

public:

	void Push(const Type& _val)
	{
		if (mRoot == nullptr)
		{
			mRoot = new Node(_val);
		}
		else
		{
			Node* temp = mRoot;
			Node* parent;
			while (true)
			{
				if (_val < temp->data)
				{
					if (temp->left == nullptr)
					{
						temp->left = new Node(_val, temp);
						break;
					}
					else
					{	
						parent = temp;
						temp = temp->left;
					}
				}
				else
				{
					if (temp->right == nullptr)
					{
						temp->right = new Node(_val, temp);
						break;
					}
					else
					{
						parent = temp;
						temp = temp->right;
						
					}
				}
				
			}
		}
	}
	bool Contains(const Type& _val) 
	{
		if (FindNode(_val) != nullptr)
			return true;
		else
			return false;


	}

private:

	Node* FindNode(const Type& _val) 
	{
		Node* temp = mRoot;
		while (temp != nullptr)
		{
			if (_val < temp->data)
			{
				temp = temp->left;
			}
			else if (_val > temp->data)
			{
				temp = temp->right;
			}
			else if (_val == temp->data)
			{
				return temp;
			}
		}
		return nullptr;
	}

	void RemoveCase0(Node* _node)
	{
		if (_node == mRoot)
		{
			mRoot = nullptr;
		}
		else if (_node ->parent->left ==_node)
			{
				_node->parent->left = nullptr;
			}
		else
		{
			_node->parent->right = nullptr;
		}
		delete _node;
	}
	void RemoveCase1(Node* _node)
	{
		Node* child = (_node->left != nullptr) ? _node->left : _node->right;
		if (_node == mRoot)
		{
			mRoot = child;
			child->parent = nullptr;

		}
		else
		{
			_node->parent->left = (_node->parent->left == _node) ? child : _node->parent->left;
			_node->parent->right = (_node->parent->right == _node) ? child : _node->parent->right;
			child->parent = _node->parent;
		}
		delete _node;
	}

	void RemoveCase2(Node* _node) 
	{
		Node* mini = _node->right;
		while (mini ->left != nullptr)
		{
			mini = mini->left;
		}
		_node->data = mini->data;
		if (mini->right == nullptr)

		{
			RemoveCase0(mini);
		}
		else
		{
			RemoveCase1(mini);
		}
	}

public:

	bool Remove(const Type& _val)
	{
		if (mRoot == nullptr)
		{
			return false;
		}
		Node* rnode = FindNode(_val);
		if (rnode == nullptr)
		{
			return false;
		}
			if (rnode->left == nullptr && rnode->right == nullptr)
			{
				RemoveCase0(rnode);
			}
			else if (rnode->left != nullptr && rnode->right != nullptr)
			{
				RemoveCase2(rnode);
			}
			else 
			{
				RemoveCase1(rnode);
			}
		return true;
	};
	std::string InOrder()
	{
		std::string stg;
		InOrder(mRoot, stg);
		if (!stg.empty())
		{
			stg.erase(stg.size() - 1);

		}return stg;

	}

private:

	// Recursive helper method to help with InOrder
	void InOrder(Node* _curr, std::string& _str) 
	{
		//// TODO: Implement this method
		if (_curr != nullptr)
		{
			InOrder(_curr->left, _str);
			
			_str += std::to_string(_curr->data) + " ";
			InOrder(_curr->right, _str);
		}
	}
};

