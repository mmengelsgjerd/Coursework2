// Coursework1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>

#include "MultiLock.h"
#include "Set.h"

using namespace std;

const string KEY_FILE = "key.txt";
const string MSF_FILE = "multi-safe file.txt";
const string LOCKED_FILE = "locked safe file.txt";
const string KEY_FILE_C2 = "key c2.txt";
const string MSF_FILE_C2 = "multi-safe file c2.txt";
int safeSize = 0;


void Coursework1(int validSolWanted, vector<Set>& goodROOTS, HashKey UHF, HashKey LHF, HashKey PHF, ofstream& dataFile, ifstream& readFile, vector<Set>& foundROOTS, vector<MultiLock>& locksHolder);

Digits<int> UnlockHashFunctionRoot(Root ROOT, HashKey UHF) {return ROOT + UHF;}

Digits<int> UnlockHashFunction(Digits<int> HN, HashKey UHF) {return HN + UHF;}

Digits<int>  LockHashFunction(Digits<int> CN, HashKey LHF) {return CN + LHF;}

Digits<int> PassHashFunction(Digits<int> LN, HashKey PHF) {return LN + PHF;}

void CheckLocksMultiSafeFile(int i, vector<Set>& foundROOTS, vector<MultiLock>& locksHolder);

void CheckLocksKeyFile(int& validSol, vector<Set>& goodROOTS, HashKey UHF, HashKey LHF, HashKey PHF);

void ReadTextFile(ifstream& readFile, vector<Set>& findROOTS, string fileName) throw (invalid_argument);

void ParseTextFile(string line, int w, int x, int y, int z, int& a, int& b, int& c, int& d);

void WriteMultiLockFile(ofstream& dataFile, vector<MultiLock>& locksHolder, string fileName) throw (invalid_argument);

void WriteKeyFile(ofstream& dataFile, vector<Set>& ROOTS, string fileName) throw (invalid_argument);

void SetLockValues(MultiLock &locks, Root ROOT, HashKey UHF, HashKey LHF, HashKey PHF);

//Coursework 2

void Coursework2(ifstream& readFile, ofstream& dataFile, vector<MultiLock>& locksHolder, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, vector<Set>& unlockedRoots);

void ReadTextFileC2(ifstream& readFile, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, string keyFileName, string msfFileName) throw (invalid_argument);

void WriteLockFile(ofstream& dataFile, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, string fileName) throw (invalid_argument);

Digits<int> FindHashKey(Digits<int> LNCNHN, Digits<int> rootOrHashKey);

void HackSafe(int i, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, vector<Set>& unlockedRoots, Digits<int> CNCheck);

void PrintRoots(vector<Set> root);


int main()
{
	cout << "Welcome To The Safe Problem Program " << endl;
	char input;
	bool runAgain;

	ofstream dataFile;
	ifstream readFile;
	
	srand((unsigned int)time(NULL));
	HashKey UHF, LHF, PHF;
	Root ROOT;
	clock_t start;

	//Coursework 1 variables 
	vector<MultiLock> locksHolder;
	vector<Root> ROOTS;
	vector<Set> foundROOTS;
	vector<Set> goodROOTS;
	MultiLock locks;

	//Coursework 2 variables
	vector<MultiLock> lockedSafes;
	vector<Root> lockedRoots;
	vector<Set> unlockedRoots;

	do
	{
		cout << "Welcome! Please enter the number corresponding to the option you would like to select from the menu." << endl;
		cout << "1. Run program in its entirity" << endl << "2. Read a key file and generate a multi-safe file" << endl << "3. Print roots" << endl << "Select: ";
		int selection = 0;
		cin >> selection;
		if (selection != 1 && selection != 2 && selection != 3)
		{
			cout << "Please enter a valid selection." << endl;
			runAgain = true;
			break;
		}
		
		if (selection == 1)
		{
			cout << "How many locks do you want the safe to consist of? ";
			cin >> safeSize;

			cout << "How many valid solutions do you need? ";
			int validSolWanted;
			cin >> validSolWanted;
			cout << endl;

			start = clock();
			Coursework1(validSolWanted, goodROOTS, UHF, LHF, PHF, dataFile, readFile, foundROOTS, locksHolder);
			cout << "Reading roots, checking validity of them, and then writing them to multi-safe file took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;

			start = clock();
			Coursework2(readFile, dataFile, locksHolder, lockedSafes, lockedRoots, unlockedRoots);
			cout << "Hacking the safe took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
			
		}
		else if (selection == 2)
		{
			cout << "Enter the name of the key file you would like to generate CN, LN and HN values of: ";
			string fileToRead;
			cin >> fileToRead;
			cout << "Reading roots from key file..." << endl;
			time_t start = clock();
			try {
				ReadTextFile(readFile, foundROOTS, fileToRead);
				safeSize = 5;
				cout << "Checking the roots found in the key file..." << endl;
				for (int i = 0; i < (int)foundROOTS.size(); i++)
				{
					CheckLocksMultiSafeFile(i, foundROOTS, locksHolder);
				}

				cout << "Writing the multi-safe file..." << endl;
				WriteMultiLockFile(dataFile, locksHolder, "new multi-lock file.txt");

				cout << "Reading roots, checking validity of them, and then writing them to multi-safe file took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
			}
			catch (const invalid_argument& ifn) {
				cout << "Unable to read data: " << ifn.what() << endl;
				exit(1);
			}



		}
		else
		{
			PrintRoots(goodROOTS);

		}

		//User friendly loop
		cout << "Would you like to run the program again? (y for Yes/n for No) ";
		cin >> input;
		if (input != 'y' && input != 'Y' && input != 'n' && input != 'N'){ cout << "Invalid input. Terminating..." << endl; runAgain = false;}
		else{ if (input == 'y' || input == 'Y') runAgain = true;
			else { runAgain = false; cout << "Terminating program... Good bye!" << endl;}}
		

	} while (runAgain);
	return 0;

}

