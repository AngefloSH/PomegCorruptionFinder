// PomegCorruptionFinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int corruptionUnmarked[] = {8, 8, 7, 7, 5, 5, 8, 8, 4, 4, 3, 3, 7, 7, 4, 4, 1, 1, 5, 5, 3, 3, 1, 1};
const int corruptionHeart[] = { 6, 6, 3, 3, 10, 10, 6, 6, 2, 2, 9, 9, 3, 3, 2, 2, 8, 8, 10, 10, 9, 9, 8, 8};
const string natures[] = {	"Hardy", "Lonely", "Brave", "Adamant", "Naughty", 
							"Bold", "Docile", "Relaxed", "Impish", "Lax", 
							"Timid", "Hasty", "Serious", "Jolly", "Naive", 
							"Modest", "Mild", "Quiet", "Bashful", "Rash", 
							"Calm", "Gentle", "Sassy", "Careful", "Quirky" };


string dec2hex(unsigned int number) {
	string result = "";
	int my_number = number;
	while (my_number != 0) {
		int i = my_number & 0xf;
		my_number /= 16;
		if (i < 10) {
			result = string(1, '0' + i) + result;
		}
		else {
			result = string(1, 'a' + i - 10) + result;
		}
	}
	return result;
}

string dec2hex(int number, unsigned int nbBytes) {
	string result = "";
	unsigned int my_number = number;
	while (my_number != 0) {
		int i = my_number & 0xf;
		my_number /= 16;
		if (i < 10) {
			result = string(1, '0' + i) + result;
		}
		else {
			result = string(1, 'a' + i - 10) + result;
		}
	}
	while (result.length() < nbBytes * 2) {
		result = "0" + result;
	}
	return result;
}


string dec2str(int number) {
	string result = "";
	int my_number = number;
	while (my_number != 0) {
		int i = my_number % 10;
		my_number /= 10;
		result = string(1, '0' + i) + result;
	}
	return result;
}

string dec2str(int number, unsigned int nbDigits) {
	string result = "";
	int my_number = number;
	while (my_number != 0) {
		int i = my_number % 10;
		my_number /= 10;
		result = string(1, '0' + i) + result;
	}
	while (result.length() < nbDigits) {
		result = "0" + result;
	}
	return result;
}

// Get chosen corruption Type 
int getCorruptionType() {

	int type = 0;

	cout << "Please choose Corruption type :" << endl << endl;
	cout << "No.\tGrowth read on\tAttacks read on\tEVs & Contest read on\tMiscellaneous read on" << endl;
	cout << "1\tGrowth\t\tEVs\t\tMiscellaneous\t\tAttacks" << endl;
	cout << "2\tGrowth\t\tMiscellaneous\tAttacks\t\t\tEVs" << endl;
	cout << "3\tAttacks\t\tGrowth\t\tMiscellaneous\t\tEVs" << endl;
	cout << "4\tAttacks\t\tEVs\t\tGrowth\t\t\tMiscellaneous" << endl;
	cout << "5\tAttacks\t\tMiscellaneous\tEVs\t\t\tGrowth" << endl;
	cout << "6\tEVs\t\tGrowth\t\tAttacks\t\t\tMiscellaneous" << endl;
	cout << "7\tEVs\t\tAttacks\t\tMiscellaneous\t\tGrowth" << endl;
	cout << "8\tEVs\t\tMiscellaneous\tGrowth\t\t\tAttacks" << endl;
	cout << "9\tMiscellaneous\tGrowth\t\tEVs\t\t\tAttacks" << endl;
	cout << "10\tMiscellaneous\tAttacks\t\tGrowth\t\t\tEVs" << endl;

	cin >> type;
	while (cin.fail() || type > 10 || type < 1) {
		cin.clear();
		cout << endl << "Invalid input, please try again" << endl;
		cin >> type;
	}

	return type;

}

// Get chosen nature if user wants to choose one. This is to choose the nature the user wants to get after corruption.
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

