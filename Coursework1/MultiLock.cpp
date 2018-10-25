#include "pch.h"
#include "MultiLock.h"

MultiLock::MultiLock() {}

MultiLock::~MultiLock() {}

void MultiLock::SetCN(Digits<int> arg) { CN.push_back(arg); }
void MultiLock::SetLN(Digits<int> arg) { LN.push_back(arg); }
void MultiLock::SetHN(Digits<int> arg) { HN.push_back(arg); }

void MultiLock::ClearLN() { LN.clear(); }
int MultiLock::GetLNSize() { return (int)LN.size(); }

void MultiLock::SetValidCN(bool arg) { validCN.push_back(arg); }
void MultiLock::SetValidLN(bool arg) { validLN.push_back(arg); }
void MultiLock::SetValidHN(bool arg) { validHN.push_back(arg); }

bool MultiLock::IsValidCN(int i) { return validCN[i]; }
bool MultiLock::IsValidLN(int i) { return validLN[i]; }
bool MultiLock::IsValidHN(int i) { return validHN[i]; }


Digits<int> MultiLock::GetCN(int i) { return CN[i]; }
Digits<int> MultiLock::GetLN(int i) { return LN[i]; }
Digits<int> MultiLock::GetHN(int i) { return HN[i]; }

bool MultiLock::Validate(int safeSize)
{
	int count = 0;
	for (int i = 0; i < safeSize; i++)
	{
		if (!validCN[i]) count += 1;
		if (!validLN[i]) count += 1;
		if (!validHN[i]) count += 1;
	}
	//if (count == 0 && SumToLeftLess(safeSize) && SumEquals(safeSize)) return true;
	//if (count == 0 && SumEquals(safeSize)) return true;
	//if (count == 0 && SumToLeftLess(safeSize)) return true;
	if (count == 0) return true;
	else return false;
}

bool MultiLock::SumToLeftLess(int safeSize)
{
	int count = 0;
	for (int i = 1; i < safeSize; i++)
	{
		if (CN[i - 1] < CN[i]) count += 1;
	}
	if (count == (safeSize - 1)) return true;
	else return false;
	/*if ((CN[0] < CN[1]) && (CN[1] < CN[2]) && (CN[2] < CN[3]) && (CN[3] < CN[4])) return true;
	else return false;*/
}

bool MultiLock::SumEquals(int safeSize)
{
	int count = 0;
	for (int i = 0; i < safeSize; i++)
	{
		if ((CN[i].GetA() + CN[i].GetB() + CN[i].GetC() + CN[i].GetD()) % 2 == 0) count += 1;
	}
	if (count == safeSize) return true;
	else return false;

	/*bool a = false, b = false, c = false , d = false, e = false;
	if ((CN[0].GetA() + CN[0].GetB() + CN[0].GetC() + CN[0].GetD()) % 2 == 0) a = true;
	if ((CN[1].GetA() + CN[1].GetB() + CN[1].GetC() + CN[1].GetD()) % 2 == 0) b = true;
	if ((CN[2].GetA() + CN[2].GetB() + CN[2].GetC() + CN[2].GetD()) % 2 == 0) c = true;
	if ((CN[3].GetA() + CN[3].GetB() + CN[3].GetC() + CN[3].GetD()) % 2 == 0) d = true;
	if ((CN[4].GetA() + CN[4].GetB() + CN[4].GetC() + CN[4].GetD()) % 2 == 0) e = true;

	if (a && b && c && d && e) return true;
	else return false;
	*/
}