#ifndef DICT_H

#include <string>
#include <vector>

using namespace std;

class Dict
{
public:
	Dict(string words = "", string pres="", string fols="");
	string word;
	string pre;
	string fol;
	vector <int> LineNum;

};

#endif // !DICT_H