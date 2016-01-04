#ifndef DS_H
#define DS_H

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "Student.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "AVLTree.h"


using std::exception;

class DS
{
	int numOfFacultys;
	int* maxArray;
	int* maxIdArray;
	int* gradesHistogram;
	UnionFind facultys;
	avlTree<Student, StudentComparer> studentTree;
	HashTable<Student, StudentComparer, StudentIDKey> ht;


public:
	class InvalidInput :public exception {};
	class Failure :public exception {};

	DS(int numOfFacu) :numOfFacultys(numOfFacu),facultys(numOfFacu)
	{
		if (numOfFacu < 2)
		{
			throw InvalidInput();
		}
		maxArray = new int[numOfFacu];
		maxIdArray = new int[numOfFacu];
		gradesHistogram = new int[101];
	}
	~DS()
	{
		delete[] maxArray;
		delete[] maxIdArray;
		delete[] gradesHistogram;
	}
	void AddStudent(int studentID, int average);
	void AssignStudent(void* DS, int studentID, int studyGroup);
};

#endif /*DS_H*/