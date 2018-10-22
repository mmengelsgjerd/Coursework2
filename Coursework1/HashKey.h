#pragma once
#include "Digits.h"

class HashKey : virtual public Digits
{
public:
	HashKey();
	HashKey(int a, int b, int c, int d);
	~HashKey();

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