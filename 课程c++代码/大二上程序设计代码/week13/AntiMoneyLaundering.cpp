#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <set>

using namespace std;
struct transfer
{
	//stack<int> giverId;
	double money;
	string time;
	int receiverID;
	unsigned long transferID;  //ÿһ�ʽ��׶�����id������ȥ��
	transfer(double d,string t,int id2,unsigned long id3)
	{
		money = d;
		time = t;
		receiverID = id2;
		transferID = id3;
	}
};
bool timeSatisfy(string a, string b)
{
	//a<=b��b-a<=30day
	int dyear = (b[2] - a[2]) * 10 + b[3] - a[3];
	int dmon = (b[5] - a[5]) * 10 + b[6] - a[6];
	int dday = (b[8] - a[8]) * 10 + b[9] - a[9];
	if (dyear == 0 && (dmon * 30 + dday) >= 0 && (dmon * 30 + dday) <= 30)
		return true;
	return false;
}
int main()
{
	ifstream ifs("test2.txt");
	string line;
	map<int, vector<transfer>> suspects;  //id, all transfer
	cout << "data loading..." << endl;
	unsigned long id3 = 0;
	while (getline(ifs, line))
	{
		stringstream ss(line);
		int id1, id2;
		double money;
		string time;
		char c;
		ss >> id1 >> c >> id2 >> c >> money >> c >> time;
		suspects[id1].push_back(transfer(money, time, id2, id3));
		id3++;
		//��������������id���������еĽ���
	}
	cout << "data finish loaded..." << endl;
	//����������
	for (auto oneman = suspects.begin(); oneman != suspects.end(); oneman++)
	{
		int thismanid = oneman->first;  //���˵�id
		//�������˵����е�
		bool goodman = 1;
		for (int i = 0; i < oneman->second.size(); i++)
		{
			set<int> avoidRepeat;  //��ֹ�ظ�����
			stack<int> idStack;  //����������
			stack<int> shotList;  //ǹ������
			map<int, int> idLayer;  //ÿ��id�������еĲ��
			transfer tran = oneman->second[i];  //��ǰ��鶩��
			double curMoney = tran.money;
			string curTime = tran.time;
			int curId = tran.receiverID;
			idLayer[curId] = 1;  //��ǵ�һ��
			avoidRepeat.insert(tran.transferID);
			idStack.push(curId);
			bool find = 0;
			int count = 0;
			int id;  //��һ���������ķ����ߵ�id
			while (!idStack.empty() && !find)
			{
				count++;
				id = idStack.top();
				idStack.pop();
				shotList.push(id);
				if (id == thismanid)
				{
					find = count>1?1:0;
					break;
				}
				bool haveSuspect = 0;
				for (int j = 0; j < suspects[id].size(); j++)
				{
					if (avoidRepeat.count(suspects[id][j].transferID) != 0)
						continue;
					avoidRepeat.insert(suspects[id][j].transferID);
					if (suspects[id][j].money == curMoney)
					{
						if (timeSatisfy(curTime, suspects[id][j].time))
						{
							idLayer[suspects[id][j].receiverID] = idLayer[id] + 1;
							idStack.push(suspects[id][j].receiverID);
							haveSuspect = 1;
						}
					}
				}
				if (!haveSuspect)
				{
					shotList.pop();  //��������ת����û���⣬�������ɣ��Ƴ�ǽ������
					while (!shotList.empty()&&!idStack.empty()&&idLayer[shotList.top()]>=idLayer[idStack.top()])
					{
						shotList.pop();
					}
				}
			}
			if (find)
			{
				cout << "shot list: ";
				while (!shotList.empty())
				{
					cout << shotList.top() << "<-";
					shotList.pop();
				}
				cout << thismanid << endl;
				cout << "washing money: " << curMoney << endl;
				goodman = 0;
				system("pause");
			}
			
		}
		//if (goodman)
		//	cout << thismanid << "is a good man!" << endl;
	}
	system("pause");
	return 0;
}