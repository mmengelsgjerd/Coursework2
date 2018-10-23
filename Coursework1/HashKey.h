#pragma once
#include "Digits.h"

class HashKey : virtual public Digits<int>
{
public:
	HashKey();
	HashKey(int a, int b, int c, int d);
	~HashKey();
	void IncreaseHashKey(HashKey hashKey);

};

HashKey::HashKey()
	:
	Digits()
{
}

HashKey::HashKey(int a, int b, int c, int d)
	:
	Digits(a,b,c,d)
{
}


HashKey::~HashKey()
{

}

void HashKey::IncreaseHashKey(HashKey hashKey)
{
	if (hashKey.a < 9) hashKey.a += 1;
	if (hashKey.b < 9) hashKey.b += 1;
	if (hashKey.c < 9) hashKey.c += 1;
	if (hashKey.d < 9) hashKey.d += 1;
}