void Coursework2(ifstream& readFile, ofstream& dataFile, vector<MultiLock>& locksHolder, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, vector<Set>& unlockedRoots)
{
	try {
		cout << "Reading the key file and multi-safe file to extract roots and LN values..." << endl;
		ReadTextFileC2(readFile, lockedSafes, lockedRoots, KEY_FILE, MSF_FILE);
		cout << "Writing the roots and LN to the locked safe file..." << endl;
		WriteLockFile(dataFile, lockedSafes, lockedRoots, LOCKED_FILE);

		cout << "Hacking the safe..." << endl;
		for (int i = 0; i < (int)lockedRoots.size(); i++)
		{
			Digits<int> CNCheck = locksHolder[i].GetCN(0);
			HackSafe(i, lockedSafes, lockedRoots, unlockedRoots, CNCheck);
		}

		cout << "Writing the key file with the hacked roots and hashkeys..." << endl;
		WriteKeyFile(dataFile, unlockedRoots, KEY_FILE_C2);
		cout << "Writing the multi-lock file with the hacked CN, LN, and HN values..." << endl;
		WriteMultiLockFile(dataFile, lockedSafes, MSF_FILE_C2);
	}
	catch (const invalid_argument& ifn) {
		cout << "Unable to read data: " << ifn.what() << endl;
		exit(1);
	}
	cout << endl << "Hacking complete!" << endl << endl;
	
}

void Coursework1(int validSolWanted,  vector<Set>& goodROOTS, HashKey UHF, HashKey LHF, HashKey PHF, ofstream& dataFile, ifstream& readFile, vector<Set>& foundROOTS, vector<MultiLock>& locksHolder)
{
	int validSol = 0;

	

	cout << "Finding solutions..." << endl;
	//Find solutions
	int iterations = 0;
	while (validSol < validSolWanted)
	{
		CheckLocksKeyFile(validSol, goodROOTS, UHF, LHF, PHF);
		iterations += 1;
		if (iterations > 10000)
		{
			cout << "Currently " << validSol << " valid solutions have been found.\nAfter 10 000 iterations the hash keys have been regenerated.\n";
			iterations = 0;
			UHF = HashKey();
			LHF = HashKey();
			PHF = HashKey();
		}
	}

	//Write solutions key file
	try {
		cout << "Writing solutions to key file..." << endl;
		WriteKeyFile(dataFile, goodROOTS, KEY_FILE);
		
		cout << "Reading roots from key file..." << endl;
		ReadTextFile(readFile, foundROOTS, KEY_FILE);

		cout << "Checking the roots found in the key file..." << endl;
		for (int i = 0; i < (int)foundROOTS.size(); i++)
		{
			CheckLocksMultiSafeFile(i, foundROOTS, locksHolder);
		}

		cout << "Writing the multi-safe file..." << endl;
		WriteMultiLockFile(dataFile, locksHolder, MSF_FILE);
	}
	catch (const invalid_argument& ifn)
	{
		cout << "Unable to read data: " << ifn.what() << endl;
		exit(1);
	}

}

