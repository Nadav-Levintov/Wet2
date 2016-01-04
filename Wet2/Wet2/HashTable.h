#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "AVLTree.h"
#include <iostream>
#include <assert.h>
#include <exception>

#define ARRAYINLARGE 2
#define ARRAYFULLFACTOR 1
using std::exception;


template<class T, class C, class K>
class HashTable
{
	int arraySize;
	int numOfItems;
	K keyFunc;
	avlTree<T, C>* hashArray;

private:

public:
	class NotFound :public exception {};
	class Exists :public exception {};

	HashTable(int initSize = 2) : arraySize(initSize), numOfItems(0)
	{
		keyFunc = K();
		hashArray = new avlTree<T, C>[arraySize];
	}
	~HashTable()
	{
		delete[] hashArray;
	}
	int hashing(int index) {
		return index % arraySize;
	}
	void enlargeArray()
	{
		int oldSize = arraySize;
		arraySize *= ARRAYINLARGE;
		numOfItems = 0;
		avlTree<T, C>* oldArray = hashArray;
		avlTree<T, C>* newArray = new avlTree<T, C>[arraySize];
		hashArray = newArray;
		for (int i = 0; i < oldSize; i++)
		{
			T* oldContent = oldArray[i].inOrder();
			int treeSize = oldArray[i].getSize();
			for (int j = 0; j < treeSize; j++)
			{
				insert(oldContent[j]);
			}
			delete[] oldContent;
		}
		delete[] oldArray;
	}
	
	void insert(T& item)
	{
		if (numOfItems == ARRAYFULLFACTOR * arraySize)
		{
			enlargeArray();
		}
		
		if (hashArray[hashing(keyFunc(item))].find(item))
		{
			throw Exists();
		}
		hashArray[hashing(keyFunc(item))].insert(item);
		numOfItems++;
	}
	T& member(int itemID) {
		T searchItem = T(itemID);
		if (!hashArray[hashing(itemID)].find(searchItem))
		{
			throw NotFound();
		}
		T& item = hashArray[hashing(itemID)].find(searchItem)->getData();
		
		return item;
	}

	void del(int itemID)
	{
		T searchItem = T(itemID);
		if (!hashArray[hashing(itemID)].find(searchItem))
		{
			throw NotFound();
		}
		hashArray[hashing(itemID)].remove(searchItem);
		
	}
};

#endif /*HASH_TABLE*/