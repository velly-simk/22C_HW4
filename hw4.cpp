
#include <fstream>
#include <iostream>
#include <string>

#include "BinarySearchTree.h"
#include "Queue.h"
#include "hw4.h"

#define DEBUG 1

int main(int charc, char *argv[]) {
	Queue<string> readFileLines;
	BinarySearchTree<Employee> db;

	readFile("employees.txt", readFileLines);
	processLines(readFileLines, db);

	if (DEBUG) {
		printQueue(readFileLines);
	}

	std::cout << readFileLines.getCount() << std::endl;

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

		}
		else if (input[0] == 'B') {

		}
		else if (input[0] == 'T') {

		}
		else if (input[0] == 'L') {

		}
		else if (input[0] == 'H') {

		}
		else if (input[0] == 'M') {
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
	std::cout << "S - Search by unique key." << std::endl;
	std::cout << "D - Recursive Depth-First Traversals." << std::endl;
	std::cout << "B - Breadth-First Traversal." << std::endl;
	std::cout << "T - Print Tree." << std::endl;
	std::cout << "L - Print Smallest Key." << std::endl;
	std::cout << "H - Print Largest Key." << std::endl;
	std::cout << "M - Show Menu." << std::endl;
	std::cout << "Q - Quit Program." << std::endl;
	return 0;
}

int printAuthor() {
	std::cout << "Program author: Velly Simeonov" << std::endl;
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
					if (bst.getEntry(a, a))
						std::cout << "\t" << a.getId() << " Found : " << a.getName() << std::endl;
					else {
						std::cout << "\t" << a.getId() << " Not found." << std::endl;
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
	return 0;
}

void visit(Employee &emp) {
	std::cout << emp.getId() << " " << emp.getName() << std::endl;
}