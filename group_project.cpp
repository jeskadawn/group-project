// Group project

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstring>
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
int searchAndDisplay(Customer);
int searchAndDelete(Customer);
int searchAndChange(Customer);
void showRecord(Customer);
int displayContents(Customer);

int main()
{
	int choice;						// To hold the menu choice.
	char again = 'N';				
	
	Customer person;				// Instance of Customer struct.
	
	do
	{
		// Display menu
		displayMenu();
	
		//Get menu choice
		choice = getMenuChoice();
	
		
		switch(choice)
		{
			case 1: enterRecords(person);			// Allow user to enter a record.
					break;
					
			case 2: searchAndDisplay(person);		// Allow user to search for and display a record.
					break;
					
			case 3: searchAndDelete(person);		// Allow user to search for and delete a record.
					break;
					
			case 4: searchAndChange(person);		// Allow user to search for and change a record.
					break;
			
			case 5: displayContents(person);		// Displays all of the file's contents.
					break;
			
			case 6: cout << "Quitting program...";	// Terminates the program
					return 0;
					
			default: cout << "That is an invalid choice.\n";
		}

		// Ask if user wants to display the menu again.
		cout << "\n\nDisplay menu again? Y or N: ";
		cin >> again;
		
		while (again != 'Y' && again != 'y' && again != 'N' && again != 'n')	// Input validation
		{
			cout << "Error. Please type either a Y or N: ";
			cin >> again;
		}
		cin.ignore(); 	// Skip over the remaning newline	
	} while (toupper(again) == 'Y');
	
	
	
	cout << "Program terminating...";
	
	
	
	return 0;
}


//********************************************
// 		displayMenu function
// This function displays a menu for the user.
//********************************************

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
// 		getMenuChoice function
// This function gets the menu choice 
// from the user.
//***************************************

int getMenuChoice()
{
	int choice;						// To hold the choice.
	
	
	cout << "\nMenu choice: ";
	cin >> choice;
	cin.ignore();
	
	while (choice < 1 || choice > 6)		//Input validation
	{
		cout << "Error. Please enter a choice between 1 and 6: ";
		cin >> choice;	
	}
	
	return choice;	
}

//***************************************
// 		enterRecord function
// This function allows the user to enter
// a whole new record for the file.
//***************************************

int enterRecords(Customer person)
{
	char again;				// To hold the user's choice for entering another record.
	
	//Open a file for binary output.
	fstream records("records.dat", ios::out | ios::app | ios::binary);
	
	// Test for errors
	if (!records)
	{
		cout << "Error opening file. Program aborting.\n";
		return 0; 		// If there are issues opening the file, this will cause the function to stop.
	}
	
	do
	{
		//Get data about a person
		cout << "Enter the following data about a person:\n";
		
		cout << "Name: ";
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
		while (again != 'Y' && again != 'y' && again != 'N' && again != 'n')		// Input validation
		{
			cout << "Error. Please type either a Y or N: ";
			cin >> again;
		}
		cin.ignore(); 	// Skip over the remaning newline
		
	} while (toupper(again) == 'Y');
	
	// Close the file
	records.close();
	
}

//*****************************************************************
// 		searchName function
// This function asks the user for a name to search in the file. 
// This function returns the position (pos) of the record if found.
// It returns a -1 if not found.
//******************************************************************

int searchName(Customer person)
{
	char name[NAME_SIZE];			// To hold the name that the user wants to search for.
	bool found = false;				// Flag 
	int pos = 0;					// To hold the name's position.
	
	//Open the file
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
	cin.getline(name, NAME_SIZE);
	
	// Read the first record from the file
	records.read(reinterpret_cast<char *>(&person), sizeof(person));
	
	while (!records.eof())
	{
		// Compare the user entered name to the name of the current record
		
		if (strcmp(person.name, name) == 0)
		{
			found = true;			// If name is found in file, set flag to true
			break;					// and break out of loop.
		}
		
		// If name wasn't found in the first record.......
		// Read the next record from the file.
		records.read(reinterpret_cast<char *>(&person), sizeof(person));
		
		// Increment pos
		pos++;

	}
	
	// Close the file
	records.close();
	
	if (found == true)				// If the name was found...
	{
		cout << "Record found for " << name << ". Record #" << pos + 1 << endl;
	}
	else if (found == false)		// If the name was not found
	{
		cout << "No record found for " << name << endl;
		pos = -1;					//Set pos to -1
	}
	
	//Return the position in the file the name was found at, or a -1 if the name was not found.
	cout << "pos is: " << pos << endl;
	return pos;
}

