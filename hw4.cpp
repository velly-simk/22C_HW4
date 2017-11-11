/*
	Homework 4 main entry point and helpers.

	22C Fall 2017

	Velly Simeonov
*/
#include <fstream>
#include <iostream>
#include <string>


#include "BinarySearchTree.h"
#include "Queue.h"
#include "hw4.h"


int main(int charc, char *argv[]) {
	Queue<string> readFileLines;
	BinarySearchTree<Employee> db;

	readFile("employees.txt", readFileLines);
	processLines(readFileLines, db);

	menuManager(db);

}

int menuManager(BinarySearchTree<Employee> &bst) {
	std::string input = "";

	printMenu();

	while (input != "Q") {
		std::cout << "User command : ";

		std::getline(std::cin, input); // get whole line so we dont need to flush

		if (input.length() != 1) continue; // input thats not 1 character in length is invalid

		input[0] = toupper(input[0]);

		if (input[0] == 'S') {
			searchManager(bst);
		}
		else if (input[0] == 'D') {
			depthPrint(bst);
		}
		else if (input[0] == 'B') {
			breadthPrint(bst);
		}
		else if (input[0] == 'T') {
			printBST(bst);
		}
		else if (input[0] == 'L') {
			Employee left = Employee(0, "");
			bst.getLeftMost(left);

			if (left.getId() != 0)
				coutPrint(left);
			else
				std::cout << "Database is empty." << std::endl;
		}
		else if (input[0] == 'H') {
			Employee right = Employee(0,"");
			bst.getRightMost(right);

			if (right.getId())
				coutPrint(right);
			else
				std::cout << "Database is empty." << std::endl;
		}
		else if (input[0] == 'M') {
			std::cout << std::endl;
			printMenu();
		}
		else if (input[0] == 'A') {
			printAuthor();
		}

	}

	return 0;
}

int printMenu() {
	std::cout << "Employee Database Menu" << std::endl;
	std::cout << "\t\tS - Search by unique key." << std::endl;
	std::cout << "\t\tD - Recursive Depth-First Traversals." << std::endl;
	std::cout << "\t\tB - Breadth-First Traversal." << std::endl;
	std::cout << "\t\tT - Print Tree." << std::endl;
	std::cout << "\t\tL - Print Smallest Key." << std::endl;
	std::cout << "\t\tH - Print Largest Key." << std::endl;
	std::cout << "\t\tM - Show Menu." << std::endl;
	std::cout << "\t\tQ - Quit Program." << std::endl;
	return 0;
}

int printAuthor() {
	std::cout << "\t\tProgram author: Velly Simeonov" << std::endl;
	return 0;
}

int searchManager(BinarySearchTree<Employee> &bst) {
	std::string input = "";
	int id = -1;
	
	while (input != "Q") {
		std::cout << "Employee ID (or Q to go back) : ";
		std::getline(cin, input);
		if (input.size() > 0) {
			input[0] = ::toupper(input[0]);
			try {
				if ((id = std::stoi(input, NULL)) > 0) {
					Employee a = Employee(id, std::string(""));
					if (bst.getEntry(a, a)) {
						std::cout << std::endl;
						coutPrint(a);
					}
					else {
						std::cout << "\n\t\t" << a.getId() << " Not found." << std::endl;
					}
					id = -1;
				}
			}
			catch (exception e) {
				continue;
			}
		}
	}



	return 0;
}

int readFile(const std::string &fileName, Queue<string> &lines) {
	string tmpLine;
	std::ifstream iFile;

	iFile.open(fileName, std::fstream::in);

	if (!iFile) return 1; // file failed to open

	while (std::getline(iFile,tmpLine)) {
		lines.enqueue(tmpLine);
	}

	iFile.close();

	return 0;
}

int processLines(Queue<string> &lines, BinarySearchTree<Employee> &bst) {
	std::string tmp;
	size_t index = 0;

	Employee tmp2;
	int id;
	std::string name;

	while (!lines.isEmpty()) {
		lines.dequeue(tmp);

		id = std::stoi(tmp, &index);
		name = tmp.substr(index);
		tmp2 = Employee(id, name);

		bst.insert(tmp2); // silently ignores duplicates
	}

	return 0;
}

int printQueue(Queue<string> &queue) {
	int i = queue.getCount();
	while (i) {
		std::string tmp;
		queue.dequeue(tmp);
		std::cout << tmp << std::endl;
		queue.enqueue(tmp);
		i--;
	}
	return 0;
}

int printBST(BinarySearchTree<Employee> &bst) {
	/* vertical table
	Employee *employees = NULL;
	int arrSize = pow(2, bst.Depth() + 1) - 1;
	int negtabs, tabs = bst.Depth();

	
	bst.toArray(employees);
	
	for (int i = 0; i < arrSize; ++i) {
		negtabs = log2(i + 1);
		for (int x = 0; x <= tabs - negtabs; ++x) std::cout << "\t";
		std::cout << negtabs+1 << ". "  << employees[i].getId() << "\t";
		if (i+1 == pow(2,negtabs+1)-1) std::cout << "\n";
	}
	delete[] employees;
	*/

	std::cout << "\nBinary tree growing horizontally :\n" << std::endl;
	bst.inOrderR(nodePrint);
	std::cout << std::endl;
	return 0;
}

