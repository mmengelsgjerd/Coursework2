#pragma once

#include <random>

//template <typename T>
class Digits {
public:
	Digits();
	Digits(int a, int b, int c, int d);
	~Digits();
	bool ValidCN();

	friend Digits operator+(const Digits& lhs, const Digits& rhs);
	friend std::ostream& operator<<(std::ostream& ostr, const Digits& num);
	friend bool operator==(const Digits& lhs, const Digits& rhs);
	friend bool operator < (const Digits& lhs, const Digits& rhs);

	int GetA();
	int GetB();
	int GetC();
	int GetD();

protected:
	int a, b, c, d;

};

Digits::Digits() :
	a(rand() % 19 - 9), b(rand() % 19 - 9),
	c(rand() % 19 - 9), d(rand() % 19 - 9)

{
}

Digits::Digits(int a, int b, int c, int d) :
	a(a), b(b), c(c), d(d)
{}

Digits::~Digits() {}

bool Digits::ValidCN()
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

Digits operator+(const Digits& lhs, const Digits& rhs)
{
	int a = (lhs.a + rhs.a) % 10; if (a < 0) a += 10;
	int b = (lhs.b + rhs.b) % 10; if (b < 0) b += 10;
	int c = (lhs.c + rhs.c) % 10; if (c < 0) c += 10;
	int d = (lhs.d + rhs.d) % 10; if (d < 0) d += 10;

	return Digits(a, b, c, d);
}

std::ostream& operator<<(std::ostream& ostr, const Digits& num)
{
	ostr <<
		(num.a >= 0 ? "+" : "") << num.a << "," <<
		(num.b >= 0 ? "+" : "") << num.b << "," <<
		(num.c >= 0 ? "+" : "") << num.c << "," <<
		(num.d >= 0 ? "+" : "") << num.d;
	return ostr;
}

bool operator==(const Digits& lhs, const Digits& rhs)
{
	if ((lhs.a != rhs.a) || (lhs.b != rhs.b) || (lhs.c != rhs.c) || (lhs.d != rhs.d)) return true;
	else return false;
}

bool operator < (const Digits& lhs, const Digits& rhs)
{
	int x = (lhs.a + lhs.b + lhs.c + lhs.d);
	int y = (rhs.a + rhs.b + rhs.c + rhs.d);
	if (x < y) return true;
	else return false;
}

int Digits::GetA() { return a; }
int Digits::GetB() { return b; }
int Digits::GetC() { return c; }
int Digits::GetD() { return d; }
