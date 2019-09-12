//#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <iterator>
#include <ctime>
#include "company.h"
#include "employee.h"
#include "department.h"

Department::Department() { }
// for new departments
Department::Department(std::string name, std::string companyName, std::string companyID) {
	_name = name;
	time_t now = time(0);
	_creationDate = *localtime(&now);
	_companyName = companyName;
	_companyID = companyID;
}
// for old departments
Department::Department(std::string name, std::string companyName, std::string companyID, struct tm creationDate) {
	_name = name;
	_creationDate = creationDate;
	_companyName = companyName;
	_companyID = companyID;
}

Department::Department(std::string name, std::string companyName, std::string companyID, int year, int month, int date) {
	_name = name;
	_companyName = companyName;
	_companyID = companyID;
	_creationDate.tm_year = year - 1900;
	_creationDate.tm_mon = month - 1;
	_creationDate.tm_mday = date;
	mktime(&_creationDate);
}


std::string Department::getName() const { return this->_name; }
void Department::setName(std::string name) {
	std::list<Employee>::iterator e;
	
	for (e = _employees.begin(); e != _employees.end(); e++) {
		e->setDepartment(name);
	}

	this->_name = name;
}

uint32_t    Department::getEmployeeCount() const                { return this->_employees.size(); }
std::string Department::getCompanyName() const                  { return this->_companyName; }
void        Department::setCompanyName(std::string companyName) { this->_companyName = companyName; }
tm          Department::getCreationDate() const                 { return this->_creationDate; }
void        Department::setCreationDate(tm &creationDate)       { this->_creationDate = creationDate; }
std::list<Employee>& Department::getEmployees()                 { return this->_employees; }

void Department::addEmployee(Employee e) {
	e.setDepartment(this->_name);
	this->_employees.push_back(e);
}

void Department::delEmployee(std::string EGN) {
	std::list<Employee>::iterator e;
	for (e = _employees.begin(); e != _employees.end(); e++) {
		if (e->getEgn().compare(EGN)) {
			this->_employees.erase(e);
		}
	}
}

void Department::delEmployees() {
	this->_employees.clear();
}

void Department::delProject(std::string project) {
	for (std::list<Employee>::iterator itEmp = this->_employees.begin(); itEmp != this->_employees.end(); itEmp++) {
			itEmp->removeFromProject(project);
	}
}

std::ostream& operator<< (std::ostream &out, const Department &d) {
	out << d._name << "," << d._companyName << "," << d._creationDate.tm_mday << "." << d._creationDate.tm_mon+1 << "." << d._creationDate.tm_year+1900;
	return out;
}