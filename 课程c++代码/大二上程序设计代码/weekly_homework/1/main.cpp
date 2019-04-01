#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>

using namespace std;
void genword(string &word)
{
	if (word.find(",") != -1)
	{
		word.replace(word.find(","), 1, "");
	}
	if (word.find(".") != -1)
	{
		word.replace(word.find("."), 1, "");
	}
	if (word.find(":") != -1)
	{
		word.replace(word.find(":"), 1, "");
	}
	if (word.find("!") != -1)
	{
		word.replace(word.find("!"), 1, "");
	}
	if (word.find("?") != -1)
	{
		word.replace(word.find("?"), 1, "");
	}
	if (word.find("-") != -1)
	{
		word.replace(word.find("-"), 1, "");
	}
}
int main()
{
	
	std::cout << "intput the word:";
	string wanted;
	cin >> wanted;

	ifstream file("F:\\new_cppcode\\homework1\\homework1\\shakespeare.txt", ios::in);
	if (!file)//判断是否打开成功
		cerr << "open failed" << endl;
	int cur_line = 1;
	string line ="",line2="", word="";
	int count = 0;
	vector <string> oneline;
	
	while (getline(file, line))
	{
		oneline.push_back("");
		string remain = "";
		if (line.size() != 0 && line[line.size() - 1] == '-')
		{
			file >> remain;
			line.erase(line.size() - 1);
		}
		line += remain;
		
		istringstream istrm(line);
		while (istrm >> word)
		{
			genword(word);
			oneline.push_back(word);
		}
		oneline.push_back("");
		for (vector<string>::iterator it = oneline.begin(); it != oneline.end(); it++)
		{
			if (wanted == *it)
			{
				std::cout << "lines:   " << cur_line << endl;
				std::cout << "previous:" << *(it-1) << endl;
				std::cout << "follow:  " << *(it+1) << endl;
				count++;
			}
		}
		oneline.clear();
		cur_line++;
			
	}
	std::cout << "count:" << count << endl;
	std::system("pause");
	return 0;
}




/*#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

int main()
{
	vector<string> text;//创建vector对象
	ifstream ifile;//创建输入文件流对象
	ifile.open("F:\\new_cppcode\\homework1\\homework1\\try.txt", ifstream::in);//打开文件
	if (!ifile)//判断是否打开成功
		cerr << "open failed" << endl;
	//初始化vector对象
	string line, word;
	while (getline(ifile, line))//逐行读
	{
		istringstream istrm(line);//创建字符串流
		while (istrm >> word)//逐单词读
			text.push_back(word);
	}
	ifile.clear();
	ifile.seekg(0);//文件重定位
	while (ifile >> word) cout << word << endl;//逐单词读
	ifile.close();//关闭文件
	vector<string>::iterator it = text.begin();
	while (it != text.end())//遍历vector容器
	{
		cout << *it++ << endl;
	}
	system("pause");
	return 1;
}*/