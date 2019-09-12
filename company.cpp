//#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <ctime>
#include "company.h"
#include "employee.h"
#include "department.h"

std::string generateID() {
	static const int len = 16;
	char id[len + 1];
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		id[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	id[len] = NULL;
	return std::string(id);
}

Company::Company(companyType type, std::string name, bool ddsRegistered) {
	_type = type;
	_name = name;
	_ddsRegistered = ddsRegistered;
	_ID = generateID();
	_unassignedDep = Department(UNASSIGNED_DEP, name, _ID);
}

Company::Company(companyType type, std::string name, bool ddsRegistered,
	std::list <std::string> projects, std::list <std::string> departmentNames) {
	_type = type;
	_name = name;
	_ddsRegistered = ddsRegistered;
	_projects = projects;
	_ID = generateID();
	_unassignedDep = Department(UNASSIGNED_DEP, name, _ID);

	for (std::string n : departmentNames) {
		_deps.push_back(Department(n, name, this->_ID));
	}
	
	//_employees = employees;
}

std::string              Company::getId() const { return this->_ID; }
companyType              Company::getCompanyType() const { return this->_type; }
void                     Company::setCompanyType(companyType type) { this->_type = type; }
std::string              Company::getName() const { return this->_name; }
void                     Company::setName(std::string name) { this->_name = name; }
bool                     Company::isDdsRegistered() const { return this->_ddsRegistered; }
void                     Company::setDdsRegistered(bool dds) { this->_ddsRegistered = dds; }
std::list <std::string>& Company::getProjects() { return this->_projects; }
void                     Company::setProjects(std::list <std::string> projects) { this->_projects = projects; }
std::list <Department>&  Company::getDepartments() { return this->_deps; }
void                     Company::setDepartments(std::list <Department> deps) { this->_deps = deps; }
//std::list <Employee>    Company::getEmployees() const { return this->_employees; }
//void                    Company::setEmployees(std::list <Employee> employees) { this->_employees = employees; }

void Company::addDepartment(Department dep) {
	for (std::list<Department>::iterator it = this->_deps.begin(); it != this->_deps.end(); it++) {
		if (it->getName() == dep.getName()) {
			throw AlreadyExistsException();
			//throw std::runtime_error("Department called " + dep + " already exists.");
		}
	}
	this->_deps.push_back(dep);
}

void Company::addDepartment(std::string dep) {
	for (std::list<Department>::iterator it = this->_deps.begin(); it != this->_deps.end(); it++) {
		if (it->getName() == dep) {
			throw AlreadyExistsException();
			//throw std::runtime_error("Department called " + dep + " already exists.");
		}
	}
	this->_deps.push_back(Department(dep, _name, _ID));
}

void Company::addDepartment(std::string dep, int year, int month, int date) {
	for (std::list<Department>::iterator it = this->_deps.begin(); it != this->_deps.end(); it++) {
		if (it->getName() == dep) {
			throw AlreadyExistsException();
			//throw std::runtime_error("Department called " + dep + " already exists.");
		}
	}
	this->_deps.push_back(Department(dep, _name, _ID, year, month, date));
}

int Company::delDepartment(std::string depName) {
	int ret = -1;
	for (std::list<Department>::iterator itDep = this->_deps.begin(); itDep != this->_deps.end(); itDep++) {
		if (itDep->getName() == depName) {
			std::list<Employee>& emps = itDep->getEmployees();
			while (!emps.empty()) {
				this->_unassignedDep.addEmployee( emps.front() );
				emps.pop_front();
			}
			this->_deps.erase(itDep);
			ret = 0;
		}
	}
	return ret;
}

void Company::addProject(std::string project) { this->_projects.push_back(project); }

int Company::delProject(std::string project) {
	int ret = -1;
	for (std::list<std::string>::iterator itP = this->_projects.begin(); itP != this->_projects.end(); itP++) {
		if (*itP == project) {
			this->_projects.erase(itP);

			for (std::list<Department>::iterator itDep = this->_deps.begin(); itDep != this->_deps.end(); itDep++) {
				itDep->delProject(project);
			}
			ret = 0;
		}
	}
	return ret;
}

void Company::addEmployee(Employee employee) { this->_unassignedDep.addEmployee(employee); }

std::ostream & operator << (std::ostream &out, const Company &c) {
	out << c._name << "," << c._type << "," << c._ID << "," << c._ddsRegistered;
	return out;
}


/*int Company::delEmployee(std::string empl) {
	for (std::list<Employee>::iterator e = this->_employees.begin(); e != this->_employees.end(); e++) {
		if (e->getName() == empl) {
			this->_employees.erase(e);

			return 0;
		}
	}
	return -1;
}*/