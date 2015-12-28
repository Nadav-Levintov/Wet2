#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

template<class T, class C>
class avlTree;

static int max(int a, int b) {
	return a > b ? a : b;
}
template<class T, class C>
class avlNode {
	T data;
	avlNode<T, C>* left;
	avlNode<T, C>* right;
	avlNode<T, C>* parent;
	int height;
	friend class avlTree<T, C>;
public:
	avlNode() :
		data() {
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 0;
	}
	avlNode(T& t) :
		data(t) {
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 0;
	}
	/*
	 This returns the data stored in the node.
	 return:
	 T data.
	 */
	T& getData();
	~avlNode() {
	}
	/*
	 This sets the Parent of the node.
	 Param:
	 p - new parent.
	 */
	void setParent(avlNode<T, C>* p);
	/*
	 This sets the left son of the node.
	 Param:
	 l - new left son.
	 */
	void setLeft(avlNode<T, C>* l);
	/*
	 This sets the right son of the node.
	 Param:
	 r - new right son.
	 */
	void setRight(avlNode<T, C>* r);
	/*
	 This sets the data of the node.
	 Param:
	 d - new data.
	 */
	void setData(T& d);
	/*
	 This returns the left son of the node.
	 return:
	 avlNode<T, C>* of the son.
	 */
	avlNode<T, C>* getLeft();
	/*
	 This returns the right son of the node.
	 return:
	 avlNode<T, C>* of the son.
	 */
	avlNode<T, C>* getRight();
	/*
	 This returns the parent of the node.
	 return:
	 avlNode<T, C>* of the parent.
	 */
	avlNode<T, C>* getParent();
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

};

