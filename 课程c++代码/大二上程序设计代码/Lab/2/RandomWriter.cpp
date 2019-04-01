/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name:yuanjianyong
 * Student ID:517021910930
 * This file is the starter project for the random writer problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 100



// get order number
int read_order();

// build model
void model_read(const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

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

void model_read(const int &order, map<string, vector<char>> &model)
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
		for (int i = 0; i < order; i++)
		{
			char c = file_input.get();
			
			if (c == EOF)
				break;
			s += c;
		}
		if (order == 0)  //for the situation of order0
			s = "only";

		char next_c = file_input.get();
		if (next_c == EOF)
			break;
		
		/*I am confused that the following code run secretly after 'break'*/
		if (model.find(s) != model.end())
			model.insert(make_pair(s, vector<char>()));
			
		model[s].push_back(next_c);
		for (int i = 0; i < order; i++)
			file_input.unget();
	}
	file_input.close();
}

void random_write(const int &order, map<string, vector<char>> &model)
{
	string Seed = "";
	int max = 0;
	//the init seed must have the longest vector<char>
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
	cout << Seed;
	int write_length = order;
	srand((unsigned)time(NULL));
	while (write_length<=2000)
	{
		if (model[Seed].size() == 0)
			break;  //stop early
		int random_index = rand() % model[Seed].size();
		char choice = model[Seed][random_index];
		//writer << choice;
		cout << choice;
		if (order != 0)
		{
			Seed += choice;
			Seed.erase(0, 1);  //update Seed
		}
		write_length++;
	}
}

int main()
{
	int order = read_order();
	map<string, vector<char> > model;
	model_read(order, model);
	random_write(order, model);
	system("pause");
    return 0;
}
