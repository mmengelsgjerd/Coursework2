#include "pch.h"
#include "Set.h"

Set::Set(HashKey UHF, HashKey LHF, HashKey PHF, Root ROOT)
	:
	UHF(UHF),
	LHF(LHF),
	PHF(PHF),
	ROOT(ROOT)
{}

Set::~Set() {}

Root Set::GetROOT() { return ROOT; }
HashKey Set::GetUHF() { return UHF; }
HashKey Set::GetLHF() { return LHF; }
HashKey Set::GetPHF() { return PHF; }