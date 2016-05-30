#ifndef AVLRANKTREE_H
#define AVLRANKTREE_H

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#define NOTFOUND -1;


template<class T, class C>
class rankTree;
/*
static int max(int a, int b) {
	return a > b ? a : b;
}*/
template<class T, class C>
class rankNode {
	T data;
	rankNode<T, C>* left;
	rankNode<T, C>* right;
	rankNode<T, C>* parent;
	int height;
	int subTreeData;
	int currentData;
	
	friend class avlTree<T, C>;
public:
	rankNode() :
		data() {
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 0;
		subTreeData = 1;
		currentData = 1;
	}
	rankNode(T& t) :
		data(t) {
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 0;
		subTreeData = 1;
		currentData = 1;
	}
	/*
	This returns the data stored in the node.
	return:
	T data.
	*/
	T& getData();
	~rankNode() {
	}
	/*
	This sets the Parent of the node.
	Param:
	p - new parent.
	*/
	void setParent(rankNode<T, C>* p);
	/*
	This sets the left son of the node.
	Param:
	l - new left son.
	*/
	void setLeft(rankNode<T, C>* l);
	/*
	This sets the right son of the node.
	Param:
	r - new right son.
	*/
	void setRight(rankNode<T, C>* r);
	/*
	This sets the data of the node.
	Param:
	d - new data.
	*/
	void setData(T& d);
	/*
	This returns the left son of the node.
	return:
	rankNode<T, C>* of the son.
	*/
	rankNode<T, C>* getLeft();
	/*
	This returns the right son of the node.
	return:
	rankNode<T, C>* of the son.
	*/
	rankNode<T, C>* getRight();
	/*
	This returns the parent of the node.
	return:
	rankNode<T, C>* of the parent.
	*/
	rankNode<T, C>* getParent();
	/*
	This returns the height of the node.
	return:
	int - height of the node.
	*/
	int getHeight();
	/*
	Update this, and evrey node below it, height and returns it.
	RunTime Complex. = O(n) where n is num of nodes in the sub tree.
	return:
	int - height of the node.
	*/
	int updateHeight();
	/*
	This sets the height of the node.
	Param:
	h - new height.
	*/
	void setHeight(int h);
	/*
	This  returns the size of the sub Tree.
	Param:
	*/
	int getsubTreeData();
	/*
	This  updates the size of the sub Tree.
	Param:
	*/
	void updatesubTreeData();
	void setCurrentData(int n);
	int getCurrentData();
	/*
	This  updates all the size of the sub Tree for all nodes.
	Param:
	*/
	int updateAllsubTreeData();
	void setsubTreeData(int n);

};

/*Node Functions*/
template<class T, class C>
T& rankNode<T, C>::getData() {
	return data;
}
template<class T, class C>
void rankNode<T, C>::setParent(rankNode<T, C> * p) {
	parent = p;
}
template<class T, class C>
void rankNode<T, C>::setLeft(rankNode<T, C> * l) {
	left = l;
}
template<class T, class C>
void rankNode<T, C>::setRight(rankNode<T, C> * r) {
	right = r;
}
template<class T, class C>
void rankNode<T, C>::setData(T& d) {
	data = d;
}
template<class T, class C>
rankNode<T, C>* rankNode<T, C>::getLeft() {
	return left;
}
template<class T, class C>
rankNode<T, C>* rankNode<T, C>::getRight() {
	return right;
}
template<class T, class C>
rankNode<T, C>* rankNode<T, C>::getParent() {
	return parent;
}
template<class T, class C>
int rankNode<T, C>::getHeight() {
	return height;
}
template<class T, class C>
int rankNode<T, C>::updateHeight() {
	if (!left && !right) // Is this a leaf?
	{
		height = 0; // yes- height is 0.
	}
	else {// not a leaf - height is 1+max height of sons.
		if (!left) // does it have only right son?
		{
			height = 1 + right->updateHeight();
		}
		else if (!right) // does it have only left son?
		{
			height = 1 + left->updateHeight();
		}
		else // it has both sons.
		{
			height = 1 + max(left->updateHeight(), right->updateHeight());
		}
	}

	return height;
}
template<class T, class C>
void rankNode<T, C>::setHeight(int h) {
	height = h;
}

