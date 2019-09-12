#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <string>
#include <list>
#include <iterator>
#include <ctime>
#include <iostream>
#include "employee.h"

#define UNASSIGNED_DEP "__UNASSIGNED__"

//class Employee;

class Department {
private:
	std::string         _name; // used as key in company class
	struct tm           _creationDate;
	std::string         _companyName;
	std::string         _companyID;
	std::list<Employee> _employees;

public:

	Department();
	// for new departments
	Department(std::string name, std::string companyName, std::string companyID);
	// for old departments
	Department(std::string name, std::string companyName, std::string companyID, struct tm creationDate);
	Department(std::string name, std::string companyName, std::string companyID, int year, int month, int date);

	std::string getName() const;
	void        setName(std::string name);
	uint32_t    getEmployeeCount() const;
	std::string getCompanyName() const;
	void        setCompanyName(std::string companyName);
	tm          getCreationDate() const;
	void        setCreationDate(tm &creationDate);
	std::list<Employee>& getEmployees();

	void addEmployee(Employee e);
	void delEmployee(std::string EGN);
	void delEmployees();
	void delProject(std::string project);

	friend std::ostream& operator<< (std::ostream &out, const Department &d);
};