/*Node Functions*/
template<class T, class C>
T& avlNode<T, C>::getData() {
	return data;
}
template<class T, class C>
void avlNode<T, C>::setParent(avlNode<T, C> * p) {
	parent = p;
}
template<class T, class C>
void avlNode<T, C>::setLeft(avlNode<T, C> * l) {
	left = l;
}
template<class T, class C>
void avlNode<T, C>::setRight(avlNode<T, C> * r) {
	right = r;
}
template<class T, class C>
void avlNode<T, C>::setData(T& d) {
	data = d;
}
template<class T, class C>
avlNode<T, C>* avlNode<T, C>::getLeft() {
	return left;
}
template<class T, class C>
avlNode<T, C>* avlNode<T, C>::getRight() {
	return right;
}
template<class T, class C>
avlNode<T, C>* avlNode<T, C>::getParent() {
	return parent;
}
template<class T, class C>
int avlNode<T, C>::getHeight() {
	return height;
}
template<class T, class C>
int avlNode<T, C>::updateHeight() {
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
void avlNode<T, C>::setHeight(int h) {
	height = h;
}

template<class T, class C>
class avlTree {
	avlNode<T, C>* root;
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
	avlNode<T, C>* findAux(T& item, avlNode<T, C>* node);
	/*
	 This function locates the parent node of the item that would be inserted to the Tree using recursion and the C function.
	 param:
	 item - The item to search for.
	 node - The current node in the tree.
	 return:
	 node - The one node above (Would be parent) of the new node that would be inserted to the tree.
	 NULL - if item was not found.
	 */
	avlNode<T, C>* insertAux(T& item, avlNode<T, C>* node);
	/*
	 This function is used to decide of two items are equal using the compare function.
	 param:
	 a - The first item.
	 b - The second item.
	 return:
	 true - if they are equal.
	 false - if they are not.
	 */
	bool isEqual(avlNode<T, C>* a, avlNode<T, C>* b);
	/*
	 This function prints the tree to the console - IN-ORDER
	 param:
	 root - The current node in the tree.
	 */
	void printAux(avlNode<T, C>* root);
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
	void insertRebalance(avlNode<T, C> * parent, avlNode<T, C> * node);
	/*
	 This function does a LL roll as seen in class.
	 param:
	 node - The current node in the tree.
	 return:
	 Status.
	 */
	void rollLL(avlNode<T, C>* node);
	/*
	 This function does a RR roll as seen in class.
	 param:
	 node - The current node in the tree.
	 return:
	 Status.
	 */
	void rollRR(avlNode<T, C>* node);
	/*
	This function clears the tree recursvly
	return:
	*/
	void clearAux(avlNode<T, C>* node);
	/*
	This function finds and removes the node with the wanted item from the tree.
	return:
	*/
	bool removeAux(avlNode<T, C>* node, T& item);
	void removeHelper(avlNode<T, C>* node);
	int height(avlNode<T, C>* node);
	void reBalance(avlNode<T, C>* node);
	int getBalanceFactor(avlNode<T, C>* node);
	void rollLR(avlNode<T, C>* node);
	void rollRL(avlNode<T, C>* node);
	void inOrderAUX(T* array, int* i, avlNode<T, C>* node);
	avlNode<T, C>* completeTree(int newHeight, avlNode<T, C>* parent);
	void removeLeaves(avlNode<T, C>* node, int *numToRemove);
	void inOrderInsertAux(avlNode<T, C>* node, T* array, int* index);
	int powInt(int x, int p);
public:
	void inOrderInsert(T* array, int* index);
	avlTree() {
		root = NULL;
		comparer = C();
		size = 0;
	}
	avlNode<T, C>* getRoot();
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
	avlNode<T, C>* find(T& item);
	/*
	 This function inserts the item to the Tree and adjust it in order to make sure that the tree
	 is balanced.
	 param:
	 item - The item to insert.
	 return:
	 Status.
	 */
	bool insert(T& item);
	void buildEmpty(int newSize);
	~avlTree();

	/*Used for testing*/
	void print();

	T* inOrder();

	void setSize(int size) {
		this->size = size;
	}

};

/*Tree Function*/

template<class T, class C>
avlNode<T, C>* avlTree<T, C>::findAux(T & item, avlNode<T, C> * node) {
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
avlNode<T, C>* avlTree<T, C>::insertAux(T & item, avlNode<T, C> * node) {
	/* Item is DEFENTLY not in try before this function is called */
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
bool avlTree<T, C>::isEqual(avlNode<T, C>* a, avlNode<T, C>* b) {
	T dataA = a->getData();
	T dataB = b->getData();
	if (!comparer(dataA, dataB) && !comparer(dataB, dataA))
		return true;

	return false;
}
template<class T, class C>
void avlTree<T, C>::printAux(avlNode<T, C> * root) {
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
avlNode<T, C>* avlTree<T, C>::find(T& item) {
	return findAux(item, root); // Call to the recorsion find function with the root of the tree.
}

template<class T, class C>
bool avlTree<T, C>::insert(T & item) {
	if (find(item) != NULL) // Search if item allready exists.
	{
		return false;
	}
	avlNode<T, C>* newNode = new avlNode<T, C>(item);
	if (root == NULL) //Check if Tree it empty, if it is insert to the root.
	{
		root = newNode;
		size++;
		return true;
	}
	else // tree not empty
	{
		avlNode<T, C>* parentNode = insertAux(item, root); // Find the would be parent node.
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
void avlTree<T, C>::buildEmpty(int newSize) {
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
void avlTree<T, C>::insertRebalance(avlNode<T, C> * parent,
	avlNode<T, C> * node) {
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
void avlTree<T, C>::rollRR(avlNode<T, C>* node) {
	assert(node != NULL);
	avlNode<T, C>* oldRight = node->getRight();
	avlNode<T, C>* parent = node->getParent();
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
	oldRight->setHeight(
		1
		+ max(height(oldRight->getRight()),
			height(oldRight->getLeft())));
}
template<class T, class C>
void avlTree<T, C>::rollLL(avlNode<T, C> * node) {
	assert(node != NULL);
	avlNode<T, C>* oldLeft = node->getLeft();
	avlNode<T, C>* parent = node->getParent();
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
	oldLeft->setHeight(
		1 + max(height(oldLeft->getRight()), height(oldLeft->getLeft())));
}

template<class T, class C>
void avlTree<T, C>::print() {
	printAux(root);
}
template<class T, class C>
void avlTree<T, C>::inOrderAUX(T * array, int* i, avlNode<T, C> * node) {
	if (!node)
	{
		return;
	}
	if (node->getLeft())
		inOrderAUX(array, i, node->getLeft());

	array[*i] = node->getData();
	*i = *i + 1;
	if (node->getRight())
		inOrderAUX(array, i, node->getRight());

}
template<class T, class C>
inline avlNode<T, C>* avlTree<T, C>::completeTree(int newHeight, avlNode<T, C>* parent) {
	if (newHeight < 0) {
		return NULL;
	}
	avlNode<T, C>* head = new avlNode<T, C>();
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
inline void avlTree<T, C>::removeLeaves(avlNode<T, C>* node, int *numToRemove) {
	if (!node || *numToRemove < 1) {
		return;
	}
	removeLeaves(node->getRight(), numToRemove);
	if (!(node->getLeft()) && !(node->getRight())) {
		avlNode<T, C>* parent = node->getParent();
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
inline void avlTree<T, C>::inOrderInsertAux(avlNode<T, C>* node, T * array,
	int * index) {
	if (!node) {
		return;
	}
	inOrderInsertAux(node->getLeft(), array, index);
	node->setData(array[*index]);
	(*index)++;
	inOrderInsertAux(node->getRight(), array, index);

}
template<class T, class C>
inline void avlTree<T, C>::inOrderInsert(T * array, int * index) {
	inOrderInsertAux(root, array, index);
}
template<class T, class C>

T * avlTree<T, C>::inOrder() {
	T* array = new T[size];
	int i = 0;
	int* ptr = &i;
	inOrderAUX(array, ptr, root);
	return array;

}

/* Michael's function*/

template<class T, class C>
bool avlTree<T, C>::remove(T& item) {
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
bool avlTree<T, C>::removeAux(avlNode<T, C>* node, T& item) {
	if (!node) {
		return false;
	}
	if (comparer(node->getData(), item)) {
		if (removeAux(node->getRight(), item)) {
			node->setHeight(
				1 + max(height(node->getLeft()), height(node->getRight())));
			reBalance(node);
			return true;
		}
		return false;
	}
	if (comparer(item, node->getData())) {
		if (removeAux(node->getLeft(), item)) {
			node->setHeight(
				1 + max(height(node->getLeft()), height(node->getRight())));
			reBalance(node);
			return true;
		}
		return false;
	}
	/* if we found the node in the tree: */
	/* if the node has two sons */
	if (node->getLeft() && node->getRight()) {
		/* finding the next node in-order */
		avlNode<T, C>* ptr = node->getRight();
		while (ptr->getLeft()) {
			ptr = ptr->getLeft();
		}
		/** switching between node and ptr */
		node->setData(ptr->getData());
		avlNode<T, C>* tmp = ptr->getParent();
		removeHelper(ptr);
		while (tmp && tmp != node) {
			tmp->setHeight(
				1 + max(height(tmp->getLeft()), height(tmp->getRight())));
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
void avlTree<T, C>::removeHelper(avlNode<T, C>* node) {
	/* if the node is a leaf */
	if (!node->getRight() && !node->getLeft()) {
		/* if the only node is the root */
		if (node == root) {
			root = NULL;
		}
		/* otherwise */
		else if (node->parent->getRight() == node) {
			node->parent->setRight(NULL);
		}
		else {
			node->parent->setLeft(NULL);
		}
		/* if the node has only one son */
	}
	else {
		avlNode<T, C>* son =
			(node->getRight()) ? node->getRight() : node->getLeft();
		if (node == root) {
			root = son;
			son->setParent(NULL);
		}
		else {
			if (node->parent->getRight() == node) {
				node->parent->setRight(son);
			}
			else {
				node->parent->setLeft(son);
			}
			son->setParent(node->getParent());
		}
	}
	delete node;
}

template<class T, class C>
void avlTree<T, C>::reBalance(avlNode<T, C>* node) {
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
int avlTree<T, C>::getBalanceFactor(avlNode<T, C>* node) {
	if (!node) {
		return 0;
	}
	return height(node->getLeft()) - height(node->getRight());
}

template<class T, class C>
int avlTree<T, C>::height(avlNode<T, C>* node) {
	if (!node) {
		return -1;
	}
	return node->getHeight();
}
/*
 avlTree<T,C>::avlTree<T,C>(C comparer) :
 comparer(comparer), size(0), root(NULL) {
 }
 */
template<class T, class C>
avlTree<T, C>::~avlTree() {
	this->clear();
}
template<class T, class C>
void avlTree<T, C>::rollLR(avlNode<T, C>* node) {
	rollRR(node->getLeft());
	rollLL(node);

}

template<class T, class C>
void avlTree<T, C>::rollRL(avlNode<T, C>* node) {
	rollLL(node->getRight());
	rollRR(node);
}

template<class T, class C>
bool avlTree<T, C>::isEmpty() {
	return !root;
}

template<class T, class C>
int avlTree<T, C>::getSize() {
	return size;
}

template<class T, class C>
void avlTree<T, C>::clear() {
	if (!root) {
		return;
	}
	clearAux(root);
	this->setSize(0);
	root = NULL;
}
template<class T, class C>
void avlTree<T, C>::clearAux(avlNode<T, C>* node) {
	if (!node) {
		return;
	}
	clearAux(node->getLeft());
	clearAux(node->getRight());
	delete node;
}

template<class T, class C>
avlNode<T, C>* avlTree<T, C>::getRoot() {
	return root;
}

template<class T, class C>
int avlTree<T, C>::powInt(int x, int p) {
	if (p == 0)
		return 1;
	if (p == 1)
		return x;
	return x * powInt(x, p - 1);
}

#endif /*AVL_TREE*/
