#pragma once
#include "Number.h"



class Lock {


public:
	Lock();
	~Lock();
	void SetCN(Number arg, int i);
	void SetLN(Number arg, int i);
	void SetHN(Number arg, int i);

	void SetValidCN(bool arg, int i);
	void SetValidLN(bool arg, int i);
	void SetValidHN(bool arg, int i);

	bool GetValidCN(int i);
	bool GetValidLN(int i);
	bool GetValidHN(int i);
	
	bool Validate();

	Number GetCN(int i);
	Number GetLN(int i);
	Number GetHN(int i);

	friend bool operator < (Lock& lhs, Lock& rhs);

 private:
	 Number CN[5] = { Number(0,0,0,0) };
	 Number LN[5] = { Number(0,0,0,0) };
	 Number HN[5] = { Number(0,0,0,0) };
	 bool validCN[5];
	 bool validLN[5];
	 bool validHN[5];

};


Lock::Lock() {}
Lock::~Lock(){}

void Lock::SetCN(Number arg, int i){ CN[i] = arg; }
void Lock::SetLN(Number arg, int i) { LN[i] = arg; } 
void Lock::SetHN(Number arg, int i) { HN[i] = arg; } 

void Lock::SetValidCN(bool arg, int i) { validCN[i] = arg; }
void Lock::SetValidLN(bool arg, int i) { validLN[i] = arg; }
void Lock::SetValidHN(bool arg, int i) { validHN[i] = arg; }

bool Lock::GetValidCN(int i) { return validCN[i]; }
bool Lock::GetValidLN(int i) { return validLN[i]; }
bool Lock::GetValidHN(int i) { return validHN[i]; }


Number Lock::GetCN(int i) { return CN[i]; }
Number Lock::GetLN(int i) { return LN[i]; }
Number Lock::GetHN(int i) { return HN[i]; }


bool operator < (Lock& lhs, Lock& rhs)
{
	//if ((lhs.GetCN().GetA() + lhs.GetCN().GetB() + lhs.GetCN().GetC() + lhs.GetCN().GetD()) < (rhs.GetCN().GetA() + rhs.GetCN().GetB() + rhs.GetCN().GetC() + rhs.GetCN().GetD())) return true;
	//else return false;
	return false;
}

bool Lock::Validate()
{
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (!validCN[i]) count += 1;
		if (!validLN[i]) count += 1;
		if (!validHN[i]) count += 1;
	}
	if (count > 0) return false;
	else return true;
}