void PrintRoots(vector<Set> root)
{
	for_each(root.begin(), root.end(), [](Set r) {cout << r.GetROOT() << "\n"; });
}

void HackSafe(int i, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, vector<Set>& unlockedRoots, Digits<int> CNCheck)
{
	bool found = false;
	HashKey UHF2;// = HashKey(-9, 0, -9, 0);
	HashKey LHF2, PHF2;
	Digits<int> CN0;
	Digits<int> HN0;
	int iterations = 0;
	while (!found)
	{
		CN0 = UnlockHashFunctionRoot(lockedRoots[i], UHF2);
		if ((CN0.GetA() == CNCheck.GetA()) && (CN0.GetB() == CNCheck.GetB()) && (CN0.GetC() == CNCheck.GetC()) && (CN0.GetD() == CNCheck.GetD()))
		{
			found = true;
		}
		else
		{
			UHF2 = HashKey();
		}
		iterations += 1;
	}

	lockedSafes[i].SetCN(CN0);
	Digits<int> difference = lockedSafes[i].GetLN(1) - lockedSafes[i].GetLN(0);
	for (int j = 1; j < safeSize; j++)
	{
		Digits<int> prevCN = lockedSafes[i].GetCN(j - 1);
		Digits<int> currentCN = prevCN + difference;
		lockedSafes[i].SetCN(currentCN);
	}

	Digits<int> tempUHF = FindHashKey(CN0, lockedRoots[i]);
	UHF2 = HashKey(tempUHF.GetA(), tempUHF.GetB(), tempUHF.GetC(), tempUHF.GetD());

	HN0 = lockedSafes[i].GetCN(1) - UHF2;
	lockedSafes[i].SetHN(HN0);

	for (int k = 1; k < safeSize; k++)
	{
		Digits<int> prevHN = lockedSafes[i].GetHN(k - 1);
		Digits<int> currentHN = prevHN + difference;
		lockedSafes[i].SetHN(currentHN);
	}

	Digits<int> tempLHF = FindHashKey(lockedSafes[i].GetLN(0), CN0);
	LHF2 = HashKey(tempLHF.GetA(), tempLHF.GetB(), tempLHF.GetC(), tempLHF.GetD());

	Digits<int> tempPHF = FindHashKey(lockedSafes[i].GetHN(0), lockedSafes[i].GetLN(0));
	PHF2 = HashKey(tempPHF.GetA(), tempPHF.GetB(), tempPHF.GetC(), tempPHF.GetD());

	unlockedRoots.push_back(Set(UHF2, LHF2, PHF2, lockedRoots[i]));
}

Digits<int> FindHashKey(Digits<int> LNCNHN, Digits<int> rootOrHashKey)
{
	int a = LNCNHN.GetA() - rootOrHashKey.GetA(); if (a > 0) a -= 10;
	int b = LNCNHN.GetB() - rootOrHashKey.GetB(); if (b < 0) b += 10;
	int c = LNCNHN.GetC() - rootOrHashKey.GetC(); if (c > 0) c -= 10;
	int d = LNCNHN.GetD() - rootOrHashKey.GetD(); if (d < 0) d += 10;
	return Digits<int>(a,b,c,d);
}

void WriteLockFile(ofstream& dataFile, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, string fileName) throw (invalid_argument)
{
	dataFile.open(fileName.c_str());//, std::ios_base::app);
	if (dataFile.fail()) throw invalid_argument("no file exists" + KEY_FILE);

	dataFile << "NL " << (int)lockedSafes.size() << "\n";

	for (int i = 0; i < (int)lockedSafes.size(); i++)
	{
		dataFile << "ROOT " << lockedRoots[i].GetA() << lockedRoots[i].GetB() << lockedRoots[i].GetC() << lockedRoots[i].GetD() << "\n";
		
		for (int j = 0; j < safeSize; j++)
		{
			dataFile << "LN" << j << " " << lockedSafes[i].GetLN(j).GetA() << lockedSafes[i].GetLN(j).GetB() << lockedSafes[i].GetLN(j).GetC() << lockedSafes[i].GetLN(j).GetD() << "\n";
		}
		dataFile << "\n";
	}

	dataFile.close();
}

