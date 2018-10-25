#pragma once
#include "Digits.h"

class HashKey : public Digits<int>
{
public:
	HashKey();
	HashKey(int a, int b, int c, int d);
	~HashKey();

};

