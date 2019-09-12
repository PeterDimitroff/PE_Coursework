// PE_38_Peter.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <ctime>
#include "company.h"
#include "employee.h"
#include <cstdlib>
#include <ctype.h>
#include <sstream>
#include <algorithm>

using namespace std;

/* DECLARATIONS */

list <Company> lCompanies;


// Functions

string getString(string label) {
	string in;
	//fflush(stdin);
	cout << "Enter " << label << ":";
	//cin.ignore();
	getline(cin, in);
	return in;
}

int getYear() {
	string str = "";
	int year = 0;

	while (true) {
		cout << "Year: ";
		getline(cin, str);
		try { year = stoi(str, nullptr); }
		catch (const std::invalid_argument&) {
			cout << "Please enter a valid number.\n";
			continue;
		}
		break;
	}
	return year;
}

int getMonth() {
	string str = "";
	int month = 0;

	while (true) {
		cout << "Month: ";
		getline(cin, str);
		try { month = stoi(str, nullptr); }
		catch (const std::invalid_argument&) {
			cout << "Please enter a valid number.\n";
			continue;
		}
		if (month < 1 || month > 12) {
			cout << "Enter a valid month from 1 to 12.\n";
			continue;
		}
		break;
	}
	return month;
}

int getDay(int year, int month) {
	string str = "";
	int day = 0,
		maxday = 0;

	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		maxday = 31;
		break;
	case 4: case 6: case 9: case 11:
		maxday = 30;
		break;
	case 2:
		if (year % 4 == 0) {
			maxday = 29;
		}
		else {
			maxday = 28;
		}
		break;
	default:
		cout << "ERROR Invalid month received in getDay()!\n";
		return -1;
	}

	while (true) {
		cout << "Date: ";
		getline(cin, str);
		try { day = stoi(str, nullptr); }
		catch (const std::invalid_argument&) {
			cout << "Please enter a valid number.\n";
			continue;
		}
		if (day < 1 || day > maxday) {
			cout << "Enter a valid day from 1 to " << maxday << "\n";
			continue;
		}
		break;
	}
	return day;
}

bool isNumerical(const string& s) {
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) it++;
	return !s.empty() && it == s.end();
}

/*// Controversial - not used for now.
Company& getCompanyByName(string name) {
	for (list<Company>::iterator c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == name) {
			return *c;
		}
		else {
			throw runtime_error("NotFound");
		}
	}
}*/

void addEmployee() {
	Employee e;
	string egn = "", name = "", dep = "", comp = "", compId = "", input = "";
	list<string> projects, companyProjects;
	list<Company>::iterator c;
	//list<Department>& lDeps;
	list<Department>::iterator d;
	struct tm employmentDate;
	int workHours = 0,
		year = 0,
		month = 0,
		day = 0;

	cout << "Adding Employee." << endl;
	while (name == "")	name = getString("Name");

	while (true) {
		egn = getString("EGN");
		if (!isNumerical(egn)) {
			cout << "Invalid EGN! Must contain digits only." << endl;
			continue;
		}
		if (egn.size() != 10) {
			cout << "EGN must be 10 digits long!" << endl;
			continue;
		}
		break;
	}

	while (comp == "") {
		input = getString("Company");
		if (input == "") continue;
		for (c = lCompanies.begin(); c != lCompanies.end(); c++) {
			if (c->getName() == input) {
				comp = input;
				compId = c->getId();
				companyProjects = c->getProjects(); // ??
				break;
			}
		}
		if (c == lCompanies.end()) {
			cout << "No such Company!\n";
			continue;
		}
	}
	list<Department>& lDeps = c->getDepartments();
	while (dep == "") {
		input = getString("Department");
		if (input == "") continue;
		
		for (d = lDeps.begin(); d != lDeps.end(); d++) {
			if (d->getName() == input) {
				dep = input;
				break;
			}
		}
		if (d == lDeps.end()) {
			cout << "No such Department!\n";
			continue;
		}
	}

	input = getString("Projects? [y/N]");
	if (input == "y") {
		while (true) {
			input = getString("Project Name");
			if (input.size() > 0) {
				if (find(projects.begin(), projects.end(), input) != projects.end()) {
					cout << "Duplicate entry not inserted.\n";
				}
				else if (find(companyProjects.begin(), companyProjects.end(), input) == companyProjects.end()) {
					cout << "No such project in company.\n";
				}
				else {
					projects.push_back(input);
				}

				input = getString("Another Project? [y/n]");
				if (input != "y") break;
			}
		}
	}
	
	while (workHours == 0) {
		input = getString("Work Hours [8]");
		if (input == "") {
			workHours = 8;
			break;
		}
		try { year = stoi(input, nullptr); }
		catch (const std::invalid_argument&) {
			cout << "Please enter an integer over 0.\n";
			continue;
		}
	}

	input = getString("Set employment date different than today? [y/N]");
	if (input == "y") {
		year = getYear();
		month = getMonth();
		day = getDay(year, month);
		if (day == -1) {
			cout << "Could not set a creation date!\n";
			year = month = day = 0;
		}
		else {
			employmentDate.tm_year = year - 1900;
			employmentDate.tm_mon = month - 1;
			employmentDate.tm_mday = day;
			mktime(&employmentDate);
		}
	}
	
	if (year && month && day) {
		e = Employee(name, egn, projects, dep, comp, compId, workHours, employmentDate);
	}
	else {
		e = Employee(name, egn, projects, dep, comp, compId, workHours);
	}

	d->addEmployee(e);
}