template<class T, class C>
 int rankNode<T, C>::getsubTreeData()
{
	return subTreeData;
}

 template<class T, class C>
  void rankNode<T, C>::updatesubTreeData()
 {
	 int leftS = (getLeft() == NULL) ? 0 : getLeft()->getsubTreeData();
		 int rightS = (getRight() == NULL) ? 0 : getRight()->getsubTreeData();
		 subTreeData = currentData + leftS + rightS;
 }

  template<class T, class C>
  inline void rankNode<T, C>::setCurrentData(int n)
  {
	  currentData = n;
	  updatesubTreeData();
  }

  template<class T, class C>
  inline int rankNode<T, C>::getCurrentData()
  {
	  return currentData;
  }



  template<class T, class C>
  int rankNode<T, C>::updateAllsubTreeData()
  {
	  int leftS = getLeft() ? getLeft()->updateAllsubTreeData() : 0;
	  int rightS = getRight() ? getRight()->updateAllsubTreeData() : 0;
	  subTreeData = currentData + leftS + rightS;
	  return subTreeData;
  }

  template<class T, class C>
void rankNode<T, C>::setsubTreeData(int n)
  {
	  subTreeData = n;
  }



template<class T, class C>
class rankTree {
	rankNode<T, C>* root;
	int size;
	C comparer; // function object, returns True if first parm is SMALLER then second parm.

private:
	/*
	This function locates the item in the Tree using recursion and the C function.
	param:
	item - The item to search for.
	node - The current node in the tree.
	return:
	node - The node that holds the wanted item in the tree.
	NULL - if item was not found.
	*/
	rankNode<T, C>* findAux(T& item, rankNode<T, C>* node);
	/*
	This function locates the parent node of the item that would be inserted to the Tree using recursion and the C function.
	param:
	item - The item to search for.
	node - The current node in the tree.
	return:
	node - The one node above (Would be parent) of the new node that would be inserted to the tree.
	NULL - if item was not found.
	*/
	rankNode<T, C>* insertAux(T& item, rankNode<T, C>* node);
	/*
	This function is used to decide of two items are equal using the compare function.
	param:
	a - The first item.
	b - The second item.
	return:
	true - if they are equal.
	false - if they are not.
	*/
	bool isEqual(rankNode<T, C>* a, rankNode<T, C>* b);
	/*
	This function prints the tree to the console - IN-ORDER
	param:
	root - The current node in the tree.
	*/
	void printAux(rankNode<T, C>* root);
	/*
	This function balances the tree after a new item is inserted.
	Using recorsion this function travels up the search path and checks each node if it is
	not balanced, when it finds the unbalanced node it corrects is using a roll.
	param:
	parent - The parent of the new node - need to check if not balanced.
	node - The current node in the tree.
	return:
	status.
	*/
	void insertRebalance(rankNode<T, C> * parent, rankNode<T, C> * node);
	/*
	This function does a LL roll as seen in class.
	param:
	node - The current node in the tree.
	return:
	Status.
	*/
	void rollLL(rankNode<T, C>* node);
	/*
	This function does a RR roll as seen in class.
	param:
	node - The current node in the tree.
	return:
	Status.
	*/
	void rollRR(rankNode<T, C>* node);
	/*
	This function clears the tree recursvly
	return:
	*/
	void clearAux(rankNode<T, C>* node);
	/*
	This function finds and removes the node with the wanted item from the tree.
	return:
	*/
	bool removeAux(rankNode<T, C>* node, T& item);
	void removeHelper(rankNode<T, C>* node);
	int height(rankNode<T, C>* node);
	void reBalance(rankNode<T, C>* node);
	int getBalanceFactor(rankNode<T, C>* node);
	void rollLR(rankNode<T, C>* node);
	void rollRL(rankNode<T, C>* node);
	void inOrderAUX(T* array,int* extraData, int* i, rankNode<T, C>* node);
	rankNode<T, C>* completeTree(int newHeight, rankNode<T, C>* parent);
	void removeLeaves(rankNode<T, C>* node, int *numToRemove);
	void inOrderInsertAux(rankNode<T, C>* node, T* array,int* extraData, int* index);
	int powInt(int x, int p);
	int rankAux(T& item, rankNode<T, C>* node);
	void updateRankDataOnPathAux(rankNode<T, C>* node, T& item);
public:
	void inOrderInsert(T* array, int* extraData, int* index);
	rankTree() {
		root = NULL;
		comparer = C();
		size = 0;
	}
	rankNode<T, C>* getRoot();
	void clear();
	int getSize();
	bool isEmpty();
	bool remove(T& item);

