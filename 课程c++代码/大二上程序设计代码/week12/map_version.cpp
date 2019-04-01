#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------

struct pos
{
	int x;
	int y;
	pos(int _x, int _y) {
		x = _x; y = _y;
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
	int shortest_distance(pos A, pos B)
	{
		return max(abs(A.x - B.x), abs(A.y - B.y));
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
		map<int,pos> numPos;
		for (int i = 0; i < puzz.size(); i++)
		{
			if (puzz[i] != "."&&puzz[i] != "*")
			{
				pos curPos(i / max_wid, i%max_wid);
				int value = atoi(puzz[i].c_str());
				numPos[value] = curPos;
			}
		}
		

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
			cout << "   ";
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
	bool bFound = s.solve(puzzles[puzzleIndex].data, puzzles[puzzleIndex].width);

	if (bFound)
	{
		cout << "The answer: " << endl;
		printPuzzle(puzzles[puzzleIndex]);
	}
	else
	{
		cout << "No answer." << endl;
	}

	system("pause");
	return 1;
}