/*
	Homework 4 main header

	22C Fall 2017

	Velly Simeonov
*/

#pragma once

#ifndef HW4_H

#define HW4_H


#include "Queue.h"
#include "BinarySearchTree.h"
#include "Employee.h"

#include <string>


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

/* prints employee to stdout */
void coutPrint(Employee &emp);

/* used it to confirm index differences on binary tree nodes */
void testPrint(int offs, int odd, int dir);

/* prints to stdout bst in breadth first traversal */
int breadthPrint(BinarySearchTree<Employee> &bst);

/* prints to stdout bst in breadth first preorder, inorder and postorder */
int depthPrint(BinarySearchTree<Employee> &bst);

/* prints node with proper indentation for printBST() */
void nodePrint(Employee &item, int x);
#endif