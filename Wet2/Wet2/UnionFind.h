#ifndef UNIONFIND_H_
#define UNIONFIND_H_
#include <cassert>
#define ROOT -1

typedef int T;

class UnionFind {
	int size;
	T* parent;
	T* numOfEelements;
	T* groupName;
public:
	UnionFind(int n);
	~UnionFind();
	T& Find(T& element);
	void Union(T& set1, T& set2);
	T* getNumOfEelements() const;
	void setNumOfEelements(T* numOfEelements);
	T* getParent() const;
	void setParent(T* parent);
	int getSize() const;
	void setSize(int size);
};

UnionFind::UnionFind(int n) :
		size(n) {
	assert(n > 2);
	this->parent = new T[n];
	this->numOfEelements = new T[n];
	for (int i = 0; i < n; i++) {
		parent[i] = ROOT;
		numOfEelements[i] = 1;
	}
}

UnionFind::~UnionFind() {
	delete[] parent;
	delete[] numOfEelements;
}

T& UnionFind::Find(T& element) {
	T root = element;
	while (this->parent[root] != ROOT) {
		root = this->parent[root];
	}
	/* shrinking paths */
	T ptr = element;
	while (this->parent[ptr] != ROOT) {
		T tmp = this->parent[ptr];
		this->parent[ptr] = root;
		ptr = tmp;
	}
	return root;
}

void UnionFind::Union(T& set1, T& set2) {

}

T* UnionFind::getNumOfEelements() const {
	return numOfEelements;
}

void UnionFind::setNumOfEelements(T* numOfEelements) {
	this->numOfEelements = numOfEelements;
}

T* UnionFind::getParent() const {
	return parent;
}

void UnionFind::setParent(T* parent) {
	this->parent = parent;
}

int UnionFind::getSize() const {
	return size;
}

void UnionFind::setSize(int size) {
	this->size = size;
}

#endif /* UNIONFIND_H_ */
