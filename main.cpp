// 20 November 2018
// Lior Sinai, s1909134
// Based on Deitel & Deitel Fig. 12.17: fig12_17.cpp
// Processing Employee derived-class objects with static binding 
// then polymorphically using dynamic binding.
#include <iostream>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "SalariedEmployee.h" 
#include "CommissionEmployee.h"  
#include "BasePlusCommissionEmployee.h" 
//using namespace std;

void virtualViaPointer(const Employee* const); // prototype
void virtualViaReference(const Employee&); // prototype

int main() {
	std::cout << std::fixed << std::setprecision(2); // set floating-point formatting

	std::vector<SalariedEmployee*> salariedEmployees;
	std::vector<CommissionEmployee*> commissionEmployees;
	//std::vector<BasePlusCommissionEmployee*> basePlusCommissionEmployees; //Lior: not needed afer adding sales function
	int type; // a variable to swtich case for each type
	char inputString[255]; // declare character array large enough to hold 255 characters
	std::string firstName; 
	std::string  lastName;
	std::string socialSecurityNumber;
	double salary;
	double sales;
	double rate;
	double baseSalary;

	std::cout << "What type of employee would you like to add (input the number only):\n" <<
		"1: salaried employee\n" <<
		"2: comissioned employee\n" <<
		"3: base salary + comission employee\n" <<
		"4: exit" <<
		"\n";

	// User inputs its on employees
	bool addMore = true;
	while (addMore)
	{	
		std::cin >> type;
		
		// check if the input was read properly
		if ((type < 1) || (type > 4))
		{
			std::cin.clear();
			std::cin.ignore(255, '\n');  // discard rest of the input stream
			std::cout << "Input not recognised. Please input 1,2,3 or 4." << '\n';
			continue; //skip to the start again to get a valid input
		}

		if (type == 4) 
		{
			addMore = false;
			break;
		}
		
		
		std::cout << "Please enter their first and last name:" << "\t";
		std::cin.getline(inputString, 255, ' '); // deliminator is a space, so assumes the first word is the first name
		// XXX for later: add functionality for only entering a first name: exit after enter and check for first space in the character array
		firstName = inputString;// convert char array to string
		std::cin.getline(inputString, 255, '\n'); // and the rest is the last name, and discard everything after '\n'
		lastName = inputString; // convert char array to string
		// Check
		//std::cout << "First name: " << firstName << '\n';
		//std::cout << "Last name: " << lastName << '\n';

		std::cout << "Please enter the social security number (format: xxx-xx-xxxx):" << "\t";
		std::cin.getline(inputString, 255, '\n');
		socialSecurityNumber = inputString; // convert char array to string
		// Check
		//std::cout << "Social secruity number: " << socialSecurityNumber << '\n';
		//SalariedEmployee dummyPerson =  SalariedEmployee{ firstName, lastName, socialSecurityNumber, 0 };
		switch (type)
		{
			case 1:
				std::cout << "Please enter a salary: ";
				std::cin >> salary;
				std::cin.ignore(255, '\n');
				//dummyPerson = SalariedEmployee{ firstName, lastName, socialSecurityNumber, salary };
				//std::cout << dummyPerson.toString() << '\n';
				//salariedEmployees.push_back(&dummyPerson);
				salariedEmployees.push_back(new SalariedEmployee{ firstName, lastName, socialSecurityNumber, salary });
				break;
			case 2:
				std::cout << "Please enter the commission rate (0<rate<1): ";
				std::cin >> rate;
				std::cin.ignore(255, '\n');
				std::cout << "Please enter the gross weekly sales for this employeee: ";
				std::cin >> sales;
				std::cin.ignore(255, '\n');

				commissionEmployees.push_back(new CommissionEmployee{ firstName, lastName, socialSecurityNumber, sales,rate });
				break;

			case 3:
				std::cout << "Please enter the base salary: ";
				std::cin >> salary;
				std::cin.ignore(255, '\n');
				std::cout << "Please enter the commission rate (0<rate<1): ";
				std::cin >> rate;
				std::cin.ignore(255, '\n');
				std::cout << "Please enter the gross weekly sales for this employeee: ";
				std::cin >> sales;
				std::cin.ignore(255, '\n');

				commissionEmployees.push_back(new BasePlusCommissionEmployee{ firstName, lastName, socialSecurityNumber, sales,rate,salary });
				break;
		}
		//prompt for next loop (does not include options)
		std::cout << "\nWhat type of employee would you like to add (input the number only): ";
	}
	std::cout << "\n";

	// Print all employees
	for (const Employee* employeePtr : salariedEmployees) {
		std::cout << employeePtr->toString() << "\n\n";
	}
	for (const Employee* employeePtr : commissionEmployees) {
		std::cout << employeePtr->toString() << "\n\n";
	}

	// Get total salaries
	std::cout << "Please enter how many weeks you would like to pay salaries for: ";
	int weeks;
	std::cin >> weeks;
	std::cin.ignore(255, '\n');
	double totalSalaries = 0.0;
	for (const SalariedEmployee* employeePtr : salariedEmployees) {
		totalSalaries += employeePtr->getWeeklySalary();
	}
	for (const CommissionEmployee* employeePtr : commissionEmployees) {
		totalSalaries += employeePtr->earnings();
	}
	std::cout << "total salaries for " << weeks << " weeks: " << weeks * totalSalaries << '\n';

	// Get total sales
	double totalSales = 0.0;
	for (const CommissionEmployee* employeePtr : commissionEmployees) {
		totalSales += employeePtr->getGrossSales();
	}
	std::cout << "total sales: " << totalSales << '\n';


	/* alternative methods to print the vector 
	//std::cout << "EMPLOYEES PROCESSED POLYMORPHICALLY VIA DYNAMIC BINDING\n\n";
	// call virtualViaPointer to print each Employee's information
	// and earnings using dynamic binding
	//std::cout << "VIRTUAL FUNCTION CALLS MADE OFF BASE-CLASS POINTERS\n";

	for (const Employee* employeePtr : myEmployees) {
		virtualViaPointer(employeePtr);
	}

	
	// call virtualViaReference to print each Employee's information 
	// and earnings using dynamic binding
	std::cout << "VIRTUAL FUNCTION CALLS MADE OFF BASE-CLASS REFERENCES\n";

	for (const Employee* employeePtr : employees) {
		virtualViaReference(*employeePtr); // note dereferencing
	}
	*/
}

// call Employee virtual functions toString and earnings off a   
// base-class pointer using dynamic binding                   
void virtualViaPointer(const Employee* const baseClassPtr) {
	std::cout << baseClassPtr->toString()
		<< "\nearned $" << baseClassPtr->earnings() << "\n\n";
}

// call Employee virtual functions toString and earnings off a  
// base-class reference using dynamic binding                
void virtualViaReference(const Employee& baseClassRef) {
	std::cout << baseClassRef.toString()
		<< "\nearned $" << baseClassRef.earnings() << "\n\n";
}