	/*
	This function locates the item in the Tree using recursion and the C function.
	param:
	item - The item to search for.
	return:
	node - The node that holds the wanted item in the tree.
	NULL - if item was not found.
	*/
	rankNode<T, C>* find(T& item);
	/*
	This function inserts the item to the Tree and adjust it in order to make sure that the tree
	is balanced.
	param:
	item - The item to insert.
	return:
	Status.
	*/
	void updateRankDataOnPath(T& item);
	
	bool insert(T& item);
	void buildEmpty(int newSize);
	
	int rank(T& item);
	~rankTree();

	/*Used for testing*/
	void print();

	T* inOrder(int* extraDataPtr);

	void setSize(int size) {
		this->size = size;
	}
	

};

/*Tree Function*/

template<class T, class C>
rankNode<T, C>* rankTree<T, C>::findAux(T & item, rankNode<T, C> * node) {
	if (node == NULL)
		return NULL; //Did not find the item.
	T data = node->getData();
	if (comparer(item, data)) // Item is smaller then current node? keep searching left.
		return findAux(item, node->getLeft());
	if (comparer(data, item)) // Current node is smaller then item? keep searching right.
		return findAux(item, node->getRight());

	return node; //found item.
}

template<class T, class C>
rankNode<T, C>* rankTree<T, C>::insertAux(T & item, rankNode<T, C> * node) {
	/* Item is DEFENTLY not in tree before this function is called */
	/* Item would be in this Sub tree */
	node->setsubTreeData(1 + node->getsubTreeData());
	T data = node->getData();
	if (comparer(item, data)) // Item is smaller then current node?
	{
		if (node->getLeft() == NULL) // There is no nodes to the left? found the insert location.
			return node;
		else
			return insertAux(item, node->getLeft()); // keep searching left.
	}
	else // current node is bigger then item.
	{
		if (node->getRight() == NULL) // There is no nodes to the right? found the insert location.
			return node;
		else
			return insertAux(item, node->getRight()); // keep searching right.
	}
}
template<class T, class C>
bool rankTree<T, C>::isEqual(rankNode<T, C>* a, rankNode<T, C>* b) {
	T dataA = a->getData();
	T dataB = b->getData();
	if (!comparer(dataA, dataB) && !comparer(dataB, dataA))
		return true;

	return false;
}
template<class T, class C>
void rankTree<T, C>::printAux(rankNode<T, C> * root) {
	if (root != NULL) {
		std::cout << "Left: ";
		printAux(root->getLeft());
		std::cout << std::endl;
		std::cout << "Value: ";
		std::cout << root->getData() << " height: " << root->getHeight() << std::endl;
		std::cout << std::endl;
		std::cout << "Right: ";
		printAux(root->getRight());

		std::cout << "up! ";
	}
	else
		std::cout << "NIL" << std::endl;
}
template<class T, class C>
rankNode<T, C>* rankTree<T, C>::find(T& item) {
	return findAux(item, root); // Call to the recorsion find function with the root of the tree.
}

template<class T, class C>
void rankTree<T, C>::updateRankDataOnPath(T & item)
{
	updateRankDataOnPathAux(root, item);
}

template<class T, class C>
void rankTree<T, C>::updateRankDataOnPathAux(rankNode<T, C>* node,T & item)
{
	if (!node)
		return;
	if (comparer(node->getData(), item))
		{	
			updateRankDataOnPathAux(node->getRight(), item);
		}
	if (comparer(item, node->getData())) 
		{
			updateRankDataOnPathAux(node->getLeft(), item);
		}
		node->updatesubTreeData();

}

