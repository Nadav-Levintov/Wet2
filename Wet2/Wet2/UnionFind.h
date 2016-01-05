#ifndef UNIONFIND_H_
#define UNIONFIND_H_
#include <cassert>
#define ROOT -1
#define NO_NAME -1

class UnionFind {
	int size;
	int* parent;
	int* numOfEelements;
	int* groupName;
public:
	UnionFind(int n);
	~UnionFind();
	int Find(int element);
	void Union(int set1, int set2);
	int* getNumOfEelements() const;
	void setNumOfEelements(int* numOfEelements);
	int* getParent() const;
	void setParent(int* parent);
	int getSize() const;
	void setSize(int size);
	int getNumOfGroups();
	int* getGroupName() const;
	void setGroupName(int* groupName);
};

#endif /* UNIONFIND_H_ */
