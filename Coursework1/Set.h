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
