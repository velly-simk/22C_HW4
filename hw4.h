#pragma once

#ifndef HW4_H

#define HW4_H


#include "Queue.h"
#include "BinarySearchTree.h"

#include <string>

class Employee {
	int _idNumber;
	std::string _name;

public:
	Employee() { _idNumber = 0, _name = ""; }
	Employee(int id, std::string name) { _idNumber = id, _name = name; }
	std::string getName() { return _name; }
	int getId() { return _idNumber; }

};

/* main program interface with user */
int menuManager(BinarySearchTree<Employee> &bst);

/* prints the menu to user */
int printMenu();

/* hidden option */
int printAuthor();

/* search interface*/
int searchManager(BinarySearchTree<Employee> &bst);

/* reads a file and changes lines object to contain the lines of the file */
int readFile(const std::string &fileName, Queue<string> &lines);

/* process a lines queue into employee objects */
int processLines(Queue<string> &lines, BinarySearchTree<Employee> &bst);

/* prints contents of queue to stdout */
int printQueue(Queue<string> &queue);

/* prints contents of bst to stdout */
int printBST(BinarySearchTree<Employee> &bst);

/* prints tree in breadth first format */
int printBST_breadth(BinaryTree<Employee> &bst);

/* prints employee to stdout */
void coutPrint(Employee &emp);

void testPrint(int offs, int odd, int dir);

/* prints to stdout bst in breadth first traversal */
int breadthPrint(BinarySearchTree<Employee> &bst);

/* prints to stdout bst in breadth first preorder, inorder and postorder */
int depthPrint(BinarySearchTree<Employee> &bst);

void treePrint(Employee &item, int x);

/* employee operator overloads */
bool operator<(Employee a, Employee b) { return a.getId() < b.getId(); }
bool operator>(Employee a, Employee b) { return b < a; }
bool operator<=(Employee a, Employee b) { return !(a > b); }
bool operator>=(Employee a, Employee b) { return !(a < b); }
bool operator==(Employee a, Employee b) { return a.getId() == b.getId(); }
bool operator!=(Employee a, Employee b) { return !(a == b); }

#endif