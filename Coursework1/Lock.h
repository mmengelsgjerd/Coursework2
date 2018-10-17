#pragma once
#include "Number.h"

class Lock {


public:
	Lock();
	~Lock();
	void SetCN(Number num);
	void SetLN(Number num);
	void SetHN(Number num);

	Number GetCN();
	Number GetLN();
	Number GetHN();

private:
	Number CN = Number(0,0,0,0);
	Number LN = Number(0,0,0,0);
	Number HN = Number(0,0,0,0);

};


Lock::Lock() {}


Lock::~Lock(){}

void Lock::SetCN(Number num) { CN = num; }
void Lock::SetLN(Number num) { LN = num; }
void Lock::SetHN(Number num) { HN = num; }

Number Lock::GetCN() { return CN; }
Number Lock::GetLN() { return LN; }
Number Lock::GetHN() { return HN; }
