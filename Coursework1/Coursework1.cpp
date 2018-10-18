// Coursework1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
//#include "Number.h"
#include "Lock.h"
#include <string>
#include <chrono>
#include <vector>

using namespace std;

const string key_file_name = "key.txt";
const string msf_file_name = "multi-safe file.txt";

Number UnlockHashFunction(Number ROOT, Number UHF)
{
	return ROOT + UHF;
}

Number LockHashFunction(Number CN, Number LHF)
{
	return CN + LHF;
}

Number PassHashFunction(Number LN, Number PHF)
{
	return LN + PHF;
}

void RunOneIteration(int i, Number UHF, Number LHF, Number PHF)
{
	srand(i); //2 Generates valid CN. No srand() Generates non valid CN.

	Number ROOT = Number((rand() % 9 + 0), (rand() % 9 + 0), (rand() % 9 + 0), (rand() % 9 + 0));

	for (int i = 0; i < 5; i++)
	{
		cout << "**********" << "LOCK " << i << "************" << endl;

		Number CN = UnlockHashFunction(ROOT, UHF);
		bool validCN = CN.ValidCN();
		cout << (validCN ? "CN is valid. " : "CN is not valid. ");

		Number LN = LockHashFunction(CN, LHF);
		bool validLN = (LN == CN);
		cout << (validLN ? "LN is valid. " : "LN is not valid. ");

		Number HN = PassHashFunction(LN, PHF);
		bool validHN = (HN == ROOT);
		cout << (validHN ? "HN is valid. " : "HN is not valid. ") << endl << endl;

		
	}
	
	
}

bool Validate(bool CN[5], bool LN[5], bool HN[5])
{
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (!CN[i]) count += 1;
		if (!LN[i]) count += 1;
		if (!HN[i]) count += 1;
	}
	if (count > 0) return false;
	else return true;
}

void Write5Locks(int i, Number UHF, Number LHF, Number PHF, ofstream& dataFile);

void Read5Locks(int i, Number ROOT, Number UHF, Number LHF, Number PHF, ofstream& dataFile);

void ParseTextFile(ifstream& readFile, vector<Number>& ROOTS, Number UHF, Number LHF, Number PHF);





int main()
{


	Number UHF, LHF, PHF;
	ofstream dataFile;
	ifstream readFile;

	cout << "How many iterations do you want to run? ";
	int iterations;
	cin >> iterations;
	cout << endl;

	//auto start = chrono::steady_clock::now();

	for (int i = 0; i < iterations; i++)
	{
		Write5Locks(i, UHF, LHF, PHF, dataFile);
	}
	//auto end = chrono::steady_clock::now();

	//cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	

	vector<Number> ROOTS;
	ParseTextFile(readFile, ROOTS, UHF, LHF, PHF);

	for (int i = 0; i < ROOTS.size(); i++)
	{
		Read5Locks(i, ROOTS[i], UHF, LHF, PHF, dataFile);
	}

	

	return 0;
    
}

