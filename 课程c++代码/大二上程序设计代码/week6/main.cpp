#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>
using namespace std;
class Rational
{
public:
	Rational();
	Rational(int x, int y = 1);
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
Rational::Rational()
{
	num = 0;
	den = 1;
}

Rational::Rational(int x, int y) :num(x), den(y)
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

void bfs(vector<Rational> number,int n,int target,bool &found)
{
	if (found == 1)
		return;
	if (n == 1)
	{
		if (number[0].getNum()/ number[0].getDen() == target)
			found = 1;
		return;
	}
	long long mul = 1, sum = 0;
	for (int i = 0; i < n; i++)
	{
		mul *= (number[i].getNum() / number[i].getDen());
		sum += (number[i].getNum() / number[i].getDen());
	}
	if (mul < target&&sum < target)
		return;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			Rational a = number[i];
			Rational b = number[j];
			vector<Rational> tmpVec(number);
			tmpVec.erase(tmpVec.begin() + i);
			tmpVec.erase(tmpVec.begin() + j - 1);
			Rational result(0);
			int tmpN = n - 1;
			for (int k = 0; k < 5; k++)
			{
				if (found)
					return;
				switch (k)
				{
				case 0:
					result = a + b;
					tmpVec.push_back(result);
					bfs(tmpVec, tmpN, target, found);
					tmpVec.pop_back();
					break;
				case 1:
					result = (a > b)?(a-b):(b-a);
					tmpVec.push_back(result);
					bfs(tmpVec, tmpN, target, found);
					tmpVec.pop_back();
					break;
				case 2:
					result = a * b;
					tmpVec.push_back(result);
					bfs(tmpVec, tmpN, target, found);
					tmpVec.pop_back();
					break;
				case 3:
					if (b.getNum() != 0)
					{
						result = a / b;
						tmpVec.push_back(result);
						bfs(tmpVec, tmpN, target, found);
						tmpVec.pop_back();
					}
					break;
				case 4:
					if (a.getNum() != 0)
					{
						result = b / a;
						tmpVec.push_back(result);
						bfs(tmpVec, tmpN, target, found);
						tmpVec.pop_back();
					}
					break;
				default:
					break;
				}
			}
				
		}
	}
}
int main()
{
	while (true)
	{
		cout << endl;
		clock_t start, finish;
		srand((unsigned)time(NULL));
		int n = 9, target = 0;
		cout << "input n,target,number[i]:";
		cin >> n >> target;
		//cout << "input n:"<<n<<endl;
		//cin >> n;
		//target = rand() % 1000;
		//cout << "target:" << target << endl;
		vector <Rational> number;

		for (int i = 0; i < n; i++)
		{
			int tmp = 0;
			cin >> tmp;
			
			//int tmp = rand() % 100;
			//cout << tmp << "  ";

			Rational tmpR(tmp);
			number.push_back(tmpR);
		}
		cout << endl;
		bool found = 0;
		start = clock();
		bfs(number, n, target, found);
		finish = clock();
		if (found)
		{
			cout << "True" << endl;
		}
		else
		{
			cout << "False" << endl;
		}
		cout << "time:" << double(finish - start) / 1000 << "s" << endl;
		Sleep(2000);
	}
	
	
	
	system("pause");
	return 0;
}