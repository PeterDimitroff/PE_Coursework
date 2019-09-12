#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <string>
#include <list>
#include <iterator>
#include <ctime>
#include <cstdlib>

class Department;
class Company;

class Employee {
private:
	std::string _name;
	std::string _egn;
	struct tm   _employmentDate;
	uint32_t    _workHours;
	std::list<std::string> _projects;
	std::string _department; // key _name
	std::string _companyName;
	std::string _companyID;

public:
	Employee();
	// for new employees
	Employee(std::string name, std::string egn, std::list<std::string> projects, std::string department,
		std::string companyName, std::string companyID, uint32_t workHours);
	Employee(std::string name, std::string egn, std::list<std::string> projects, std::string department,
		std::string companyName, std::string companyID,	uint32_t workHours, struct tm employmentDate);

	std::string             getName() const;
	void                    setName(std::string name);
	std::string             getEgn() const;
	void                    setEgn(std::string egn);
	tm                      getEmploymentDate() const;
	void                    setEmploymentDate(tm &employmentDate);
	uint32_t                getWorkHours() const;
	void                    setWorkHours(uint32_t workHours);
	std::list<std::string>& getProjects();
	void                    setProjects(std::list<std::string> projects);
	std::string             getDepartment() const;
	void                    setDepartment(std::string dep);
	std::string             getCompanyName() const;
	void                    setCompanyName(std::string companyName);
	std::string             getCompanyID() const;
	void                    setCompanyID(std::string companyID);

	void addProject(std::string project);
	void removeFromProject(std::string project);

	friend std::ostream& operator<< (std::ostream &out, const Employee &e);
};

