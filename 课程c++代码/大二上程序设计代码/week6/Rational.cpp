#include "Rational.h"

Rational::Rational()
{
	num = 0;
	den = 1;
}

Rational::Rational(int x, int y):num(x),den(y)
{
}

Rational::~Rational()
{
}

Rational Rational::operator+(const Rational & a) const
{
	Rational tmp;
	tmp.num = num * a.den + a.num*den;
	tmp.den = den * a.den;
	tmp.reductFraction();
	return tmp;
}

Rational Rational::operator-(const Rational & a) const
{
	Rational tmp;
	tmp.num = num * a.den - a.num*den;
	tmp.den = den * a.den;
	tmp.reductFraction();
	return tmp;
}

Rational Rational::operator*(const Rational & a) const
{
	Rational tmp;
	tmp.num = num * a.num;
	tmp.den = den * a.den;
	tmp.reductFraction();
	return tmp;
}

Rational Rational::operator/(const Rational & a) const
{
	Rational tmp;
	tmp.num = num * a.den;
	tmp.den = den * a.num;
	tmp.reductFraction();
	return tmp;
}

Rational & Rational::operator=(const Rational & a)
{
	if (this == &a) return *this;
	num = a.num;
	den = a.den;
	return *this;
}

bool Rational::operator>(const Rational & a) const
{
	return (num*a.den)>(den*a.num);
}

int Rational::getNum()
{
	return num;
}

int Rational::getDen()
{
	return den;
}

void Rational::reductFraction()
{
	int tmp = (num > den) ? den : num;
	for (; tmp > 1; --tmp)
	{
		if (num%tmp == 0 && den%tmp == 0)
		{
			num /= tmp;
			den /= tmp;
			break;
		}
	}
}
