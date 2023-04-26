/*
Programmer: Christian Penick
Purpose: Store inventory information in a binary file
Date Modified: 05/11/2022
Compiler: MS VC++ 2022
*/

#include <iostream>
#include <fstream>
#include "inventory.h"
using namespace std;

void menu(); // function prototype for menu
int check_input(int choice); // input check
int get_input(); // get user input

int main()
{
	inventory records;
	int choice = 0;

	do
	{
		menu();
		choice = get_input();
		
		switch (choice)
		{
		case 1: // add a new record to the end of the binary file
			system("cls");
			records.addRec();
			break;

		case 2: // show a specific record
			system("cls");
			records.showSpecRec();
			break;

		case 3: // change a record
			records.editRec();
			system("cls");
			break;

		case 4:
			system("cls");
			records.showAllRec();
			break;
		}

	} while (choice != 5);
	
	cout << "Goodbye\n";

	return 0;
}

void menu()
{
	cout << "1. Add a new record" << endl;
	cout << "2. Show a specific record" << endl;
	cout << "3. Change a record" << endl;
	cout << "4. Show all records" << endl;
	cout << "5. Exit" << endl;
}

int check_input(int choice) // This function makes sure the value is between 1 - 3
{
	int foo = choice;
	while (foo < 1 || foo > 5)
	{
		cout << "Must must be between 1 and 5: ";
		cin >> choice;
		foo = choice;
		cin.clear();
		cin.ignore(100, '\n');
	}
	return foo;
}

int get_input()// get user input
{
	int choice;
	cout << "What would you like to do? ";
	cin >> choice;
	cin.clear();
	cin.ignore(100, '\n');
	return check_input(choice);
}