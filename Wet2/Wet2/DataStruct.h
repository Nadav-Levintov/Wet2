#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Troll.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "AVLTree.h"
#include "AVLRankTree.h"

#define EMPTY -1
#define NOTROLL 0

using std::exception;

class intComparer {
public:
	intComparer() {
	}
	~intComparer() {
	}
	bool operator()(int a, int b) {
		return a < b;
	}
};

class DataStruct
{
	int numOfGroups;
	int* maxArray;
	int* maxIdArray;
	UnionFind groups;
	avlTree<Troll, TrollComparer> TrollTree;
	avlTree<Troll, TrollStrengthComparer> TrollStrengthTree;
	rankTree<int, intComparer> strengthTree;
	HashTable<Troll, TrollComparer, TrollIDKey> ht;

	static Troll* mergeTrollsArray(Troll* array1, Troll* array2, int num);
	static void buildStrengthHistogram(Troll* strengthArray, int** histogramData,int** histogramBase, int numOfTrolls, int* numOfStrengths);
public:
	class InvalidInput :public exception {};
	class Failure :public exception {};

	DataStruct(int numOfTeams);
	~DataStruct();
	void AddTroll(int TrollID, int strength);
	void AssignTroll(int TrollID, int team);
	void JoinGroups(int team1, int team2);
	void GetGroup(int TrollID, int *group);
	/*void UnifyFacultiesByTrolls(int TrollID1, int TrollID2);*/
	void TeamUpgrade(int team, int factor);
	void GetStrongestTroll(int groupID, int* Troll);
	void GetNumOfTrollsInRange(int fromStrength, int toStrength, int* num);
};

#endif /*DS_H*/
