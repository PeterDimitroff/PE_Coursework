//#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <ctime>
#include "company.h"
#include "employee.h"

Employee::Employee() { }
// for new employees
Employee::Employee(std::string name, std::string egn, std::list<std::string> projects, std::string department,
	std::string companyName, std::string companyID, uint32_t workHours) {
	_name = name;
	_egn = egn;
	time_t now = time(0);
	_employmentDate = *localtime(&now);
	_workHours = workHours;
	_projects = projects;
	_companyName = companyName;
	_companyID = companyID;
}

Employee::Employee(std::string name, std::string egn, std::list<std::string> projects, std::string department,
	std::string companyName, std::string companyID, uint32_t workHours, struct tm employmentDate) {
	_name = name;
	_egn = egn;
	_employmentDate = employmentDate;
	_workHours = workHours;
	_projects = projects;
	_companyName = companyName;
	_companyID = companyID;
}

std::string             Employee::getName() const                              { return this->_name; }
void                    Employee::setName(std::string name)                    { this->_name = name; }
std::string             Employee::getEgn() const                               { return this->_egn; }
void                    Employee::setEgn(std::string egn)                      { this->_egn = egn; }
tm                      Employee::getEmploymentDate() const                    { return this->_employmentDate; }
void                    Employee::setEmploymentDate(tm &employmentDate)        { this->_employmentDate = employmentDate; }
uint32_t                Employee::getWorkHours() const                         { return this->_workHours; }
void                    Employee::setWorkHours(uint32_t workHours)             { this->_workHours = workHours; }
std::list<std::string>& Employee::getProjects()                                { return this->_projects; }
void                    Employee::setProjects(std::list<std::string> projects) { this->_projects = projects; }
std::string             Employee::getDepartment() const                        { return this->_department; }
void                    Employee::setDepartment(std::string dep)               { this->_department = dep; }
std::string             Employee::getCompanyName() const                       { return this->_companyName; };
void                    Employee::setCompanyName(std::string companyName)      { this->_companyName = companyName; };
std::string             Employee::getCompanyID() const                         { return this->_companyID; };
void                    Employee::setCompanyID(std::string companyID)          { this->_companyName = companyID; };

void Employee::addProject(std::string project) {
	_projects.push_back(project);
}

void Employee::removeFromProject(std::string project) {
	_projects.remove(project);
}

std::ostream & operator << (std::ostream &out, const Employee &e) {
	std::list<std::string> projects = e._projects;
	std::list<std::string>::iterator p;

	out << e._name << "," << e._egn << "," << e._companyID << "," << e._department << ","
		<< e._employmentDate.tm_mday << "." << e._employmentDate.tm_mon + 1 << "." << e._employmentDate.tm_year + 1900;

	for (p = projects.begin(); p != projects.end(); p++) {
		out << "," << *p;
	}

	return out;
}