void ReadTextFileC2(ifstream& readFile, vector<MultiLock>& lockedSafes, vector<Root>& lockedRoots, string keyFileName, string msfFileName) throw (invalid_argument)
{
	MultiLock lockedLocks;
	//Read roots
	readFile.open(keyFileName);
	if (readFile.fail()) throw invalid_argument("no file exists" + KEY_FILE);
	if (readFile.is_open())
	{
		Root ROOT = Root(0, 0, 0, 0);
		string line;
		int lineNumber = 0;

		while (getline(readFile, line))
		{
			if (lineNumber != 0)
			{
				if (lineNumber % 4 == 1)
				{
					ROOT = Root(((int)line[5] - 48), ((int)line[6] - 48), ((int)line[7] - 48), ((int)line[8] - 48));
					lockedRoots.push_back(ROOT);
				}
			}
			lineNumber += 1;
		}
	}
	readFile.close();

	//Read LNs
	//Digits<int> LN[5];// = { Digits<int>(0,0,0,0) };
	vector<Digits<int> > LN;

	readFile.open(msfFileName);
	if (readFile.fail()) throw invalid_argument("no file exists" + KEY_FILE);
	if (readFile.is_open())
	{
		string line;
		int lineNumber = 0;
		while (getline(readFile, line))
		{
			if (line.find("LN") != string::npos)
			{
				//LN[lineNumber] = { (int)(line[14]-48), (int)(line[15]-48), (int)(line[16]-48), (int)(line[17]-48) };
				if (lockedLocks.GetLNSize() < 10) lockedLocks.SetLN(Digits<int>((int)(line[14] - 48), (int)(line[15] - 48), (int)(line[16] - 48), (int)(line[17] - 48)));
				else lockedLocks.SetLN(Digits<int>((int)(line[16] - 48), (int)(line[17] - 48), (int)(line[18] - 48), (int)(line[19] - 48)));
				lineNumber += 1; 
				if (lineNumber > (safeSize-1))
				{
					lockedSafes.push_back(lockedLocks);
					lockedLocks.ClearLN();
					lineNumber = 0;
				}

			}
			
		}
	}
	readFile.close();
	
	
}

void ReadTextFile(ifstream& readFile, vector<Set>& findROOTS, string fileName) throw (invalid_argument)
{
	readFile.open(fileName);
	if (readFile.fail()) throw invalid_argument("no file exists" + KEY_FILE);
	if (readFile.is_open())
	{
		Root ROOT = Root(0, 0, 0, 0);
		HashKey UHF = HashKey(0, 0, 0, 0);
		HashKey LHF = HashKey(0, 0, 0, 0);
		HashKey PHF = HashKey(0, 0, 0, 0);

		string line;
		int lineNumber = 0;
		int a, b, c, d;

		while (getline(readFile, line))
		{
			if (lineNumber != 0)
			{	
				if (lineNumber % 4 == 1)
				{
					ROOT = Root(((int)line[5] - 48), ((int)line[6] - 48), ((int)line[7] - 48), ((int)line[8] - 48));
				}
				else if (lineNumber % 4 == 2)
				{
					ParseTextFile(line, 4, 7, 10, 13, a, b, c, d);
					UHF = HashKey(a, b, c, d);
				}
				else if (lineNumber % 4 == 3)
				{
					ParseTextFile(line, 4, 7, 10, 13, a, b, c, d);
					LHF = HashKey(a, b, c, d);
				}
				else
				{
					ParseTextFile(line, 4, 7, 10, 13, a, b, c, d);
					PHF = HashKey(a, b, c, d);
				}
			}
			if (lineNumber % 4 == 0 && lineNumber != 0)
			{
				findROOTS.push_back(Set(UHF, LHF, PHF, ROOT));
			}
			lineNumber += 1;
		}
	}
	readFile.close();
}

void ParseTextFile(string line, int w, int x,int y, int z, int& a, int& b, int& c, int& d)
{ 

	if (line[w] == '+') a = (int)(line[w + 1] - 48);
	else a = (int)((line[w + 1] - 48)*-1);

	if (line[x] == '+') b = (int)(line[x + 1] - 48);
	else b = (int)((line[x + 1] - 48)*-1);

	if (line[y] == '+') c = (int)(line[y + 1] - 48);
	else c = (int)((line[y + 1] - 48)*-1);

	if (line[z] == '+') d = (int)(line[z + 1] - 48);
	else d = (int)((line[z + 1] - 48)*-1);
	
}

