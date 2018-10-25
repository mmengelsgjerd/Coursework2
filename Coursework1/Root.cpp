#include "pch.h"
#include "Root.h"

Root::Root()
	:
	Digits()
{
	if (a < 0) a += 10;
	if (b < 0) b += 10;
	if (c < 0) c += 10;
	if (d < 0) d += 10;
}

Root::Root(int a, int b, int c, int d)
	:
	Digits(a, b, c, d)
{
}

Root::~Root()
{

}