/*
File:			Huffman.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A class to wrap up Huffman compression algorithm
Notes:			Property of Full Sail University 2406
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <queue>
#include "BitStream.h"

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
#define LAB_8	1

// Individual unit test toggles
#define HUFFMAN_CTOR					1
#define HUFFMAN_GENERATE_FREQUENCY		1
#define HUFFMAN_GENERATE_LEAFLIST		1
#define HUFFMAN_GENERATE_TREE			1
#define HUFFMAN_CLEAR_TREE				1
#define HUFFMAN_DTOR					1
#define HUFFMAN_GENERATE_ENCODING		1
#define HUFFMAN_COMPRESS				1
#define HUFFMAN_DECOMPRESS				1

// Optional unit tests for debugging with small file containing "HELLO WORLD"
#define HUFFMAN_DEBUG_COMPRESS			0
#define HUFFMAN_DEBUG_DECOMPRESS		0

// Wraps up Huffman compression algorithm
class Huffman {

	friend class UnitTests_Lab8; // Giving access to test code

	// A node for a a Huffman tree
	struct HuffNode {
		short value;
		unsigned int freq;
		HuffNode* left;
		HuffNode* right;
		HuffNode* parent;

		HuffNode(short _value, unsigned int _freq, HuffNode* _left = nullptr, HuffNode* _right = nullptr, HuffNode* _parent = nullptr)
			: value(_value), freq(_freq), left(_left), right(_right), parent(_parent) {
		}

		HuffNode(const HuffNode& _hnode)
			: value(_hnode.value), freq(_hnode.freq), left(_hnode.left), right(_hnode.right), parent(_hnode.parent) {
		}
	};

	struct HuffCompare {
		bool operator() (const HuffNode* _a, const HuffNode* _b) {
			return(_a->freq > _b->freq);
		}
	};


	// Data members
	// NOTE: Values set to 1/-1 for unit test purposes
	std::string mFileName = "-1";
	unsigned int mFrequencyTable[256] = { 1 };
	std::vector<HuffNode*> mLeafList;
	HuffNode* mRoot = reinterpret_cast<HuffNode*>(-1);
	std::vector<bool> mEncodingTable[256];


	Huffman(const std::string& _fileName) {
		// TODO: Implement this method
		mFileName = _fileName;
		for (int i = 0; i < 256; ++i)
		{
			mFrequencyTable[i] = 0;
		}
		mRoot = nullptr;
	}

	~Huffman()
	{
		ClearTree();
	}


	void GenerateFrequencyTable()
	{
		std::ifstream file(mFileName, std::ios::binary);

		char genFrq;
		while (file.get(genFrq))
		{
			for (unsigned int i = 0; i < 256; ++i)
				if ((unsigned char)genFrq == i)
					mFrequencyTable[i]++;
		}
		file.close();
	}




	void GenerateLeafList()
	{
		for (int i = 0; i < 256; ++i)
		{
			if (mFrequencyTable[i] != 0)
			{
				HuffNode* node = new HuffNode(i, mFrequencyTable[i]);
				mLeafList.push_back(node);
			}
		}

	}

	void GenerateTree()
	{
		std::priority_queue<HuffNode*, std::vector<HuffNode*>, HuffCompare>priority;
		for (int i = 0; i < mLeafList.size(); ++i)

			priority.push(mLeafList[i]);
		while (priority.size() > 1)
		{
			HuffNode* left = priority.top();
			priority.pop();
			HuffNode* right = priority.top();
			priority.pop();

			HuffNode* parent = new HuffNode(-1, left->freq + right->freq, left, right);
			left->parent = parent;
			right->parent = parent;
			priority.push(parent);
		}
		mRoot = priority.top();
	}

	void GenerateEncodingTable()
	{
		for (int i = 0; i < mLeafList.size(); ++i)
		{
			HuffNode* temp = mLeafList[i];
			std::vector<bool> encoding;
			while (temp != mRoot)
			{
				if (temp == temp->parent->left)
				{
					encoding.push_back(0);
				}
				else if (temp == temp->parent->right)
				{
					encoding.push_back(1);
				}
				temp = temp->parent;
			}
			std::reverse(encoding.begin(), encoding.end());
			mEncodingTable[mLeafList[i]->value] = encoding;
		}

	}

	void ClearTree()
	{
		ClearTree(mRoot);
		mRoot = nullptr;

	}

	void ClearTree(HuffNode* _curr)
	{
		if (_curr != nullptr)
		{
			ClearTree(_curr->left);
			ClearTree(_curr->right);
			delete _curr;
		}

	}

	void Compress(const char* _outputFile)
	{
		GenerateFrequencyTable();		//Create the leaf list and tree by calling the existing methods (in this order)
		GenerateLeafList();
		GenerateTree();
		GenerateEncodingTable();

		BitOfstream bitOf(_outputFile, (const char*)mFrequencyTable, sizeof(unsigned int) * 256);		//Create a BitOfstream and supply it the Huffman header
		//Open the input file in binary mode with a std::ifstream
		std::ifstream fOpen(mFileName, std::ios::binary);	//Create a std::ofstream for output in binary mode NEXT STEP!!!!!
		fOpen.seekg(0, std::ios::end);
		size_t totalSize = fOpen.tellg();
		fOpen.seekg(0, std::ios::beg);
		char* buffer = new char[totalSize];
		fOpen.read(buffer, totalSize);
		for (int i = 0; i < totalSize; ++i)		//Compress the file
		{
			for (unsigned int j = 0; j < 256; ++j)
			{
				if ((unsigned char)buffer[i] == j)
					bitOf << mEncodingTable[j];
			}
		}
		fOpen.close();
		delete[] buffer;
	}

	void Decompress(const char* _outputFile)
	{
		//Create a BitIfstream and read the frequency table

		BitIfstream bitstream(mFileName.c_str(), (char*)mFrequencyTable, 256 * 4);


		//Create the leaf list and tree by calling the existing methods(in this order)	
		GenerateLeafList();
		GenerateTree();
		//Create a std::ofstream for output in binary mode
		std::ofstream fOpen(_outputFile, std::ios::binary);
		//Create a bool to use for traversing down the tree, and an unsigned char for writing to the file
		bool traverse = false;
		
		//Create a HuffNode pointer for use in traversing the tree (start at the top)
		HuffNode* curr = mRoot;

		unsigned int tFrequency = 0;
		for (unsigned int freq : mFrequencyTable)
		{
			tFrequency += freq;
		}

		unsigned int charsDecoded = 0;
		while (charsDecoded < tFrequency)
		{
			while (curr->left || curr->right)
			{
				bitstream >> traverse;
				curr = traverse ? curr->right : curr->left;
			}
			fOpen.put(static_cast<unsigned char>(curr->value));
			++charsDecoded;
			curr = mRoot;
		}
		bitstream.Close();
		fOpen.close();
	}
};

