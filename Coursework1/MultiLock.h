#pragma once
//#include "LockDigit.h"
#include "Digits.h"

using namespace std;

class MultiLock {

public:
	MultiLock();
	~MultiLock();
	void SetCN(Digits<int> arg);
	void SetLN(Digits<int> arg);
	void SetHN(Digits<int> arg);

	void ClearLN();
	int GetLNSize();

	void SetValidCN(bool arg);
	void SetValidLN(bool arg);
	void SetValidHN(bool arg);

	bool IsValidCN(int i);
	bool IsValidLN(int i);
	bool IsValidHN(int i); 
	 
	bool Validate(int safeSize);
	bool SumToLeftLess(int safeSize);
	bool SumEquals(int safeSize);

	Digits<int> GetCN(int i);
	Digits<int> GetLN(int i);
	Digits<int> GetHN(int i);

 private:
	 vector<Digits<int> > CN;
	 vector<Digits<int> > LN;
	 vector<Digits<int> > HN;

	 vector<bool> validCN;
	 vector<bool> validLN;
	 vector<bool> validHN;
};