void addCompany() {
	string name = "", input = "", id = "";
	list <string> projects, deps;
	bool dds = 0;
	companyType t;
	int num = 0;

	while (name == "") name = getString("Company Name");
	for (list<Company>::iterator c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == name) {
			cout << "Company with this name exists. Aborting.\n";
			return;
		}
	}

	while (input != "y" && input != "n") input = getString("DDS registered [y/n]");
	(input == "y") ? dds = true : dds = false;

	cout << "Company Types:" << endl << "1. ET" << endl << "2. EOOD" << endl << "3. OOD" << endl << "4. AD" << endl;
	while (num < 1 || num > 4) {
		input = getString("Type");
		try { num = stoi(input, nullptr); }
		catch (const std::invalid_argument&) {
			cout << "Please enter a valid number!" << endl;;
		}
	}
	t = companyType(num);

	input = getString("Projects? [y/n]");
	if (input == "y") {
		while (true) {
			input = getString("Project Name");
			if (input.size() > 0) {
				if (find(begin(projects), end(projects), input) != end(projects)) {
					cout << "Duplicate entry not inserted.\n";
				}
				else {
					projects.push_back(input);
				}
				input = getString("Another Project? [y/n]");
				if (input != "y") break;
			}
		}
	}

	input = getString("Departments? [y/n]");
	if (input == "y") {
		while (true) {
			input = getString("Department Name");
			if (input.size() > 0) {
				if (find(begin(deps), end(deps), input) != end(deps)) {
					cout << "Duplicate entry not inserted.\n";
				}
				else {
					deps.push_back(input);
				}
					input = getString("Another Department? [y/n]");
					if (input != "y") break;
			}
		}
	}

	id = generateID();
	Company comp(t, name, dds, projects, deps);
	lCompanies.push_back(comp);
	cout << "Successfully added company " << name << ". Bulstat: " << comp.getId() << endl << endl;

	getString("anything to continue");
}

void addDepartment() {
	string dep = "",
		comp = "",
		input = "";
	int year = 0,
		month = 0,
		day = 0;
	//list<Department>& deps;

	while (dep == "")
		dep = getString("Department Name");

	input = getString("Set creation date different than today? [y/N]");
	if (input == "y") {
		year = getYear();
		month = getMonth();
		day = getDay(year, month);
		if (day == -1) {
			cout << "Could not set a creation date!\n";
			year = month = day = 0;
		}
	}

	while (comp == "")
		comp = getString("Company Name");

	for (list<Company>::iterator c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == comp) {
			list<Department>& deps = c->getDepartments();
			try {
				if (year && month && day)
					c->addDepartment(dep, year, month, day);
				else
					c->addDepartment(dep);
				cout << "Department sucessfully added." << endl;
			}
			catch (AlreadyExistsException const&) {
				cout << "Company already has department '" << dep << "' . Aborting.\n";
			}
			getString("anything to continue");
			return;
		}
	}
	cout << "Company not found!" << endl;
	getString("anything to continue");
}

void listCompanies() {
	list<Company>::iterator c;
	cout << "Company Name,Type,Bulstat,DDS status" << endl;
	for (c = lCompanies.begin(); c != lCompanies.end(); c++) {
		cout << *c << endl;
	}
	getString("anything to continue");
}

void listDepartments() {
	list<Department>::iterator d;
	string comp = "";
	//list<Department>& deps;

	while (comp == "")
		comp = getString("Company Name");

	for (list<Company>::iterator it = lCompanies.begin(); it != lCompanies.end(); it++) {
		if (it->getName() == comp) {
			list<Department>& deps = it->getDepartments();
			cout << "Department Name, Company Name, Creation Date" << endl;
			for (d = deps.begin(); d != deps.end(); d++) {
				cout << *d << "\n";
			}
			getString("anything to continue");
		}
	}
}

