#pragma once
#pragma warning( disable : 4290 )  

#include "HashKey.h"
#include "Root.h"

class Set {
public:
	Set(HashKey UHF, HashKey LHF, HashKey PHF, Root ROOT);
	~Set();
	Root GetROOT();
	HashKey GetUHF();
	HashKey GetLHF();
	HashKey GetPHF();

private:
	HashKey UHF;
	HashKey LHF;
	HashKey PHF;
	Root ROOT;
};

Set::Set(HashKey UHF, HashKey LHF, HashKey PHF, Root ROOT)
	:
	UHF(UHF),
	LHF(LHF),
	PHF(PHF),
	ROOT(ROOT)
{}

Set::~Set(){}

Root Set::GetROOT() { return ROOT; }
HashKey Set::GetUHF() { return UHF; }
HashKey Set::GetLHF() { return LHF; }
HashKey Set::GetPHF() { return PHF; }