template<class T, class C>
bool rankTree<T, C>::insert(T & item) {
	if (find(item) != NULL) // Search if item allready exists.
	{
		return false;
	}
	rankNode<T, C>* newNode = new rankNode<T, C>(item);
	if (root == NULL) //Check if Tree it empty, if it is insert to the root.
	{
		root = newNode;
		size++;
		return true;
	}
	else // tree not empty
	{
		rankNode<T, C>* parentNode = insertAux(item, root); // Find the would be parent node.
		assert(parentNode != NULL);
		newNode->setParent(parentNode); // set the parent node as the parent of the new node.
		T& parentData = parentNode->getData();
		if (comparer(item, parentData)) //Check if smaller then parent
		{

			parentNode->setLeft(newNode); // Enter as left son and rebalance.
			size++;
			insertRebalance(parentNode, parentNode->getLeft());
		}
		else //item not smaller then parent, enter right and balance.
		{
			parentNode->setRight(newNode);
			size++;
			insertRebalance(parentNode, parentNode->getRight());
		}
	}
	return true;
}
template<class T, class C>
void rankTree<T, C>::buildEmpty(int newSize) {
	if (newSize < 1)
	{
		return;
	}
	int newHeight = 0;
	while ((powInt(2, newHeight + 1) - 1) < newSize) {
		newHeight++;
	}
	root = completeTree(newHeight, NULL);
	int numToRemove = (powInt(2, newHeight + 1) - 1) - newSize;
	removeLeaves(root, &numToRemove);
	setSize(newSize);
	root->updateHeight();
	
}
template<class T, class C>
void rankTree<T, C>::insertRebalance(rankNode<T, C> * parent,
	rankNode<T, C> * node) {
	if (parent == NULL || node == NULL) // not in the tree - evrey thing is balanced.
	{
		return;
	}

	int parentH = parent->getHeight();
	int nodeH = node->getHeight();
	if (parentH >= nodeH + 1) // is the height of the parent is updated?
	{
		return;
	}
	else // it is not.
	{
		parent->setHeight(nodeH + 1);

		int balanceFactor = getBalanceFactor(parent);
		if (balanceFactor == 2 || balanceFactor == -2) {
			reBalance(parent);
			return;
		}
		else {
			insertRebalance(parent->getParent(), parent); // This junction is balanced, check upwords.
		}
	}
}

template<class T, class C>
void rankTree<T, C>::rollRR(rankNode<T, C>* node) {
	assert(node != NULL);
	rankNode<T, C>* oldRight = node->getRight();
	rankNode<T, C>* parent = node->getParent();
	oldRight->setParent(parent);
	if (parent) {
		if (comparer(parent->getData(), oldRight->getData()))
			parent->setRight(oldRight);
		else
			parent->setLeft(oldRight);
	}
	else
		root = oldRight;

	node->setRight(oldRight->getLeft());

	if (oldRight->getLeft())
		oldRight->getLeft()->setParent(node);
	oldRight->setLeft(node);
	node->setParent(oldRight);

	node->setHeight(
		1 + max(height(node->getRight()), height(node->getLeft())));
	node->updatesubTreeData();
	oldRight->setHeight(
		1
		+ max(height(oldRight->getRight()),
			height(oldRight->getLeft())));
	oldRight->updateAllsubTreeData();

}
template<class T, class C>
void rankTree<T, C>::rollLL(rankNode<T, C> * node) {
	assert(node != NULL);
	rankNode<T, C>* oldLeft = node->getLeft();
	rankNode<T, C>* parent = node->getParent();
	oldLeft->setParent(parent);
	if (parent) {
		if (comparer(oldLeft->getData(), parent->getData()))
			parent->setLeft(oldLeft);
		else
			parent->setRight(oldLeft);
	}
	else
		root = oldLeft;
	node->setLeft(oldLeft->getRight());
	if (oldLeft->getRight())
		oldLeft->getRight()->setParent(node);
	oldLeft->setRight(node);
	node->setParent(oldLeft);

	node->setHeight(1 + max(height(node->getRight()), height(node->getLeft())));
	node->updatesubTreeData();
	oldLeft->setHeight(
		1 + max(height(oldLeft->getRight()), height(oldLeft->getLeft())));
	oldLeft->updatesubTreeData();
}

