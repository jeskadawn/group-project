// Group project

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
using namespace std;

// Array sizes
const int NAME_SIZE = 51;
const int ADDR_SIZE = 51;
const int CITY_SIZE = 20;
const int STATE_SIZE = 15;
const int ZIP_SIZE = 6;
const int PHONE_SIZE = 14;
const int PAYMENT_DATE_SIZE = 11;


//Define the customer structure
struct Customer
{
	char name[NAME_SIZE];
	char address[ADDR_SIZE];
	char city[CITY_SIZE];
	char state[STATE_SIZE];
	char zip[ZIP_SIZE];
	char phone[PHONE_SIZE];
	double acct_balance;
	char payment_date[PAYMENT_DATE_SIZE];
	
};

// Function prototypes
void displayMenu();
int getMenuChoice();
int enterRecords(Customer);
int searchName(Customer);
int displayContents(Customer);

int main()
{
	int choice;
	char again = 'N';
	
	Customer person;
	
	do
	{
		// Display menu
		displayMenu();
	
		//Get menu choice
		choice = getMenuChoice();
	
		
		switch(choice)
		{
			case 1: enterRecords(person);
					break;
					
			case 2: searchName(person);
					break;
			
			case 5: displayContents(person);
					break;
			
			case 6: cout << "Quitting program...";
					return 0;
					
			default: cout << "That is an invalid choice.\n";
		}

	
		cout << "\n\nDisplay menu again? Y or N: ";
		cin >> again;
		while (again != 'Y' && again != 'y' && again != 'N' && again != 'n')
		{
			cout << "Error. Please type either a Y or N: ";
			cin >> again;
		}
		cin.ignore(); 	// Skip over the remaning newline	
	} while (toupper(again) == 'Y');
	
	
	cout << "Program terminating...";
	
	
	
	return 0;
}


//*************************************
// displayMenu function
//
//*************************************

void displayMenu()
{
	cout << "(1) Enter new records into the file." << endl;
	cout << "(2) Search for a record and display it." << endl;
	cout << "(3) Search for a record and delete it." << endl;
	cout << "(4) Search for a record and change it." << endl;
	cout << "(5) Display the contents of the entire file." << endl;
	cout << "(6) Quit." << endl;
}

//***************************************
// getMenuChoice function
//
//***************************************

int getMenuChoice()
{
	int choice;
	cout << "\nMenu choice: ";
	cin >> choice;
	
	while (choice < 1 || choice > 6)		//Input validation
	{
		cout << "Error. Please enter a choice between 1 and 6: ";
		cin >> choice;	
	}
	
	return choice;	
}

//***************************************
// enterRecord function
//
//***************************************

int enterRecords(Customer person)
{
	char again;
	
	//Open a file for binary output.
	fstream records("records.dat", ios::out | ios::app | ios::binary);
	
	// Test for errors
	if (!records)
	{
		cout << "Error opening file. Program aborting.\n";
		return 0;
	}
	
	do
	{
		//Get data about a person
		cout << "Enter the following data about a person:\n";
		
		cout << "Name: ";
		cin.ignore();
		cin.getline(person.name, NAME_SIZE);
		
		cout << "Street Address: ";
		cin.getline(person.address, ADDR_SIZE);
		
		cout << "City: ";
		cin.getline(person.city, CITY_SIZE);
		
		cout << "State: ";
		cin.getline(person.state, STATE_SIZE);
		
		cout << "Zip Code: ";
		cin.getline(person.zip, ZIP_SIZE);
		
		cout << "Telephone number: ";
		cin.getline(person.phone, PHONE_SIZE);
		
		cout << "Account Balance: $";
		cin >> person.acct_balance;
		cin.ignore(); 	// Skip over the remaining newline.
		
		cout << "Date of last payment (##/##/####): ";
		cin.getline(person.payment_date, PAYMENT_DATE_SIZE);
		
		// Write the contents of the person structure to the file.
		records.write(reinterpret_cast<char *>(&person), sizeof(person));
		
		// Determine whether the user wants to write another record.
		cout << "Do you want to enter another record? ";
		cin >> again;
		while (again != 'Y' && again != 'y' && again != 'N' && again != 'n')
		{
			cout << "Error. Please type either a Y or N: ";
			cin >> again;
		}
		cin.ignore(); 	// Skip over the remaning newline
		
	} while (toupper(again) == 'Y');
	
	// Close the file
	records.close();
	
}

//***************************************
// searchName function
//
//***************************************

int searchName (Customer person)
{
	char name[NAME_SIZE];
	bool found = false;
	int pos = 0;
	fstream records;
	records.open("records.dat", ios::in | ios::binary);
	
	
	
	//Test for errors
	if (!records)
	{
		cout << "Error opening file. Program aborting.\n";
		return 0;
	}
	
	// Prompt the user for a name to search for
	cout << "What is the name of the person to search for?: ";
	cin.ignore();
	cin.getline(name, NAME_SIZE);
	
	
	// Read the first record from the file
	records.read(reinterpret_cast<char *>(&person), sizeof(person));
	pos++;
	
	
	while (!records.eof())
	{
		
		
		// Compare the user entered name to the name of the current record
		
		if (*person.name  == *name)
		{
			found = true;
			break;	
		}
		
		// Read the next record from the file.
		records.read(reinterpret_cast<char *>(&person), sizeof(person));
		pos++;

	}
	
	if (found == true)
	{
		cout << "Record found for " << name << ". Record #" << pos << endl;
	}
	else if (found == false)
	{
		cout << "No record found for " << name << endl;
	}
	
	//Return the position in the file the name was found at
	return pos;
}

//***************************************
// display Contents function
//
//***************************************

int displayContents(Customer person)
{
	
	fstream records;
	records.open("records.dat", ios::in | ios::binary);
	
	// Test for errors
	if (!records)
	{
		cout << "Error opening file. Program aborting.\n";
		return 0;
	}
	
	cout << "\n\nFILE CONTENTS:\n\n";
	
	// Read the first record from the file.
	records.read(reinterpret_cast<char *>(&person), sizeof(person));
	
	// while not at the end of the file, display the records in the file
	while (!records.eof())
	{
		//Display the record.
		cout << "\n\nName: " << person.name << endl;
		cout << "Address: " << person.address << endl;
		cout << "City: " << person.city << endl;
		cout << "State: " << person.state << endl;
		cout << "Zip: " << person.zip << endl;
		cout << "Phone: " << person.phone << endl;
		cout << "Account Balance: $" << person.acct_balance << endl;
		cout << "Last payment date: " << person.payment_date << endl;
		
		// Read the next record from the file.
		records.read(reinterpret_cast<char *>(&person), sizeof(person));
		
	}
	cout << "\n\nEND OF FILE REACHED.\n";
	records.close();
}








