#pragma once
//#include "LockDigit.h"
#include "Digits.h";



class MultiLock {


public:
	MultiLock();
	~MultiLock();
	void SetCN(Digits arg, int i);
	void SetLN(Digits arg, int i);
	void SetHN(Digits arg, int i);

	void SetValidCN(bool arg, int i);
	void SetValidLN(bool arg, int i);
	void SetValidHN(bool arg, int i);

	bool IsValidCN(int i);
	bool IsValidLN(int i);
	bool IsValidHN(int i);
	
	bool Validate();
	bool SumToLeftLess();

	Digits GetCN(int i);
	Digits GetLN(int i);
	Digits GetHN(int i);

	friend bool operator < (MultiLock& lhs, MultiLock& rhs);

 private:
	 Digits CN[5] = { Digits(0,0,0,0) };
	 Digits LN[5] = { Digits(0,0,0,0) };
	 Digits HN[5] = { Digits(0,0,0,0) };
	 bool validCN[5];
	 bool validLN[5];
	 bool validHN[5];

};


MultiLock::MultiLock() {}
MultiLock::~MultiLock(){}

void MultiLock::SetCN(Digits arg, int i){ CN[i] = arg; }
void MultiLock::SetLN(Digits arg, int i) { LN[i] = arg; }
void MultiLock::SetHN(Digits arg, int i) { HN[i] = arg; }

void MultiLock::SetValidCN(bool arg, int i) { validCN[i] = arg; }
void MultiLock::SetValidLN(bool arg, int i) { validLN[i] = arg; }
void MultiLock::SetValidHN(bool arg, int i) { validHN[i] = arg; }

bool MultiLock::IsValidCN(int i) { return validCN[i]; }
bool MultiLock::IsValidLN(int i) { return validLN[i]; }
bool MultiLock::IsValidHN(int i) { return validHN[i]; }


Digits MultiLock::GetCN(int i) { return CN[i]; }
Digits MultiLock::GetLN(int i) { return LN[i]; }
Digits MultiLock::GetHN(int i) { return HN[i]; }


bool operator < (MultiLock& lhs, MultiLock& rhs)
{
	//if ((lhs.GetCN().GetA() + lhs.GetCN().GetB() + lhs.GetCN().GetC() + lhs.GetCN().GetD()) < (rhs.GetCN().GetA() + rhs.GetCN().GetB() + rhs.GetCN().GetC() + rhs.GetCN().GetD())) return true;
	//else return false;
	return false;
}

bool MultiLock::Validate()
{
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (!validCN[i]) count += 1;
		if (!validLN[i]) count += 1;
		if (!validHN[i]) count += 1;
	}
	if (count == 0 && SumToLeftLess()) return true;
	else return false;
}

bool MultiLock::SumToLeftLess()
{
	if ((CN[0] < CN[1]) && (CN[1] < CN[2]) && (CN[2] < CN[3]) && (CN[3] < CN[4])) return true;
	else return false;
}