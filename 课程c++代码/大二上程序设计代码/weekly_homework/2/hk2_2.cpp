/*#include <iostream>
#include <string>

using namespace std;

int main()
{
	string input;
	getline(cin,input);
	input = " " + input;
	int Size = input.size();
	int before = 0, latter = 0;
	bool get_first = 0;
	char cur = ' ', pre;
	for (int i = Size -1; i >=0; i--)
	{
		pre = cur;
		cur = input[i];
		if (pre == ' ' && cur != ' ')
		{
			latter = i;
			continue;
		}
		else if (pre != ' ' && cur == ' ')
		{
			before = i + 1;
			get_first = 1;
			input = input + " " + input.substr(before, latter - before + 1);
			continue;
		}
		else
		{
			continue;
		}
	}
	if (get_first)
	{
		input.erase(0, Size+1);
		cout << input;
	}
	else
	{
		cout << "Invalid";
	}
	return 0;
}*/