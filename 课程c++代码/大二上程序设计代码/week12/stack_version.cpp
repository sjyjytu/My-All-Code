#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <time.h>

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------

struct pos
{
	int x;
	int y;
	pos() {
		x = -1;
		y = -1;
	}
	pos(int _x, int _y) {
		x = _x; y = _y;
	}
	bool operator!=(const pos&p)const
	{
		return x != p.x || y != p.y;
	}
};

//------------------------------------------------------------------------------
class Solver
{
private:
	//member variables
	//member functions
	int maxwidth;
public:

	//constructors & deconstructors
	Solver()
	{
		maxwidth = 0;
	}
	
	bool poslegal(pos A)
	{
		return A.x >= 0 && A.y >= 0 && A.x < maxwidth&&A.y < maxwidth;
	}
	
	string intToStr(int a)
	{
		stringstream ss;
		ss << a;
		return ss.str();
	}
	//member functions
	bool solve(vector<string>& puzz, int max_wid)
	{
		//init 
		maxwidth = max_wid;
		map<int, pos> numPos; //给定的数字，位置
		for (int i = 0; i < puzz.size(); i++)
		{
			if (puzz[i] != "."&&puzz[i] != "*")
			{
				pos curPos(i / max_wid, i%max_wid);
				int value = atoi(puzz[i].c_str());
				numPos[value] = curPos;
			}
		}
		stack<pair<int, pos>> NPStack;
		NPStack.push(make_pair(1,numPos[1]));
		int searchingNum = 1;
		stack<int> changedpos;
		while (!NPStack.empty())
		{
			pair<int, pos> curNP = NPStack.top();
			NPStack.pop();
			int curNum = curNP.first;
			pos curPos = curNP.second;
			
			while (curNum < searchingNum&&curNum != 1)
			{
				searchingNum--;
				if (numPos.find(searchingNum) != numPos.end())
					continue;
				puzz[changedpos.top()] = ".";  //复原一个被改过的位置
				changedpos.pop();
			}
			//现在可能是没有给点的点，或者是与给定点位置相同的非终点的点
			if (numPos.find(curNum) == numPos.end())
			{
				//当前点是没有给定的点
				puzz[curPos.x*maxwidth + curPos.y] = intToStr(curNum);
				changedpos.push(curPos.x*maxwidth + curPos.y);
			}
			searchingNum = curNum + 1;
			//printpuzz(puzz, maxwidth);

			int nextNum = curNum + 1;
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (!(i == 0 && j == 0))
					{
						pos nextPos(curPos.x + i, curPos.y + j);
						if (!poslegal(nextPos) || puzz[nextPos.x*maxwidth + nextPos.y] == "*")
							continue;
						if (numPos.find(nextNum) != numPos.end())
						{
							//如果下一个点是给出的点
							if (numPos[nextNum] != nextPos)
							{
								//如果下一个点与给定点位置不同就重置并返回
								//unfinish
								continue;
							}
							else
							{
								if (numPos.find(nextNum) == prev(numPos.end()))
								{
									//到终点了
									return true;
								}
							}
						}
						else if (puzz[nextPos.x*maxwidth + nextPos.y] != ".")
						{
							continue;
						}
						NPStack.push(make_pair(nextNum,nextPos));
					}
				}
			}

		}
		return false;
	}
	
	void printpuzz(vector<string> puzz, int max_wid)
	{
		int c = 0;
		for (vector<string>::iterator i = puzz.begin(); i != puzz.end(); i++)
		{
			if ((*i) != "*" && (*i) != ".")
			{
				if (atoi((*i).c_str()) < 10) cout << "0";
				cout << (*i) << " ";
			}
			else
				cout << " " << (*i) << " ";
			if (++c >= max_wid)
			{
				cout << endl; c = 0;
			}
		}
		cout << endl << endl;
	}
};

struct puzzle
{
	int width;
	vector<string> data;
};

void printPuzzle(puzzle p)
{
	int c = 0;
	for (vector<string>::iterator i = p.data.begin(); i != p.data.end(); i++)
	{
		if ((*i) != "*" && (*i) != ".")
		{
			if (atoi((*i).c_str()) < 10) cout << "0";
			cout << (*i) << " ";
		}
		else
			cout << " " << (*i) << " ";
		if (++c >= p.width)
		{
			cout << endl; c = 0;
		}
	}
	cout << endl << endl;

}
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	struct puzzle puzzles[3];

	istringstream iss1("32 . . . 37 * * * . 34 . . 38 * * * . 25 . . 12 . * * 29 . 20 . 40 . * * . 28 . 19 . 10 1 * * * 15 . . . . * * * * * . . . 3 * * * * * * . 4");
	copy(istream_iterator<string>(iss1), istream_iterator<string>(), back_inserter<vector<string> >(puzzles[0].data));
	puzzles[0].width = 8;

	istringstream iss2(". 53 . 59 . 67 66 . . 52 . . 57 . . 68 72 . . . 56 . 64 * * * * 49 . . . * * 17 . * . 10 . * . 16 . . 22 . 46 . * . 2 . . 24 . 44 . . 4 1 . . 25 . . 7 6 . 34 . . 31 42 40 . . . . . 29 .");
	copy(istream_iterator<string>(iss2), istream_iterator<string>(), back_inserter<vector<string> >(puzzles[1].data));
	puzzles[1].width = 9;

	istringstream iss3("56 . . . . 62 . . 67 . 55 . 53 . . 65 . . 9 . 52 . . 48 . . 69 . 6 . * * * 47 . . 5 . . * * * 72 . 42 . . 13 * * * . . 41 . 3 . 18 . . 38 . . 2 . . 22 23 . . . 32 1 20 . . 25 . 35 . .");
	copy(istream_iterator<string>(iss3), istream_iterator<string>(), back_inserter<vector<string> >(puzzles[2].data));
	puzzles[2].width = 9;

	int puzzleIndex = 0;

	if (argc > 1)
	{
		puzzleIndex = atoi(argv[1]);
	}

	cout << "The original puzzle:" << endl;

	printPuzzle(puzzles[puzzleIndex]);

	Solver s;
	clock_t start = clock();
	bool bFound = s.solve(puzzles[puzzleIndex].data, puzzles[puzzleIndex].width);
	clock_t finish = clock();
	if (bFound)
	{
		cout << "The answer: " << endl;
		printPuzzle(puzzles[puzzleIndex]);
	}
	else
	{
		cout << "No answer." << endl;
	}
	cout << "time consumes: " << finish - start << "ms" << endl;
	system("pause");
	return 1;
}