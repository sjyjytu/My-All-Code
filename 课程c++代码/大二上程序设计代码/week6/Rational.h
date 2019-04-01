#pragma once
class Rational
{
public:
	Rational();
	Rational(int x,int y=1);
	~Rational();
	Rational operator+(const Rational &a)const;
	Rational operator-(const Rational &a)const;
	Rational operator*(const Rational &a)const;
	Rational operator/(const Rational &a)const;
	Rational &operator=(const Rational &a);
	bool operator>(const Rational &a)const;
	int getNum();
	int getDen();
private:
	int num;
	int den;
	void reductFraction();
};