/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name:yuanjianyong
 * Student ID:517021910930
 * This file is the starter project for the word ladder problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <map>
using namespace std;

//find the dest and init
void show_ans(vector<string> &ans);

//input and start function
void input_words(string &start, string &dest);

// read lexicon from file
void read_english(map<string,bool> &english);

void show_ans(vector<string> &ans)
{
    cout << "Found ladder:";
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++)
    {
        cout << "->" << ans[i];
    }
    cout << endl
         << endl;
}

void show_all(map<string, vector<string> > &all)
{
	for (auto it = all.begin(); it != all.end(); it++)
	{
		show_ans(it->second);
	}
}

void input_words(string &start, string &dest)
{
    cout << "Enter start word (enter ':q' to quit):";
    cin >> start;
    if (start == ":q")
    {
        exit(0);
    }
    cout << "Enter destination word:";
    cin >> dest;
}

void read_english(map<string,bool> &english)
{
	while (true)
	{
		cout << "Please enter filename containing source text:";
		string file_name;
		cin >> file_name;
		ifstream file_input(file_name.c_str());
		if (file_input.is_open())
		{
			string temp_word;
			while (getline(file_input, temp_word))
			{
				english.insert(make_pair(temp_word, 0));
			}
		}
		break;
	}
    
}


int main()
{
	queue<string> wordQueue;
	map<string, bool> dictionary;  //the second record whether the word has been used
	string start, destination;
	read_english(dictionary);
	input_words(start, destination);
	bool found = 0;
	vector<string> answer;

	wordQueue.push(start);
	map<string, vector<string> >developLadder;
	developLadder.insert(make_pair(start, vector<string>(1, start)));
	while (!wordQueue.empty())
	{
		string curFront = wordQueue.front();
		wordQueue.pop();
		if (curFront == destination)
		{
			//TODO:find!return this!
			answer = developLadder[destination];
			found = 1;
			break;
		}
		for (int i = 0; i < start.size(); i++)
		{
			for (char j = 'a'; j <= 'z'; j++)
			{
				string tmpMiddle = curFront;
				tmpMiddle[i] = j;
				if (dictionary.find(tmpMiddle) != dictionary.end() && dictionary[tmpMiddle] != 1)
				{
					//tmpMiddle is legal and has not been used

					vector<string> tmpVec = developLadder[curFront];
					tmpVec.push_back(tmpMiddle);
					developLadder.insert(make_pair(tmpMiddle, tmpVec));
					
					dictionary[tmpMiddle] = 1;  //set used
					wordQueue.push(tmpMiddle);

				}
			}
		}
	}
	if (!found)
		cout << "not ladder exist " << endl;
	else
	{
		show_ans(answer);
	}
	system("pause");
    return 0;
}
