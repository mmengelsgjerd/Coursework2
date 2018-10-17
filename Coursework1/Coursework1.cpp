// Coursework1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
//#include "Number.h"
#include "Lock.h"

using namespace std;

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

void RunOneIteration5Locks(int i, Number UHF, Number LHF, Number PHF)
{
	srand(i*2); //7 Generates valid CN. No srand() Generates non valid CN.

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

		/*if (validCN && validLN && validHN)
		{
			//cout << "After being hashed these are the following ROOT, CN, LN and HN value!" << endl << endl;
			cout << endl << "ROOT = " << ROOT << endl;
			cout << endl << "UHF = " << UHF << endl;
			//cout << endl << "LHF = " << LN << endl;
			//cout << endl << "PHF = " << HN << endl << endl;
		}*/

	}
	bool valid = Validate(validCN, validLN, validHN);
	if (valid)
	{
		cout << "******* Lock " << i << " *******" << endl;
		cout << "VALID!!" << endl;
	}
		//cout << (valid ? "VALID!!" : "Not valid") << endl;
}



int main()
{


	Number UHF, LHF, PHF;

	
	
	
	cout << "How many iterations do you want to run? ";
	int iterations;
	cin >> iterations;
	cout << endl;

	for (int i = 0; i < iterations; i++)
	{
		RunOneIteration5Locks(i, UHF, LHF, PHF);
	}

	

	return 0;
    
}




