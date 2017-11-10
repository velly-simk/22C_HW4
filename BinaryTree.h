// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Velly Simeonov
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree) { rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree() { clear(); }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   
	// deletes sub tree with provided root node, does nothing if node is not in tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
   
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>*  BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType> *nNode = 0;
	if (nodePtr) {
		nNode = new BinaryNode<ItemType>(nodePtr->getItem(), 
			copyTree(nodePtr->getLeftPtr()), 
			copyTree(nodePtr->getRightPtr()));
	}
	return nNode;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr == NULL) return;

	BinaryNode<ItemType>* node = rootPtr;

	// Locate start
	while ((node != NULL) && (node->getItem() != nodePtr->getItem())) {
		if (nodePtr->getItem() < node->getItem()) {
			node = node->getLeftPtr();
		}
		else if (nodePtr->getItem() > node->getItem()) {
			node = node->getRightPtr();
		}
	}

	if (node == NULL) return;
	// end locate

	// start deleting
	Queue<BinaryNode<ItemType>*> nodeQ;

	do {
		if (node == NULL) {
			nodeQ.dequeue(node);
			continue;
		}

		nodeQ.enqueue(node->getLeftPtr());
		nodeQ.enqueue(node->getRightPtr());

		delete node;
		--count;

		nodeQ.dequeue(node);

	} while (!nodeQ.isEmpty());
	// end deleting
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}  

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if (this != &sourceTree) {
		this->clear();

		BinaryNode<ItemType> *ptr;

		Queue<BinaryNode<ItemType>*> nodes;
		nodes.enqueue(sourceTree.rootPtr);
		
		while (!nodes.isEmpty()) {
			nodes.dequeue(ptr);
			while (ptr) {
				nodes.enqueue(ptr->getLeftPtr());
				nodes.enqueue(ptr->getRightPtr());
				this->insert(ptr->getItem());
				nodes.dequeue(ptr);
			}
		}
	}
	return *this;
}  


#endif