//*************************************************
// searchAndDisplay function
// This function will call the searchName function.
// Then it will display the record that was found.
//*************************************************

int searchAndDisplay(Customer person)
{
	long recNum;					// To hold a record number
	
	cout << "***SEARCH AND DISPLAY***" << endl;
	// Call the searchName function and assign it to recNum
	recNum = searchName(person);
	
	if (recNum == -1)	// If name was not found, break out of this function
	{
		return 0;
	}
	
	// Open the file
	fstream records;
	records.open("records.dat", ios::in | ios::binary);
	
	//Test for errors
	if (!records)
	{
		cout << "Error opening file. Program aborting.\n";
		return 0;
	}
	
	//Move to the record and read it
	records.seekg(recNum * sizeof(person), ios::beg);
	records.read(reinterpret_cast<char *>(&person), sizeof(person));
	
	//Display it by calling showRecord
	showRecord(person);
	
	//Close file
	records.close();
}

//**************************************************
// searchAndChange function
// This function will call the searchName function.
// Then it will allow the user to change the record.
//**************************************************

int searchAndChange(Customer person)
{
	long recNum;					// To hold a record number
	
	cout << "***SEARCH AND CHANGE***" << endl;
	// Call the searchName function and assign it to recNum
	recNum = searchName(person);
	
	if (recNum == -1)	// If name was not found, break out of this function
	{
		return 0;
	}
	
	// Open the file
	fstream records;
	records.open("records.dat", ios::in | ios::out | ios::binary);
	
	//Test for errors
	if (!records)
	{
		cout << "Error opening file. Program aborting.\n";
		return 0;
	}
	
	//Move to the record and read it
	records.seekg(recNum * sizeof(person), ios::beg);
	records.read(reinterpret_cast<char *>(&person), sizeof(person));
	
	//Display it by calling showRecord
	showRecord(person);
	
	//Get the new record data.
	cout << "\nENTER NEW DATA: \n";
	
	cout << "Name: ";
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
	
	//Move back to the beginning of this record's position.
	records.clear();
	records.seekp(recNum * sizeof(person), ios::beg);
	
	//Write the new record over the current record.
	records.write(reinterpret_cast<char *>(&person), sizeof(person));
	
	//Close the file
	records.close();
	
}

//**********************************************
// searchAndDelete function
//
//**********************************************

int searchAndDelete(Customer person)
{
	long recNum;					// To hold a record number
	int count = 0;
	
	cout << "***SEARCH AND DELETE***" << endl;
	// Call the searchName function and assign it to recNum
	recNum = searchName(person);
	
	if (recNum == -1)	// If name was not found, break out of this function
	{
		return 0;
	}
	
	// Open two files
	fstream tempFile;						//Temp file
	tempFile.open("temp.dat", ios::out | ios::binary);
	
	fstream records;						//Premade records.dat file
	records.open("records.dat", ios::in | ios::binary);
	
	//Test for errors
	if (!records)
	{
		cout << "Error opening file. Program aborting.\n";
		return 0;
	}
	
	int deleteLocation = recNum * sizeof(person);
	
//	//Move to the record and read it
//	records.seekg(recNum * sizeof(person), ios::beg);
//	records.read(reinterpret_cast<char *>(&person), sizeof(person));
	
	while(!records.eof())
	{
		if(deleteLocation != ((count) * sizeof(person)))
		{
			records.seekg((count) * sizeof(person), ios::beg);
			records.read(reinterpret_cast<char *>(&person), sizeof(person));
			tempFile.write(reinterpret_cast<char*>(&person), sizeof(person));
			count++;
		}
	}
	
	tempFile.close();
	records.close();
	remove("records.dat");
	rename("tempFile.dat", "records.dat");
}


//*******************************************
// showRecord function
// This function formats the results of the
// read record and displays it properly for
// being read by the user.
//*******************************************

void showRecord(Customer person)
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
}


//*****************************************************
// 				displayContents function
// This function will display the entire contents
// of the binary file.
//*****************************************************

int displayContents(Customer person)
{
	// Open the file
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
		showRecord(person);
		
		// Read the next record from the file.
		records.read(reinterpret_cast<char *>(&person), sizeof(person));
		
	}
	cout << "\n\nEND OF FILE REACHED.\n";
	records.close();
}



