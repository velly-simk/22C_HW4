/*
	Employee class for HW4

	22C Fall 2017

	Velly Simeonov

*/

#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

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

/* employee operator overloads */
bool operator<(Employee a, Employee b) { return a.getId() < b.getId(); }
bool operator>(Employee a, Employee b) { return b < a; }
bool operator<=(Employee a, Employee b) { return !(a > b); }
bool operator>=(Employee a, Employee b) { return !(a < b); }
bool operator==(Employee a, Employee b) { return a.getId() == b.getId(); }
bool operator!=(Employee a, Employee b) { return !(a == b); }
#endif