// 
unsigned int rng() {
	static unsigned int value = 0;
	value = value * 0x41c64e6d + 0x6073;
	return value;
}

unsigned int getPID(unsigned int rngValue) {
	unsigned int  result = (rngValue >> 16) & 0xffff;
	result += ((rngValue * 0x41c64e6d + 0x6073) & 0xffff0000);
	return result;
}

unsigned int getIVs(unsigned int rngValue) {
	unsigned int  result = rngValue;
	unsigned int ivs = 0;
	for (int i =0; i<3;i++)
		result = result * 0x41c64e6d + 0x6073;

	ivs = (result & 0xffff0000) + (((result * 0x41c64e6d + 0x6073) >> 16) & 0xffff);

	return ivs;
}




int main()
{
	cout << "\t\t\t\tPomeg Corruption PID Finder v1.0\n\t\t\t\t\tby AngefloSH\n" << endl;


	int natureChoice;
	int nature = 0;
	int corruptionType = getCorruptionType();

	cout << "Are you looking for a specific nature ?\n" << endl;
	cout << "1 : Yes\n2 : No" << endl;

	cin >> natureChoice;
	while (cin.fail() || natureChoice > 2 || natureChoice < 1) {
		cin.clear();
		cout << endl << "Invalid input, please try again" << endl;
		cin >> natureChoice;
	}
	if (natureChoice == 1) nature = getNature();
	else nature = -1;


	// Display the first 100 valid PIDs

	unsigned int rngCall = rng();
	unsigned int pid = getPID(rngCall);
	unsigned int ivs = getIVs(rngCall);
	unsigned int pidShown = 0;
	unsigned int frame = 0;
	const unsigned int pidToShow = 200;

	cout << endl << "There are the first " << pidToShow << " PID available in Emerald with method 2 :" << endl;


	cout << "\t    PID\t\t  Frame\t\tNature\t\tHP / Atk/ Def/ SpA/ SpD/ Spe\tInitiator Caterpie" << endl;
	while (pidShown < pidToShow) {
		frame++;
		int subOrder = pid % 24;
		// Check corruption by adding 0x40000000
		if ((pid >> 30) % 2 == 0) {
			if (((pid + 0x40000000) % 25 == nature || nature == -1) && corruptionUnmarked[subOrder] == corruptionType)
			{
				string strIVs = dec2str((ivs >> 16) & 0x1f, 2) + " / " + dec2str((ivs >> 21) & 0x1f, 2) + " / " + dec2str((ivs >> 26) & 0x1f, 2)
					+ " / " + dec2str((ivs >> 5) & 0x1f, 2) + " / " + dec2str((ivs >> 10) & 0x1f, 2) + " / " + dec2str(ivs & 0x1f, 2);

				cout << pidShown + 1 << ".\t0x" << dec2hex(pid, 4) << "\t Frame " << frame << "\t" << natures[pid % 25] << "\t\t" << strIVs << "\tUnmarked" << endl;
				pidShown++;
			}
		}
		// Check corruption by subtracting 0x40000000
		else {
			if (((pid - 0x40000000) % 25 == nature || nature == -1) && corruptionHeart[subOrder] == corruptionType)
			{
				string strIVs = dec2str((ivs >> 16) & 0x1f, 2) + " / " + dec2str((ivs >> 21) & 0x1f, 2) + " / " + dec2str((ivs >> 26) & 0x1f, 2)
					+ " / " + dec2str((ivs >> 5) & 0x1f, 2) + " / " + dec2str((ivs >> 10) & 0x1f, 2) + " / " + dec2str(ivs & 0x1f, 2);

				cout << pidShown + 1 << ".\t0x" << dec2hex(pid, 4) << "\t Frame " << frame << "\t" << natures[pid % 25] << "\t\t" << strIVs << "\tHeart" << endl;
				pidShown++;
			}
		}

		// Call next frame
		rngCall = rng();
		pid = getPID(rngCall);
		ivs = getIVs(rngCall);

	}

	system("PAUSE");

    return 0;
}

