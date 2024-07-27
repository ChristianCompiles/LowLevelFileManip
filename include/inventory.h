#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

const int CHAR_SIZE = 21;

class inventory
{
private:
	struct mystruct
	{
		char dscrp[CHAR_SIZE];
		int quantity;
		float wholesale_cost;
		float retail_cost;
		char date[CHAR_SIZE];
	};

	mystruct record;
	long recNum;
	fstream inventories;

public:

	inventory() : record(){recNum = 0;}
	void showSpecRec(); // show a specific record
	void addRec(); // add to the end of the binary file
	void showAllRec(); // show all the records in the file
	void editRec(); // edit a specific record
};