void coutPrint(Employee &emp) {
	std::cout << "\t\t" << emp.getId() << " " << emp.getName() << std::endl;
}


void testPrint(int top, int bot, int dir) {
	int newTop, newBot;

	newTop = top * 2;
	newBot = 2 * bot - 1;
	
	std::cout << top << " : " << bot << std::endl;

	if (top < 1)
		newTop = 1;
	
	if ((dir == 0) && (top < 9)){
		testPrint(newTop, newBot, 0);
		testPrint(newTop + 1, newBot + 2, 1);
	}
	else if ((dir == 1) && (top < 9)) {
		testPrint(newTop - 1, newBot, 0);
		testPrint(newTop, newBot + 2, 1);
	}
}

int breadthPrint(BinarySearchTree<Employee> &bst) {
	Queue<Employee> employees;
	Employee a;
	bst.breadthOrder(employees);

	std::cout << "\nBinary Tree in Breadth-First Traversal Order : " << std::endl;

	while (!employees.isEmpty()) {
		employees.dequeue(a);
		coutPrint(a);
	}
	return 0;
}

int depthPrint(BinarySearchTree<Employee> &bst) {
	std::cout << "\nEmployees in Pre-Order depth traversal : " << std::endl;
	bst.preOrder(coutPrint);
	std::cout << "\nEmployees in In-Order depth traversal : " << std::endl;
	bst.inOrder(coutPrint);
	std::cout << "\nEmployees in Post-Order depth traversal : " << std::endl;
	bst.postOrder(coutPrint);
	return 0;
}

void nodePrint(Employee &item, int x) {
	for (int i = 0; i < x; ++i) std::cout << "\t";
	std::cout << x << ". " << item.getId() << std::endl;
}


/* program sample : tabs are missing

Employee Database Menu
S - Search by unique key.
D - Recursive Depth-First Traversals.
B - Breadth-First Traversal.
T - Print Tree.
L - Print Smallest Key.
H - Print Largest Key.
M - Show Menu.
Q - Quit Program.
User command : t

Binary tree growing horizontally :

2. 5044
3. 4033
1. 3099
2. 3088
3. 3055
0. 3022
2. 2077
3. 2066
1. 1022
2. 1011

User command : s
Employee ID (or Q to go back) : 2066

2066  Sophia Williams
Employee ID (or Q to go back) : 1

1 Not found.
Employee ID (or Q to go back) : -1
Employee ID (or Q to go back) : 0
Employee ID (or Q to go back) : 3022

3022  Duo Xue
Employee ID (or Q to go back) : 99999999999999999
Employee ID (or Q to go back) : 301923

301923 Not found.
Employee ID (or Q to go back) :
Employee ID (or Q to go back) : q
User command : m

Employee Database Menu
S - Search by unique key.
D - Recursive Depth-First Traversals.
B - Breadth-First Traversal.
T - Print Tree.
L - Print Smallest Key.
H - Print Largest Key.
M - Show Menu.
Q - Quit Program.
User command : d

Employees in Pre-Order depth traversal :
3022  Duo Xue
1022  John Plemmons
1011  Ashley McMullen
2077  Bill Twain
2066  Sophia Williams
3099  Adriana Ho
3088  Josh Smith
3055  Tim Nguyen
5044  Debbie Lancaster
4033  Dale Meht

Employees in In-Order depth traversal :
1011  Ashley McMullen
1022  John Plemmons
2066  Sophia Williams
2077  Bill Twain
3022  Duo Xue
3055  Tim Nguyen
3088  Josh Smith
3099  Adriana Ho
4033  Dale Meht
5044  Debbie Lancaster

Employees in Post-Order depth traversal :
1011  Ashley McMullen
2066  Sophia Williams
2077  Bill Twain
1022  John Plemmons
3055  Tim Nguyen
3088  Josh Smith
4033  Dale Meht
5044  Debbie Lancaster
3099  Adriana Ho
3022  Duo Xue
User command : m

Employee Database Menu
S - Search by unique key.
D - Recursive Depth-First Traversals.
B - Breadth-First Traversal.
T - Print Tree.
L - Print Smallest Key.
H - Print Largest Key.
M - Show Menu.
Q - Quit Program.
User command : b

Binary Tree in Breadth-First Traversal Order :
3022  Duo Xue
1022  John Plemmons
3099  Adriana Ho
1011  Ashley McMullen
2077  Bill Twain
3088  Josh Smith
5044  Debbie Lancaster
2066  Sophia Williams
3055  Tim Nguyen
4033  Dale Meht
User command : l
1011  Ashley McMullen
User command : h
5044  Debbie Lancaster
User command : a
Program author: Velly Simeonov
User command :


*/