#pragma once

#include <random>

template <typename T>
class Digits {
public:
	Digits<T>();
	Digits(T a, T b, T c, T d);
	~Digits();
	bool ValidCN();

	template <typename T>
	friend Digits<T> operator+(const Digits<T>& lhs, const Digits<T>& rhs);

	template <typename T>
	friend std::ostream& operator<<(std::ostream& ostr, const Digits<T>& num);

	template <typename T>
	friend bool operator==(const Digits<T>& lhs, const Digits<T>& rhs);

	template <typename T>
	friend bool operator < (const Digits<T>& lhs, const Digits<T>& rhs);

	template <typename T>
	friend Digits<T> operator - (const Digits<T>& lhs, const Digits<T>& rhs);

	T GetA();
	T GetB();
	T GetC();
	T GetD();


protected:
	T a, b, c, d;

};

template <typename T>
Digits<T>::Digits() :
	a(rand() % 8 - 9), b(rand() % 10 - 0),
	c(rand() % 8 - 9), d(rand() % 10 - 0)

{
}

template <typename T>
Digits<T>::Digits(T a, T b, T c, T d) :
	a(a), b(b), c(c), d(d)
{}

template <typename T>
Digits<T>::~Digits() {}

template <typename T>
bool Digits<T>::ValidCN()
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

template <typename T>
Digits<T> operator+(const Digits<T>& lhs, const Digits<T>& rhs)
{
	T a = (lhs.a + rhs.a) % 10; if (a < 0) a += 10;
	T b = (lhs.b + rhs.b) % 10; if (b < 0) b += 10;
	T c = (lhs.c + rhs.c) % 10; if (c < 0) c += 10;
	T d = (lhs.d + rhs.d) % 10; if (d < 0) d += 10;

	return Digits<T>(a, b, c, d);
}

template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Digits<T>& num)
{
	ostr <<
		(num.a >= 0 ? "+" : "") << num.a << "," <<
		(num.b >= 0 ? "+" : "") << num.b << "," <<
		(num.c >= 0 ? "+" : "") << num.c << "," <<
		(num.d >= 0 ? "+" : "") << num.d;
	return ostr;
}

template <typename T>
bool operator==(const Digits<T>& lhs, const Digits<T>& rhs)
{
	if ((lhs.a != rhs.a) || (lhs.b != rhs.b) || (lhs.c != rhs.c) || (lhs.d != rhs.d)) return true;
	else return false;
}

template <typename T>
bool operator < (const Digits<T>& lhs, const Digits<T>& rhs)
{
	T x = (lhs.a + lhs.b + lhs.c + lhs.d);
	T y = (rhs.a + rhs.b + rhs.c + rhs.d);
	if (x < y) return true;
	else return false;
}

template <typename T>
Digits<T> operator - (const Digits<T>& lhs, const Digits<T>& rhs)
{
	T a = (lhs.a - rhs.a) % 10; if (a < 0) a += 10;
	T b = (lhs.b - rhs.b) % 10; if (b < 0) b += 10;
	T c = (lhs.c - rhs.c) % 10; if (c < 0) c += 10;
	T d = (lhs.d - rhs.d) % 10; if (d < 0) d += 10;

	return Digits<T>(a, b, c, d);
}

template <typename T>
T Digits<T>::GetA() { return a; }
template <typename T>
T Digits<T>::GetB() { return b; }
template <typename T>
T Digits<T>::GetC() { return c; }
template <typename T>
T Digits<T>::GetD() { return d; }