void WriteKeyFile(ofstream& dataFile, vector<Set>& ROOTS, string fileName) throw (invalid_argument)
{
	dataFile.open(fileName.c_str());//, std::ios_base::app);
	if (dataFile.fail()) throw invalid_argument("no file exists" + KEY_FILE);

	dataFile << "NS " << ROOTS.size() << endl;
	for (int i = 0; i < (int)ROOTS.size(); i++) {
		Root CurrentRoot = ROOTS[i].GetROOT();
			 
		dataFile << "ROOT " << CurrentRoot.GetA() << CurrentRoot.GetB() << CurrentRoot.GetC() << CurrentRoot.GetD() << "\n";
		dataFile << "UHF " << ROOTS[i].GetUHF() << "\n";
		dataFile << "LHF " << ROOTS[i].GetLHF() << "\n";
		dataFile << "PHF " << ROOTS[i].GetPHF() << "\n";
	}
	dataFile.close();
}

void WriteMultiLockFile(ofstream& dataFile, vector<MultiLock>& locksHolder, string fileName) throw (invalid_argument)
{
	dataFile.open(fileName.c_str());//, std::ios_base::app);
	if (dataFile.fail()) throw invalid_argument("no file exists" + KEY_FILE);

	dataFile << "NS" << (int)locksHolder.size() << " VALID" << "\n";
	for (int i = 0; i < (int)locksHolder.size(); i++)
	{
		for (int j = 0; j < safeSize; j++)
		{
			dataFile << "CN" << j << " " << locksHolder[i].GetCN(j).GetA() << locksHolder[i].GetCN(j).GetB() << locksHolder[i].GetCN(j).GetC() << locksHolder[i].GetCN(j).GetD()
				<< ", LN" << j << " " << locksHolder[i].GetLN(j).GetA() << locksHolder[i].GetLN(j).GetB() << locksHolder[i].GetLN(j).GetC() << locksHolder[i].GetLN(j).GetD()
				<< ", HN" << j << " " << locksHolder[i].GetHN(j).GetA() << locksHolder[i].GetHN(j).GetB() << locksHolder[i].GetHN(j).GetC() << locksHolder[i].GetHN(j).GetD() << "\n";
		}
		dataFile << "\n";
	}
	
	
	dataFile.close();

}

void CheckLocksMultiSafeFile(int i, vector<Set>& foundROOTS, vector<MultiLock>& locksHolder)
{
	MultiLock locks;
	
	Root ROOT = foundROOTS[i].GetROOT();
	HashKey UHF = foundROOTS[i].GetUHF();
	HashKey LHF = foundROOTS[i].GetLHF();
	HashKey PHF = foundROOTS[i].GetPHF();

	SetLockValues(locks, ROOT, UHF, LHF, PHF);

	if (locks.Validate(safeSize)) locksHolder.push_back(locks);
}

void CheckLocksKeyFile(int& validSol, vector<Set>& goodROOTS, HashKey UHF, HashKey LHF, HashKey PHF)
{

	Root ROOT;
	MultiLock locks;

	SetLockValues(locks, ROOT, UHF, LHF, PHF);

	if (locks.Validate(safeSize))
	{
		validSol += 1;
		goodROOTS.push_back(Set(UHF, LHF, PHF, ROOT));
	}
	
}

void SetLockValues(MultiLock &locks, Root ROOT, HashKey UHF, HashKey LHF, HashKey PHF)
{
	locks.SetCN(UnlockHashFunctionRoot(ROOT, UHF));
	locks.SetValidCN(locks.GetCN(0).ValidCN());

	locks.SetLN(LockHashFunction(locks.GetCN(0), LHF));
	locks.SetValidLN(locks.GetLN(0) == locks.GetCN(0));

	locks.SetHN(PassHashFunction(locks.GetLN(0), PHF));
	locks.SetValidHN((locks.GetHN(0) == ROOT));

	for (int i = 1; i < safeSize; i++)
	{
		locks.SetCN(UnlockHashFunction(locks.GetHN(i - 1), UHF));
		locks.SetValidCN(locks.GetCN(i).ValidCN());

		locks.SetLN(LockHashFunction(locks.GetCN(i), LHF));
		locks.SetValidLN((locks.GetLN(i) == locks.GetCN(i)));

		locks.SetHN(PassHashFunction(locks.GetLN(i), PHF));
		locks.SetValidHN((locks.GetHN(i)) == (locks.GetHN(i - 1)));
	}
}