void addProject() {
	string p = "", comp = "";
	list<Company>::iterator c;
	//list<string>& projects;
	
	while (p == "")
		p = getString("Project Name");

	while (comp == "")
		comp = getString("Company Name");

	for (c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == comp) {
			list<string>& projects = c->getProjects();
			for (list<string>::iterator it = projects.begin(); it != projects.end(); it++) {
				if (*it == p) {
					cout << "This company already has such a project. Nothing to do." << endl;
					getString("anything to continue");
					return;
				}
			}
			c->addProject(p);
			cout << "Project sucessfully added." << endl;
			getString("anything to continue");
			return;
		}
	}

	cout << "Company not found!" << endl;
	getString("anything to continue");
}

void listProjects() {
	string comp = "";
	list<Company>::iterator c;
	//list<string>& projects;

	while (comp == "")
		comp = getString("Company Name");

	for (c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == comp) {
			list<string>& projects = c->getProjects();
			for (list<string>::iterator it = projects.begin(); it != projects.end(); it++) {
				cout << *it << endl;
			}
			getString("anything to continue");
			return;
		}
	}
	cout << "Company not found!" << endl;
	getString("anything to continue");
}

void listProjectEmployees() {
	string project = "",
		company = "",
		input = "";
	list<Employee> empls;
	list<Company>::iterator c;
	list<string> projects;
	list<Department> deps;

	while (company == "")
		company = getString("Company Name");

	for (c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == company) {
			break;
		}
	}
	if (c == lCompanies.end()) {
		cout << "No such Company!\n";
		return;
	}
	
	projects = c->getProjects();

	while (project == "") {
		project = getString("Project Name");
		if (find(begin(projects), end(projects), project) == end(projects)) {
			cout << "No such project in company!\n";
			return;
		}
		else {
			break;
		}
	}

	deps = c->getDepartments();

	cout << "Name,EGN,Company,Department,Employment Date[,Any And All Projects]\n";
	for (list<Department>::iterator d = deps.begin(); d != deps.end(); d++) {
		empls = d->getEmployees();
		for (list<Employee>::iterator e = empls.begin(); e != empls.end(); e++) {
			projects = e->getProjects();
			if (find(begin(projects), end(projects), project) != end(projects)) {
				cout << *e << "\n";
			}
		}
	}
	getString("anything to continue");
}

void listDepartmentEmployees() {
	string dep = "",
		company = "",
		input = "";
	list<Employee> empls;
	list<Company>::iterator c;
	list<Department> deps;
	list<Department>::iterator d;

	while (company == "")
		company = getString("Company Name");

	for (c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == company) {
			break;
		}
	}
	if (c == lCompanies.end()) {
		cout << "No such Company!\n";
		return;
	}

	deps = c->getDepartments();

	while (dep == "") {
		input = getString("Department Name");
		for (d = deps.begin(); d != deps.end(); d++) {
			if (d->getName() == input) {
				dep = input;
				break;
			}
		}
		if (dep == "") {
			cout << "No such department in company!\n";
		}
	}
	cout << "Name,EGN,Company,Department,Employment Date[,Any And All Projects]\n";
	empls = d->getEmployees();
	for (list<Employee>::iterator e = empls.begin(); e != empls.end(); e++) {
		cout << *e << "\n";
	}
	getString("anything to continue");
}

void listCompanyEmployees() {
	string company = "",
		input = "";
	list<Employee> empls;
	list<Company>::iterator c;
	list<Department> deps;

	while (company == "")
		company = getString("Company Name");

	for (c = lCompanies.begin(); c != lCompanies.end(); c++) {
		if (c->getName() == company) {
			break;
		}
	}
	if (c == lCompanies.end()) {
		cout << "No such Company!\n";
		return;
	}
	deps = c->getDepartments();
	cout << "Name,EGN,Company,Department,Employment Date[,Any And All Projects]\n";
	for (list<Department>::iterator d = deps.begin(); d != deps.end(); d++) {
		empls = d->getEmployees();
		for (list<Employee>::iterator e = empls.begin(); e != empls.end(); e++) {
			cout << *e << "\n";
		}
	}
	getString("anything to continue");
}

void show_menu(string extraMessage = "") {
	cout << endl;//system("cls");
	cout << "Main Menu" << endl;
	cout << "1.  List Companies." << endl;
	cout << "2.  List Departments per Company." << endl;
	cout << "3.  List Employees   per Project." << endl;
	cout << "4.  List Employees   per Department." << endl;
	cout << "5.  List Employees   per Company." << endl;
	cout << "6.  List Projects    per Company." << endl;
	cout << "7.  Add Company." << endl;
	cout << "8.  Add Department." << endl;
	cout << "9.  Add Employee." << endl;
	cout << "10. Add Project." << endl;
	cout << "11. Exit." << endl;
	if (extraMessage != "") cout << extraMessage << endl;
	cout << "Your Choice: ";
}

