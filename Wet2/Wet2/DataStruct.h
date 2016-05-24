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

#define EMPTY -1

using std::exception;

class DataStruct
{
	int numOfGroups;
	int* maxArray;
	int* maxIdArray;
	int* strengthHistogram;
	UnionFind groups;
	avlTree<Troll, TrollComparer> TrollTree;
	HashTable<Troll, TrollComparer, TrollIDKey> ht;


public:
	class InvalidInput :public exception {};
	class Failure :public exception {};

	DataStruct(int numOfFacu);
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
