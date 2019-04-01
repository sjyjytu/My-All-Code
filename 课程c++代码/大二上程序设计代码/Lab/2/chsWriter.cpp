#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

class chschar
{
public:
	chschar();
	chschar(char[2]);
	~chschar();
	void getC(ifstream &ifs);
	void ungetC(ifstream &ifs);
	bool eof();
	void print();
	string getstr();

private:
	char c[2];
	bool isSpace;
};

chschar::chschar()
{
	isSpace = 0;
}

chschar::chschar(char a[2])
{
	c[0] = a[0];
	c[1] = a[1];
	isSpace = 0;
}

chschar::~chschar()
{
}

void chschar::getC(ifstream & ifs)
{
	c[0] = ifs.get();
	if (c[0] == ' ' || c[0] == '\n')
	{
		isSpace = 1;
		c[1] = NULL;
		return;
	}
	c[1] = ifs.get();
}

void chschar::ungetC(ifstream & ifs)
{
	if (isSpace)
		ifs.unget();
	else
	{
		ifs.unget();
		ifs.unget();
	}
}

bool chschar::eof()
{
	if (c[0]==EOF)
		return true;
	return false;
}

void chschar::print()
{
	cout << c[0] << c[1];
}

string chschar::getstr()
{
	string tmp = "";
	tmp += c[0];
	tmp += c[1];
	return tmp;
}


// get order number
int read_order();

// build model
void model_read(const int &order, map<string, vector<chschar>> &model);

// write
void random_write(const int &order, map<string, vector<chschar>> &model);

void read_file(ifstream &file_input)
{
	while (true)
	{
		string model_name;
		cout << "Please input the model name:";
		cin >> model_name;
		file_input.open(model_name.c_str());
		if (file_input.is_open())
			break;
		cout << endl;
	}
}

int read_order()
{
	int order = 0;
	do
	{
		cout << "Please input order number(0-9):";
		cin >> order;
	} while (order < 0 || order > 9);

	return order;
}

void model_read(const int &order, map<string, vector<chschar>> &model)
{
	ifstream file_input;
	while (true)
	{
		string model_name;
		cout << "Please input the model name:";
		cin >> model_name;
		file_input.open(model_name.c_str());
		if (file_input.is_open())
			break;
		cout << endl;
	}
	file_input.clear();
	while (!file_input.eof())
	{
		string s = "";
		chschar c[20];
		for (int i = 0; i < order; i++)
		{
			c[i].getC(file_input);
			if (c[i].eof())
				break;
			s += c[i].getstr();
		}
		if (order == 0)  //for the situation of order0
			s = "only";

		c[order].getC(file_input);  //next_c
		if (c[order].eof())
			break;

		if (model.find(s) == model.end())
			model.insert(make_pair(s, vector<chschar>()));

		model[s].push_back(c[order]);
		for (int i = order; i >0; i--)
		{
			c[i].ungetC(file_input);
		}
	}
	file_input.close();
}

void random_write(const int &order, map<string, vector<chschar>> &model)
{
	string Seed = "";
	int max = 0;
	//the init seed must have the longest vector<char[2]>
	for (auto it = model.begin(); it != model.end(); it++)
	{
		if (it->second.size() > max)
		{
			max = it->second.size();
			Seed = it->first;
		}
	}
	//ofstream writer("my_book.txt", ios::app);
	//writer << Seed;
	//cout.imbue(locale("chs"));
	cout << Seed;
	int write_length = order;
	srand((unsigned)time(NULL));
	while (write_length <= 2000)
	{
		if (model[Seed].size() == 0)
			break;  //stop early
		int random_index = rand() % model[Seed].size();
		chschar choice(model[Seed][random_index]);
		//writer << choice;
		choice.print();
		if (order != 0)
		{
			Seed += choice.getstr();
			Seed.erase(0, 2);  //update Seed
		}
		write_length++;
	}
}

int main()
{
	int order = read_order();
	map<string, vector<chschar> > model;
	model_read(order, model);
	random_write(order, model);
	system("pause");
	return 0;
}