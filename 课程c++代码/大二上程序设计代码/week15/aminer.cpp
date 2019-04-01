#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

struct paper
{
	string id;
	string title;
	//string authorOrg;
	int year;
	vector<string> references;
	paper() {};
	paper(string i, string t, int y,vector<string> r)
	{
		id = i; title = t; year = y; references = r;
	}
};

bool compareByYear(const paper&p1, const paper&p2)
{
	return p1.year < p2.year;
}

string readUntilEnd(const string &line, int start, char end)
{
	int endPos = line.find(end,start);
	if (endPos != string::npos)
	{
		return line.substr(start, endPos - start);
	}
	return line.substr(start);
}

struct author
{
	vector<paper> papers;
	map<int, string> orgs;
};

int main()
{
	ifstream file("F:\\new_cppcode\\papers\\aminer_papers_1.txt");
	//ifstream file("F:\\new_cppcode\\test1.txt");
	string line;
	map<string, author >Authors;
	map<string, int> citations;  //被引用
	map<string, vector<string> >citationsMap;  //被哪些文章引用
	while (getline(file,line))
	{
		string id = "",title = "",authors = "",references = "";
		vector<string> authorsVec;
		vector<string> referencesVec;
		int year = 0;
		int idPos = line.find("\"id\": \"");
		int titlePos = line.find("\"title\": \"");
		int authorsPos = line.find("\"authors\": [");
		int yearPos = line.find("\"year\": ");
		int referencesPos = line.find("\"references\": [");
		if (idPos != string::npos)
		{
			id = readUntilEnd(line,idPos + 7, '"');
		}
		if (titlePos != string::npos)
		{
			title = readUntilEnd(line, titlePos + 10, '"');
		}
		if (yearPos != string::npos)
		{
			year = atoi(readUntilEnd(line, yearPos + 8, ',').c_str());
		}
		/*if (authorsPos != string::npos)
		{
			authors = readUntilEnd(line, authorsPos + 12, ']');
			//{"name": "N. F. Gray", "org": "..."}, {"name": "R. O. Gray"}
			int tmpAuthorPos = authors.find("\"name\": ");
			while (tmpAuthorPos!=string::npos)
			{
				string name = readUntilEnd(authors, tmpAuthorPos + 8, '}');
				//name = "N. F. Gray", "org": "..." or "R. O. Gray"
				//name = "1234", "org...
				if (name=="\"\""||name=="null")
				{
					authorsVec.push_back("JY");  //如果没人认领，就是我写的
				}
				else
				{
					int orgPos = name.find("\"org\": \"");
					if (orgPos != string::npos)
					{
						string org = readUntilEnd(name, orgPos + 8, '"');
						string rightName = name.substr(1, orgPos - 4);
						Authors[rightName].orgs[year] = org;
						authorsVec.push_back(rightName);
					}
					else
						authorsVec.push_back(name.substr(1, name.size() - 2));
				}
				authors.erase(0, tmpAuthorPos + 8);
				tmpAuthorPos = authors.find("\"name\": ");
			}
		}*/
		if (referencesPos != string::npos)
		{
			//"53e9b0b2b7602d9703b1de16", "53e9b7a6b7602d97043502c9", "53e99addb7602d9702364025"
			references = readUntilEnd(line, referencesPos + 15, ']');
			int tmpRefPos = references.find("\"");
			while (tmpRefPos!=string::npos)
			{
				string refId = readUntilEnd(references, tmpRefPos + 1, '"');
				if (refId != "")
				{
					referencesVec.push_back(refId);
					if (citations.find(refId) == citations.end())
						citations[refId] = 1;
					else
					{
						citations[refId]++;
					}
					citationsMap[refId].push_back(id);
				}
				references.erase(0, tmpRefPos + refId.size() + 2);
				tmpRefPos = references.find("\"");
			}
		}
		/*paper tmpPaper(id,title,year,referencesVec);

		for (int i = 0; i < authorsVec.size(); i++)
		{
			Authors[authorsVec[i]].papers.push_back(tmpPaper);
		}*/
	}
	/*for (auto it = Authors.begin(); it != Authors.end(); it++)
	{
		sort(it->second.papers.begin(), it->second.papers.end(), compareByYear);
	}*/
	while (true)
	{
		/*cout << "input author name:";
		string name = "";
		getline(cin, name);
		if (Authors.find(name) != Authors.end())
		{
			for (auto it = Authors[name].orgs.begin(); it != Authors[name].orgs.end(); it++)
			{
				cout << it->first << ": " << it->second << endl;
			}
			cout << Authors[name].papers.size()<<endl;
			for (int i = 0; i < Authors[name].papers.size(); i++)
			{
				cout << Authors[name].papers[i].id << ' ' << Authors[name].papers[i].year << ' ' << citations[Authors[name].papers[i].id] << endl;
			}
		}*/
		cout << "input id:";
		string id = "";
		int n = 0;
		getline(cin, id);
		cout << "input n:";
		cin >> n;
		if (citations.find(id) != citations.end())
		{
			cout << "被引用：" << citations[id] << "次" << endl;
		}
		vector<string> curSearchVec;
		vector<string> newSearchVec;
		curSearchVec.push_back(id);
		set<string> citationSet;
		for (int i = 0; i < n; i++)	//搜n次
		{
			for (int j = 0; j < curSearchVec.size(); j++)	//所有要搜被引用的id
			{
				vector<string> tmpVec = citationsMap[curSearchVec[j]];
				for (int k = 0; k < tmpVec.size(); k++)
				{
					if (citationSet.count(tmpVec[k]) == 0)
					{
						citationSet.insert(tmpVec[k]);
						newSearchVec.push_back(tmpVec[k]);
					}
				}
			}
			curSearchVec = newSearchVec;
			newSearchVec.clear();
		}
		for (auto it = citationSet.begin();it!=citationSet.end();it++)
		{
			cout << *it << endl;
		}
	}
	return 0;
}