template<class T, class C>
void rankTree<T, C>::print() {
	printAux(root);
}
template<class T, class C>
void rankTree<T, C>::inOrderAUX(T * array,int* extraData, int* i, rankNode<T, C> * node) {
	if (!node)
	{
		return;
	}
	if (node->getLeft())
		inOrderAUX(array, extraData, i, node->getLeft());

	array[*i] = node->getData();
	extraData[*i] = node->getCurrentData();
	*i = *i + 1;
	if (node->getRight())
		inOrderAUX(array, extraData, i,  node->getRight());

}
template<class T, class C>
inline rankNode<T, C>* rankTree<T, C>::completeTree(int newHeight, rankNode<T, C>* parent) {
	if (newHeight < 0) {
		return NULL;
	}
	rankNode<T, C>* head = new rankNode<T, C>();
	if (!head) {
		return NULL;
	}
	head->setParent(parent);
	head->setHeight(newHeight);
	head->setLeft(completeTree(newHeight - 1, head));
	head->setRight(completeTree(newHeight - 1, head));
	return head;
}
template<class T, class C>
inline void rankTree<T, C>::removeLeaves(rankNode<T, C>* node, int *numToRemove) {
	if (!node || *numToRemove < 1) {
		return;
	}
	removeLeaves(node->getRight(), numToRemove);
	if (!(node->getLeft()) && !(node->getRight())) {
		rankNode<T, C>* parent = node->getParent();
		if (parent->getLeft() == node) {
			parent->setLeft(NULL);
		}
		else {
			parent->setRight(NULL);
		}
		delete node;
		(*numToRemove)--;
		return;
	}
	removeLeaves(node->getLeft(), numToRemove);
}
template<class T, class C>
inline void rankTree<T, C>::inOrderInsertAux(rankNode<T, C>* node, T * array, int* extraData,
	int * index) {
	if (!node) {
		return;
	}
	inOrderInsertAux(node->getLeft(), array,extraData, index);
	node->setData(array[*index]);
	node->setCurrentData(extraData[*index]);
	(*index)++;
	inOrderInsertAux(node->getRight(), array, extraData, index);

}
template<class T, class C>
inline void rankTree<T, C>::inOrderInsert(T * array, int* extraData, int * index) {
	inOrderInsertAux(root, array,extraData, index);
	root->updateAllsubTreeData();
}
template<class T, class C>
T * rankTree<T, C>::inOrder(int* extraDataPtr) {
	T* array = new T[size];
	
	int i = 0;
	int* ptr = &i;
	inOrderAUX(array, extraDataPtr, ptr, root);
	
	return array;

}

/* Michael's function*/

template<class T, class C>
bool rankTree<T, C>::remove(T& item) {
	if (!root) {
		return false;
	}
	if (removeAux(root, item)) {		
		this->setSize(this->getSize() - 1);
		return true;
	}
	return false;
}
template<class T, class C>
bool rankTree<T, C>::removeAux(rankNode<T, C>* node, T& item) {
	if (!node) {
		return false;
	}
	if (comparer(node->getData(), item)) {
		if (removeAux(node->getRight(), item)) {
			node->setHeight(
				1 + max(height(node->getLeft()), height(node->getRight())));
			node->updatesubTreeData();
			reBalance(node);
			return true;
		}
		return false;
	}
	if (comparer(item, node->getData())) {
		if (removeAux(node->getLeft(), item)) {
			node->setHeight(
				1 + max(height(node->getLeft()), height(node->getRight())));
			node->updatesubTreeData();
			reBalance(node);
			return true;
		}
		return false;
	}
	/* if we found the node in the tree: */
	/* if the node has two sons */
	if (node->getLeft() && node->getRight()) {
		/* finding the next node in-order */
		rankNode<T, C>* ptr = node->getRight();
		while (ptr->getLeft()) {
			ptr = ptr->getLeft();
		}
		/** switching between node and ptr */
		node->setData(ptr->getData());
		rankNode<T, C>* tmp = ptr->getParent();
		removeHelper(ptr);
		while (tmp && tmp != node) {
			tmp->setHeight(
				1 + max(height(tmp->getLeft()), height(tmp->getRight())));
			tmp->updatesubTreeData();
			reBalance(tmp);
			tmp = tmp->getParent();
		}
	}
	else {
		removeHelper(node);
	}
	return true;
}
template<class T, class C>
void rankTree<T, C>::removeHelper(rankNode<T, C>* node) {
	/* if the node is a leaf */
	if (!node->getRight() && !node->getLeft()) {
		/* if the only node is the root */
		if (node == root) {
			root = NULL;
		}
		/* otherwise */
		else if (node->getParent()->getRight() == node) {
			node->getParent()->setRight(NULL);
			node->getParent()->updatesubTreeData();
		}
		else {
			node->getParent()->setLeft(NULL);
			node->getParent()->updatesubTreeData();
		}
		/* if the node has only one son */
	}
	else {
		rankNode<T, C>* son =
			(node->getRight()) ? node->getRight() : node->getLeft();
		if (node == root) {
			root = son;
			son->setParent(NULL);
		}
		else {
			if (node->getParent()->getRight() == node) {
				node->getParent()->setRight(son);
			}
			else {
				node->getParent()->setLeft(son);
			}
			son->setParent(node->getParent());
		}
		son->updatesubTreeData();
	}
	delete node;
}