void Write5Locks(int i, Number UHF, Number LHF, Number PHF, ofstream& dataFile)
{
	srand(i * 2); //7 Generates valid CN. No srand() Generates non valid CN.

	Number ROOT = Number((rand() % 9 + 0), (rand() % 9 + 0), (rand() % 9 + 0), (rand() % 9 + 0));

	Lock locks[5];

	bool validCN[5];
	bool validLN[5];
	bool validHN[5];

	//cout << "Iteration #" << i << endl;

	//cout << "******* Lock 0 *******" << endl;
	locks[0].SetCN(UnlockHashFunction(ROOT, UHF));
	validCN[0] = locks[0].GetCN().ValidCN();
	//cout << (validCN ? "CN is valid. " : "CN is not valid. ");

	locks[0].SetLN(LockHashFunction(locks[0].GetCN(), LHF));
	validLN[0] = (locks[0].GetLN() == locks[0].GetCN());
	//cout << (validLN ? "LN is valid. " : "LN is not valid. ");

	locks[0].SetHN(PassHashFunction(locks[0].GetLN(), PHF));
	validHN[0] = (locks[0].GetHN() == ROOT);
	//cout << (validHN ? "HN is valid. " : "HN is not valid. ") << endl << endl;

	for (int i = 1; i < 5; i++)
	{
		//cout << "******* Lock " << i << " *******" << endl;
		locks[i].SetCN(UnlockHashFunction(locks[i - 1].GetHN(), UHF));
		validCN[i] = locks[i].GetCN().ValidCN();
		//cout << (validCN ? "CN is valid. " : "CN is not valid. ");

		locks[i].SetLN(LockHashFunction(locks[i].GetCN(), LHF));
		validLN[i] = (locks[i].GetLN() == locks[i].GetCN());
		//cout << (validLN ? "LN is valid. " : "LN is not valid. ");

		locks[i].SetHN(PassHashFunction(locks[i].GetLN(), PHF));
		validHN[i] = (locks[i].GetHN() == locks[i - 1].GetHN());
		//cout << (validHN ? "HN is valid. " : "HN is not valid. ") << endl << endl;


	}
	//bool valid = Validate(validCN, validLN, validHN);
	if (Validate(validCN, validLN, validHN))
	{
		dataFile.open(key_file_name.c_str(), std::ios_base::app);
		dataFile << "ROOT " << ROOT << endl;
		dataFile << "UHF " << UHF << endl;
		dataFile << "LHF " << LHF << endl;
		dataFile << "PHF " << PHF << endl;
		dataFile.close();
	}
}

void Read5Locks(int i, Number ROOT, Number UHF, Number LHF, Number PHF, ofstream& dataFile)
{
	//srand(i * 2); //7 Generates valid CN. No srand() Generates non valid CN.

	//Number ROOT = Number((rand() % 9 + 0), (rand() % 9 + 0), (rand() % 9 + 0), (rand() % 9 + 0));

	Lock locks[5];

	bool validCN[5];
	bool validLN[5];
	bool validHN[5];

	//cout << "Iteration #" << i << endl;

	//cout << "******* Lock 0 *******" << endl;
	locks[0].SetCN(UnlockHashFunction(ROOT, UHF));
	validCN[0] = locks[0].GetCN().ValidCN();
	//cout << (validCN ? "CN is valid. " : "CN is not valid. ");

	locks[0].SetLN(LockHashFunction(locks[0].GetCN(), LHF));
	validLN[0] = (locks[0].GetLN() == locks[0].GetCN());
	//cout << (validLN ? "LN is valid. " : "LN is not valid. ");

	locks[0].SetHN(PassHashFunction(locks[0].GetLN(), PHF));
	validHN[0] = (locks[0].GetHN() == ROOT);
	//cout << (validHN ? "HN is valid. " : "HN is not valid. ") << endl << endl;

	for (int i = 1; i < 5; i++)
	{
		//cout << "******* Lock " << i << " *******" << endl;
		locks[i].SetCN(UnlockHashFunction(locks[i - 1].GetHN(), UHF));
		validCN[i] = locks[i].GetCN().ValidCN();
		//cout << (validCN ? "CN is valid. " : "CN is not valid. ");

		locks[i].SetLN(LockHashFunction(locks[i].GetCN(), LHF));
		validLN[i] = (locks[i].GetLN() == locks[i].GetCN());
		//cout << (validLN ? "LN is valid. " : "LN is not valid. ");

		locks[i].SetHN(PassHashFunction(locks[i].GetLN(), PHF));
		validHN[i] = (locks[i].GetHN() == locks[i - 1].GetHN());
		//cout << (validHN ? "HN is valid. " : "HN is not valid. ") << endl << endl;


	}
	//bool valid = Validate(validCN, validLN, validHN);
	dataFile.open(msf_file_name.c_str(), std::ios_base::app);
	dataFile << "NS" << i << ((Validate(validCN, validLN, validHN)) ? " VALID" : " NOT VALID") << endl;

	for (int i = 0; i < 5; i++)
	{
		dataFile << "CN" << i << " " << locks[i].GetCN() << ", LN" << i << " " << locks[i].GetLN() << ", HN" << i << " " << locks[i].GetHN() << endl;
	}
	dataFile.close();
	//cout << (valid ? "VALID!!" : "Not valid") << endl;
}

