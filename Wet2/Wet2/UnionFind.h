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

UnionFind::UnionFind(int n) :
		size(n) {
	assert(n > 2);
	this->parent = new int[n];
	this->numOfEelements = new int[n];
	this->groupName = new int[n];
	for (int i = 0; i < n; i++) {
		parent[i] = ROOT;
		numOfEelements[i] = 1;
		groupName[i] = i;
	}
}

UnionFind::~UnionFind() {
	delete[] parent;
	delete[] numOfEelements;
	delete[] groupName;
}

int UnionFind::Find(int element) {
	int root = element;
	while (this->parent[root] != ROOT) {
		root = this->parent[root];
	}
	/* shrinking paths */
	int ptr = element;
	while (this->parent[ptr] != ROOT) {
		int tmp = this->parent[ptr];
		this->parent[ptr] = root;
		ptr = tmp;
	}
	return groupName[root];
}

void UnionFind::Union(int set1, int set2) {
	int small = (numOfEelements[set1] < numOfEelements[set2]) ? set1 : set2;
	int large = (small == set1) ? set2 : set1;
	parent[small] = large;
	numOfEelements[large] += numOfEelements[small];
	numOfEelements[small] = 0;
	groupName[small] = NO_NAME;
	groupName[large] = set1;
}

int* UnionFind::getNumOfEelements() const {
	return numOfEelements;
}

void UnionFind::setNumOfEelements(int* numOfEelements) {
	this->numOfEelements = numOfEelements;
}

int* UnionFind::getParent() const {
	return parent;
}

void UnionFind::setParent(int* parent) {
	this->parent = parent;
}

int UnionFind::getSize() const {
	return size;
}

void UnionFind::setSize(int size) {
	this->size = size;
}

int* UnionFind::getGroupName() const {
	return groupName;
}

void UnionFind::setGroupName(int* groupName) {
	this->groupName = groupName;
}

int UnionFind::getNumOfGroups() {
	int counter1 = 0, counter2 = 0;
	for (int i = 0; i < size; i++) {
		if (parent[i] == ROOT) {
			counter1++;
		}
		if (groupName[i] != NO_NAME) {
			counter2++;
		}
	}
	assert(counter1 == counter2);
	return counter1;
}

#endif /* UNIONFIND_H_ */