template<class T, class C>
void rankTree<T, C>::reBalance(rankNode<T, C>* node) {
	int balanceFactorParent = getBalanceFactor(node);
	int balanceFactorLeft = getBalanceFactor(node->getLeft());
	int balanceFactorRight = getBalanceFactor(node->getRight());
	if (balanceFactorParent == 2) {
		if (balanceFactorLeft == -1) {
			rollLR(node);
		}
		else if (balanceFactorLeft >= 0) {
			rollLL(node);
		}
	}
	else if (balanceFactorParent == -2) {
		if (balanceFactorRight == 1) {
			rollRL(node);
		}
		else if (balanceFactorRight <= 0) {
			rollRR(node);
		}
	}
}

template<class T, class C>
int rankTree<T, C>::getBalanceFactor(rankNode<T, C>* node) {
	if (!node) {
		return 0;
	}
	return height(node->getLeft()) - height(node->getRight());
}

template<class T, class C>
int rankTree<T, C>::height(rankNode<T, C>* node) {
	if (!node) {
		return -1;
	}
	return node->getHeight();
}
template<class T, class C>
int rankTree<T, C>::rank(T & item)
{
	if (!find(item))
		return NOTFOUND;
	return rankAux(item,root);
}
/*
rankTree<T,C>::rankTree<T,C>(C comparer) :
comparer(comparer), size(0), root(NULL) {
}
*/
template<class T, class C>
rankTree<T, C>::~rankTree() {
	this->clear();
}
template<class T, class C>
void rankTree<T, C>::rollLR(rankNode<T, C>* node) {
	rollRR(node->getLeft());
	rollLL(node);

}

template<class T, class C>
void rankTree<T, C>::rollRL(rankNode<T, C>* node) {
	rollLL(node->getRight());
	rollRR(node);
}

template<class T, class C>
bool rankTree<T, C>::isEmpty() {
	return !root;
}

template<class T, class C>
int rankTree<T, C>::getSize() {
	return size;
}

template<class T, class C>
void rankTree<T, C>::clear() {
	if (!root) {
		return;
	}
	clearAux(root);
	this->setSize(0);
	root = NULL;
}
template<class T, class C>
void rankTree<T, C>::clearAux(rankNode<T, C>* node) {
	if (!node) {
		return;
	}
	clearAux(node->getLeft());
	clearAux(node->getRight());
	delete node;
}

template<class T, class C>
rankNode<T, C>* rankTree<T, C>::getRoot() {
	return root;
}

template<class T, class C>
int rankTree<T, C>::powInt(int x, int p) {
	if (p == 0)
		return 1;
	if (p == 1)
		return x;
	return x * powInt(x, p - 1);
}
template<class T, class C>
int rankTree<T, C>::rankAux(T & item, rankNode<T, C>* node)
{
	if (node == NULL)
		return NOTFOUND; //Did not find the item.
	T data = node->getData();
	if (comparer(item, data)) // Item is smaller then current node? keep searching left.
		return rankAux(item, node->getLeft());
	if (comparer(data, item)) // Current node is smaller then item? keep searching right.
	{
		int leftS = (node->getLeft()) ? node->getLeft()->getsubTreeData() : 0;
		leftS += node->getCurrentData();
		return leftS + rankAux(item, node->getRight());
	}
	int rank = (node->getLeft()) ? node->getLeft()->getsubTreeData() : 0;
	rank += node->getCurrentData();
	return rank; //found item.
}
#endif /*AVLRANKTREE_H*/