void ParseTextFile(ifstream& readFile, vector<Number>& ROOTS, Number UHF, Number LHF, Number PHF)
{
	readFile.open(key_file_name);
	if (readFile.is_open())
	{
		string line;
		int lineNumber = 0;
		int a, b, c, d;
		while (getline(readFile, line))
		{
			lineNumber += 1;
			if (line.find("ROOT") != string::npos)
			{
				//numberOfRoots += 1;
				//int a, b, c, d;
				switch (line[5])
				{
				case '+': a = (int)line[6] - 48; break;
				case '-': a = (int)(line[6] - 48)*-1; break;
				}
				switch (line[8])
				{
				case '+': b = (int)line[9] - 48; break;
				case '-': b = (int)(line[9] - 48)*-1; break;
				}
				switch (line[11])
				{
				case '+': c = (int)line[12] - 48; break;
				case '-': c = (int)(line[12] - 48)*-1; break;
				}
				switch (line[14])
				{
				case '+': d = (int)line[15] - 48; break;
				case '-': d = (int)(line[15] - 48)*-1; break;
				}

				ROOTS.push_back(Number(a, b, c, d));
				//cout << "ROOT " << a << b << c << d << endl;



			}
			switch (lineNumber)
			{
			case 2:
				switch (line[4])
				{
				case '+': a = (int)line[5] - 48; break;
				case '-': a = (int)(line[5] - 48)*-1; break;
				}
				switch (line[7])
				{
				case '+': b = (int)line[8] - 48; break;
				case '-': b = (int)(line[8] - 48)*-1; break;
				}
				switch (line[10])
				{
				case '+': c = (int)line[11] - 48; break;
				case '-': c = (int)(line[11] - 48)*-1; break;
				}
				switch (line[13])
				{
				case '+': d = (int)line[14] - 48; break;
				case '-': d = (int)(line[14] - 48)*-1; break;
				}
				UHF = Number(a, b, c, d);
				break;


			case 3:
				switch (line[4])
				{
				case '+': a = (int)line[5] - 48; break;
				case '-': a = (int)(line[5] - 48)*-1; break;
				}
				switch (line[7])
				{
				case '+': b = (int)line[8] - 48; break;
				case '-': b = (int)(line[8] - 48)*-1; break;
				}
				switch (line[10])
				{
				case '+': c = (int)line[11] - 48; break;
				case '-': c = (int)(line[11] - 48)*-1; break;
				}
				switch (line[13])
				{
				case '+': d = (int)line[14] - 48; break;
				case '-': d = (int)(line[14] - 48)*-1; break;
				}
				LHF = Number(a, b, c, d);
				break;

			case 4:
				switch (line[4])
				{
				case '+': a = (int)line[5] - 48; break;
				case '-': a = (int)(line[5] - 48)*-1; break;
				}
				switch (line[7])
				{
				case '+': b = (int)line[8] - 48; break;
				case '-': b = (int)(line[8] - 48)*-1; break;
				}
				switch (line[10])
				{
				case '+': c = (int)line[11] - 48; break;
				case '-': c = (int)(line[11] - 48)*-1; break;
				}
				switch (line[13])
				{
				case '+': d = (int)line[14] - 48; break;
				case '-': d = (int)(line[14] - 48)*-1; break;
				}
				PHF = Number(a, b, c, d);
			}


		}

	}
}

