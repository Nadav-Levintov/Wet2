#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Student.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "AVLTree.h"

#define EMPTY -1

using std::exception;

class DataStruct
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

	DataStruct(int numOfFacu);
	~DataStruct();
	void AddStudent(int studentID, int average);
	void AssignStudent(int studentID, int studyGroup);
	void JoinFaculties(int studyGroup1, int studyGroup2);
	void GetFaculty(int studentID, int *faculty);
	void UnifyFacultiesByStudents(int studentID1, int studentID2);
	void UpgradeStudyGroup(int studyGroup, int factor);
	void GetSmartestStudent(int facultyID, int* student);
	void GetNumOfStudentsInRange(int fromAvg, int toAvg, int* num);
};

#endif /*DS_H*/
