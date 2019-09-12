#pragma once
#include <string>
#include <list>
#include <iterator>
#include <ctime>
#include <iostream>
#include <exception>

#include "department.h"
#include "employee.h"

enum companyType {
	ET = 1,
	EOOD = 2,
	OOD = 3,
	AD = 4
};

std::string generateID();

class Company {
private:
	companyType             _type;
	std::string             _name;
	bool                    _ddsRegistered;
	std::list <std::string> _projects;
	std::list <Department>  _deps;
	Department              _unassignedDep;
	//std::list <Employee>    _employees;
	std::string             _ID;

public:
	Company() {}
	Company(companyType type, std::string name, bool ddsRegistered);

	Company(companyType type, std::string name, bool ddsRegistered,
		std::list <std::string> projects, std::list <std::string> departmentNames);

	std::string              getId() const;
	companyType              getCompanyType() const;
	void                     setCompanyType(companyType type);
	std::string              getName() const;
	void                     setName(std::string name);
	bool                     isDdsRegistered() const;
	void                     setDdsRegistered(bool dds);
	std::list <std::string>& getProjects();
	void                     setProjects(std::list <std::string> projects);
	std::list <Department>&  getDepartments();
	void                     setDepartments(std::list <Department> deps);
	//std::list <Employee>    getEmployees() const;


	void addDepartment(Department dep);
	void addDepartment(std::string dep);
	void addDepartment(std::string dep, int year, int month, int date);
	int  delDepartment(std::string depName);
	void addEmployee(Employee employee);

	void addProject(std::string project);
	int  delProject(std::string project);;

	friend std::ostream& operator<< (std::ostream &out, const Company &c);
};

class AlreadyExistsException : public std::exception {
public:
	const char * what() const throw ()
	{
		return "AlreadyExists Exception";
	}
};