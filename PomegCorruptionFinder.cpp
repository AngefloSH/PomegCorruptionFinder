// PomegCorruptionFinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// Get chosen corruption Type 
int getCorruptionType() {

	int type = 0;

	cout << "Please choose Corrution type :" << endl << endl;
	cout << "No.\tGrowth read on\tAttacks read on\tEVs & Contest read on\tMiscellaneous read on" << endl;
	cout << "1\tGrowth\t\tEVs\t\tMiscellaneous\t\tAttacks" << endl;
	cout << "2\tGrowth\t\tMiscellaneous\tAttacks\t\t\tEVs" << endl;
	cout << "3\tAttacks\t\tGrowth\t\tMiscellaneous\t\tEVs" << endl;
	cout << "4\tAttacks\t\tEVs\t\tGrowth\t\t\tAttacks" << endl;
	cout << "5\tAttacks\t\tMiscellaneous\tEVs\t\t\tAttacks" << endl;
	cout << "6\tEVs\t\tGrowth\t\tAttacks\t\t\tAttacks" << endl;
	cout << "7\tEVs\t\tAttacks\t\tMiscellaneous\t\tAttacks" << endl;
	cout << "8\tEVs\t\tMiscellaneous\tGrowth\t\t\tAttacks" << endl;
	cout << "9\tMiscellaneous\tGrowth\t\tEVs\t\t\tAttacks" << endl;
	cout << "10\tMiscellaneous\tAttacks\t\tGrowth\t\t\tAttacks" << endl;

	cin >> type;
	while (cin.fail() || type > 10 || type < 1) {
		cin.clear();
		cout << endl << "Invalid input, please try again" << endl;
		cin >> type;
	}

	return type;

}

int getNature() {
	int nature;

	cout << "Please choose a nature :" << endl << endl;
	cout << " 0 : Hardy\t 1 : Lonely\t 2 : Brave\t 3 : Adamant\t 4 : Naughty" << endl;
	cout << " 5 : Bold\t 6 : Docile\t 7 : Relaxed\t 8 : Impish\t 9 : Lax" << endl;
	cout << "10 : Timid\t11 : Hasty\t12 : Serious\t13 : Jolly\t14 : Naive" << endl;
	cout << "15 : Modest\t16 : Mild\t17 : Quiet\t18 : Bashful\t19 : Rash" << endl;
	cout << "20 : Calm\t21 : Gentle\t22 : Sassy\t23 : Careful\t24 : Quirky" << endl;

	cin >> nature;
	while (cin.fail() || nature > 24 || nature < 0) {
		cin.clear();
		cout << endl << "Invalid input, please try again" << endl;
		cin >> nature;
	}

	return nature;

}



int main()
{
	int natureChoice;
	int nature = 0;
	int corruptionType = getCorruptionType();

	cout << "Are you looking for a specific nature ?" << endl << endl;
	cout << "1 : Yes\n2 : No" << endl;

	cin >> natureChoice;
	while (cin.fail() || natureChoice > 2 || natureChoice < 1) {
		cin.clear();
		
		cout << endl << "Invalid input, please try again" << endl;
		cin >> natureChoice;
	}
	if (natureChoice == 1) nature = getNature();
	else nature = -1;




    return 0;
}