void menu()
{
	string input;
	int choice = 0;
	
	show_menu();

	while (choice < 1 || choice > 11) {
		getline(cin, input);
		fflush(stdin);

		try { choice = stoi(input, nullptr); }
		catch (const std::invalid_argument&) {
			show_menu("Please enter a valid number.");
			continue;
		}
		if (choice > 11 || choice < 1) {
			show_menu("Please choose a valid option.");
			continue;
		}
	} // while choice

	switch (choice) {
	case 1:
		listCompanies();
		break;
	case 2:
		listDepartments();
		break;
	case 3:
		listProjectEmployees();
		break;
	case 4:
		listDepartmentEmployees();
		break;
	case 5:
		listCompanyEmployees();
		break;
	case 6:
		listProjects();
		break;
	case 7:
		addCompany();
		break;
	case 8:
		addDepartment();
		break;
	case 9:
		addEmployee();
		break;
	case 10:
		addProject();
		break;
	case 11:
		// free memory
		exit(0);
	default:
		cerr << "Unknown case!";
	}
}

// GO

int main()
{
	list<string> projects{"Windows", "Visual Studio", "Microsoft Office"};
	list<string> deps{ "R&D", "SQA", "CIA", "Marketing" };
	Employee bill;
	Company microsoft((companyType) 4, "Microsoft", true, projects, deps);
	bill = Employee("Bill Gates", "5911098524", list<string> {"Windows"}, "CIA", "Microsoft", microsoft.getId(), 16);

	list<Department>& lDeps = microsoft.getDepartments();
	for (list<Department>::iterator d = lDeps.begin(); d != lDeps.end(); d++) {
		if (d->getName() == "CIA") {
			d->addEmployee(bill);
			cout << "Added Bill!\n\n";
			cout << bill << "\n";
		}
	}
	lCompanies.push_back(microsoft);

	for (list<Company>::iterator i = lCompanies.begin(); i != lCompanies.end(); i++) {
		if (i->getName() == "Microsoft") {
			lDeps = i->getDepartments();
			for (list<Department>::iterator d = lDeps.begin(); d != lDeps.end(); d++) {
				if (d->getName() == "CIA") {
					cout << "CIA employees " << d->getEmployeeCount() << "\n";
					list<Employee>& empls = d->getEmployees();

					for (list<Employee>::iterator e = empls.begin(); e != empls.end(); e++) {
						cout << *e << "/n";
					}
				}
			}
		}
	}

	while(true) menu();
}

































/*
#include "stdafx.h"
#include <iostream>
#include <string>
#include <list> 
#include <iterator>
#include <ctime>

using namespace std;

class Employee {
private:
	string _name;
	string _egn;
	//uint32_t _monthsWorked; // TODO: change to date_started
	struct tm *_employmentDate;
	uint32_t _workHours;
	list <string> _projectIds; // primerno

public:

	Employee() { }
	// for new employees
	Employee(string name, string egn, list <string> projectIds) {
		_name = name;
		_egn = egn;
		time_t now = time(0);
		_employmentDate = localtime(&now);
		_workHours = 8;
		_projectIds = projectIds;
	}
	
	// for old employees
	Employee(string name, string egn, struct tm *employmentDate, uint32_t workHours, list <string> projectIds) {
		_name = name;
		_egn = egn;
		_employmentDate = employmentDate;
		_workHours = workHours;
		_projectIds = projectIds;
	}

	string   getName()                                { return _name; }
	void     setName(string name)                     { _name = name; }
	string   getEgn()                                 { return _egn; }
	void     setEgn(string egn)                       { _egn = egn; }
	tm       getEmploymentDate()                      { return *_employmentDate; }
	void     setEmploymentDate(tm *employmentDate)    { _employmentDate = employmentDate; }
	uint32_t getWorkHours()                           { return _workHours; }
	void     setWorkHours(uint32_t workHours)         { _workHours = workHours; }
	list <string> getProject_ids()                    { return _projectIds; }
	void     setProjectIds(list <string> projectIds)  { _projectIds = projectIds; }
	
	void addToProject(string projectId) {
		_projectIds.push_back(projectId);
	}

	void removeFromProject(string projectId) {
		_projectIds.remove(projectId);
	}
};

int main()
{
	list <Employee> l;
	Employee gosho = Employee("Gosho", "46851", {"p1", "p2"});

	l.push_back(gosho);

	list <Employee> ::iterator it;
	for (it = l.begin(); it != l.end(); ++it) {
		cout << it->getName() << " " << it->getMonthsWorked() << endl;
	}
	
	getchar();
}
*/