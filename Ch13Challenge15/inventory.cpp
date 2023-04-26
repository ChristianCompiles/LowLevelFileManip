#include "inventory.h"
using namespace std;

void inventory::showSpecRec()
{
	cout << "Which record do you want to view? ";
	cin >> recNum;

	inventories.open("inventory.dat", ios::in | ios::binary);

	if (!inventories)
	{
		cout << "Error opening file\n";
		cin.ignore();
		cin.get();
		exit(1);
	}

	long len_file = (long)inventories.seekg(0, ios::end).tellg();
	int amount_records = len_file / (int)sizeof(record);
	
	while (recNum > amount_records)
	{
		cout << "There are only " << amount_records << " records.\n";
		cout << "Please enter a valid record\n";
		cin >> recNum;
	}

	inventories.seekg((recNum - 1) * sizeof(record), ios::beg);
	if (!inventories.eof())
	{
		cout << "Here is item " << recNum << ":\n";
		inventories.read(reinterpret_cast<char*> (&record), sizeof(record));
		cout << "Item Description: " << record.dscrp << endl;
		cout << "Quantity: " << record.quantity << endl;
		cout << "Wholesale Cost: $" << record.wholesale_cost << endl;
		cout << "Retail Cost: $" << record.retail_cost << endl;
		cout << "Date Added: " << record.date << endl;
	}
	inventories.close();
	cout << endl;
}

void inventory::addRec() // add to the end of the binary file
{
	string input;
	char response = 0;

	inventories.open("inventory.dat", ios::out | ios::app | ios::binary);
	if (!inventories)
	{
		cout << "Error Opening File.\n";
		cin.ignore();
		cin.get();
		exit(1);
	}

	do
	{
		cin.ignore();
		cout << "Enter inventory information:\n";
		cout << "Item Description: ";
		getline(cin, input);

		if (input.length() >= CHAR_SIZE)
		{
			cout << "Description must be less than 21 characters.\n";
			continue;
		}

		strcpy_s(record.dscrp, input.c_str());

		cout << "Quantity: ";
		cin >> record.quantity;

		cout << "Wholesale Cost: $";
		cin >> record.wholesale_cost;

		cout << "Retail Cost: $";
		cin >> record.retail_cost;

		cout << "Date Added (in form xx/xx/xxxx): ";
		cin.ignore();
		getline(cin, input);
		while (input.length() >= CHAR_SIZE)
		{
			cout << "Date must be less than 21 characters.\n";
			getline(cin, input);
		}
		strcpy_s(record.date, input.c_str());

		inventories.write(reinterpret_cast<char*> (&record), sizeof(record));

		cout << "Do you want to enter another record? ";
		cin >> response;
		cin.ignore();
	} while (toupper(response) == 'Y');

	inventories.close();
	cout << endl;
}

void inventory::showAllRec()
{
	char response;

	inventories.open("inventory.dat", ios::in | ios::binary);
	if (!inventories)
	{
		cout << "Error Opening File.\n";
		cin.ignore();
		cin.get();
		exit(1);
	}
	cout << "Here are the records of the file: \n\n";

	// Read one structure at a time and print to screen
	inventories.read(reinterpret_cast<char*> (&record), sizeof(record));

	while (!inventories.eof())
	{
		cout << "Item Description: " << record.dscrp << endl;
		cout << "Quantity: " << record.quantity << endl;
		cout << "Wholesale Cost: $" << record.wholesale_cost << endl;
		cout << "Retail Cost: $" << record.retail_cost << endl;
		cout << "Date Added: " << record.date << endl;

		cout << "\nStrike any key to see the next item in inventory.\n";
		cin.ignore();
		cin.get(response);
		inventories.read(reinterpret_cast<char*> (&record), sizeof(record));
	}

	cout << "That is all the information in the file!\n";
	inventories.close();
}

void inventory::editRec()
{
	string input;
	inventories.clear();

	inventories.open("inventory.dat", ios::in | ios::out | ios::binary);
	if (!inventories)
	{
		cout << "Error Opening File.\n";
		cin.ignore();
		cin.get();
		exit(1);
	}
	// Move to the desired record and read it into record
	cout << "Which record do you want to edit? ";
	cin >> recNum;

	inventories.seekg((recNum - 1) * sizeof(record), ios::beg);
	inventories.read(reinterpret_cast<char*> (&record), sizeof(record));

	cout << "Item Description: " << record.dscrp << endl;
	cout << "Quantity: " << record.quantity << endl;
	cout << "Wholesale Cost: $" << record.wholesale_cost << endl;
	cout << "Retail Cost: $" << record.retail_cost << endl;
	cout << "Date Added: " << record.date << endl;

	cout << "ENTER THE NEW DATA\n";

	cout << "Item Description: ";
	cin >> record.dscrp;

	cout << "Quantity: ";
	cin >> record.quantity;

	cout << "Wholesale Cost: $";
	cin >> record.wholesale_cost;

	cout << "Retail Cost: $";
	cin >> record.retail_cost;

	cout << "Date Added (in form xx/xx/xxxx): ";
	cin.ignore();
	getline(cin, input);
	strcpy_s(record.date, input.c_str());

	// move to the correct place in file and write the record
	inventories.seekp((recNum - 1) * sizeof(record), ios::beg);
	inventories.write(reinterpret_cast<char*> (&record), sizeof(record));

	// close the file
	inventories.close();
	cout << endl;
}
