#pragma once
/*
#include <random>

class LockDigit {
public:
	LockDigit();
	LockDigit(int a, int b, int c, int d);
	~LockDigit();
	bool ValidCN();
	

	friend LockDigit operator+(const LockDigit& lhs, const LockDigit& rhs);
	friend std::ostream& operator<<(std::ostream& ostr, const LockDigit& num);
	friend bool operator==(const LockDigit& lhs, const LockDigit& rhs);

	int GetA();
	int GetB();
	int GetC();
	int GetD();

private:
	int a, b, c, d;

};

LockDigit::LockDigit() :
	a(rand() % 19 - 9), b(rand() % 19 - 9),
	c(rand() % 19 - 9), d(rand() % 19 - 9)

{	
}

LockDigit::LockDigit(int a, int b, int c, int d) :
	a(a), b(b), c(c), d(d)
{}

LockDigit::~LockDigit(){}

LockDigit operator+(const LockDigit& lhs, const LockDigit& rhs)
{
	Number num = Number((lhs.a + rhs.a) % 10, (lhs.b + rhs.b) % 10, (lhs.c + rhs.c) % 10, (lhs.d + rhs.d) % 10);

	if (num.a < 0) { num.a += 10; }
	if (num.b < 0) { num.b += 10; }
	if (num.c < 0) { num.c += 10; }
	if (num.d < 0) { num.d += 10; }
	
	int a = (lhs.a + rhs.a) % 10; if (a < 0) a += 10;
	int b = (lhs.b + rhs.b) % 10; if (b < 0) b += 10;
	int c = (lhs.c + rhs.c) % 10; if (c < 0) c += 10;
	int d = (lhs.d + rhs.d) % 10; if (d < 0) d += 10;

	LockDigit n = LockDigit(a, b, c, d);

	return n;
}

std::ostream& operator<<(std::ostream& ostr, const LockDigit& num)
{
	ostr <<
		(num.a >= 0 ? "+" : "") << num.a << "," <<
		(num.b >= 0 ? "+" : "") << num.b << "," <<
		(num.c >= 0 ? "+" : "") << num.c << "," <<
		(num.d >= 0 ? "+" : "") << num.d;
	return ostr;
}

bool LockDigit::ValidCN()
{
	int count = 0;
	if (a == b) count += 1;
	if (a == c) count += 1;
	if (a == d) count += 1;
	if (b == c) count += 1;
	if (b == d) count += 1;
	if (c == d) count += 1;

	if (count > 0) return false;
	else return true;
}

bool operator==(const LockDigit& lhs, const LockDigit& rhs)
{
	if ((lhs.a != rhs.a) || (lhs.b != rhs.b) || (lhs.c != rhs.c) || (lhs.d != rhs.d)) return true;
	else return false;
}

int LockDigit::GetA() { return a; }
int LockDigit::GetB() { return b; }
int LockDigit::GetC() { return c; }
int LockDigit::GetD() { return d; }

*/