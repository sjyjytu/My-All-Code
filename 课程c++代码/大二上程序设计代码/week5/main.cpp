#include <iostream>
#include<fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <regex>
#include <locale.h>
#include "main.h"
using namespace std;
void calOrderNum()
{
	clock_t start, finish;
	double total_time = 0;
	ifstream file;
	string order = "";
	int orderCount = 0;
	start = clock();
	for (int i = 0; i < 4; i++)
	{
		stringstream stream;
		stream << i;
		string fileName = "order" + stream.str() + ".txt";
		file.open(fileName, ios::in);
		if (!file)
			cerr << "open order fail!";
		while (!file.eof())
		{
			getline(file, order);
			orderCount++;
		}
		file.close();
	}
	finish = clock();
	total_time = (finish - start) / 1000;
	cout << "orderCount:" << orderCount << endl;
	cout << "totalTime:" << total_time << "s" << endl;
}
/*string findBuyerName(string id)
{
	string buyerName;
	ifstream file("buyer.0.0",ios::in);
	if (!file)
		cerr << "open buyer.0.0 fail!";
	string linecontent;
	while (!file.eof())
	{
		getline(file, linecontent);
		regex reg("buyerid:([0-9]|-)+");
		regex reg2("buyername:([0-9]|-)+");
		smatch sm;
		regex_search(linecontent, sm, reg);
		string buyerid = sm.str();
		buyerid.erase(0, 8);
		if (buyerid == id)
		{

		}
	}
}*/
void qOrder(string id)
{
	/*orderid,buyername,goodname,amount,price!!,amount*price,time*/
	clock_t start, finish;
	double total_time = 0;
	ifstream file;
	string order = "";
	bool found = 0;
	start = clock();
	string buyerid, goodid, amount;
	string buyername, goodname, price;
	for (int i = 0; i < 4; i++)
	{
		if (found)
			break;
		stringstream stream;
		stream << i;
		string fileName = "order" + stream.str() + ".txt";
		file.open(fileName, ios::in);
		if (!file)
			cerr << "open order fail!";
		while (!file.eof())
		{
			getline(file, order);
			regex reg("orderid:([0-9]+)");
			smatch sm;
			regex_search(order, sm, reg);
			string orderid = sm.str();
			orderid.erase(0, 8);
			if (orderid == id)
			{
				found = 1;
				regex reg2("buyerid:([0-9][a-z]|-)+");
				regex_search(order, sm, reg2);
				buyerid = sm.str().erase(0, 8);

				regex reg3("goodid:([0-9][a-z]|-)+");
				regex_search(order, sm, reg3);
				goodid = sm.str().erase(0, 7);

				regex reg4("amount:([0-9])+");
				regex_search(order, sm, reg4);
				amount = sm.str().erase(0, 7);
				break;
			}
		}
		file.close();
	}

}
void qBuyer(string id)
{

}
void qGood(string id)
{

}
int main()
{
	/*while (true)
	{
		cout << "The functions are as follows:" << endl;
		cout << "1.Calculate the total number of orders" << endl;
		cout << "2.Query an order detail by a given orderid" << endl;
		cout << "3.Query a buyer's data by a given buyerid" << endl;
		cout << "4.Query a good's data by a given goodid" << endl;
		cout << "Please choose:";
		int i;
		cin >> i;
		string id;
		switch (i)
		{
		case 1:
			calOrderNum();
			break;
		case 2:
			cout << "input id:";
			cin >> id;
			qOrder(id);
			break;
		case 3:
			cout << "input id:";
			cin >> id;
			qBuyer(id);
			break;
		case 4:
			cout << "input id:";
			cin >> id;
			qGood(id);
			break;
		default:
			cout << "input wrong!!";
			break;
		}
	}*/
	/*ifstream file("1.txt",ios::in);
	string s;
	getline(file, s);
	regex reg("[\u4e00-\u9fa5]+$");
	//regex reg2("orderid:([a-z0-9])+");
	smatch sm;
	regex_search(s, sm, reg);
	//string a = sm.str();
	//regex_search(s, sm, reg2);
	//string b = sm.str();
	cout << s <<"        "<< sm.str() << endl;
	getline(file, s);
	regex_search(s, sm, reg);
	cout << s << "        " << sm.str() << endl;
	getline(file, s);
	regex_search(s, sm, reg);
	cout << s << "        " << sm.str() << endl;
	file.close();
	//cout << b;
	system("pause");
	return 0;*/
	char * pre = setlocale(LC_ALL, "");
	cout << pre << endl;
	char *now = setlocale(LC_ALL, "chs");
	cout << now << endl;

	wchar_t ch[] = L"^[a-zA-Z0-9\u4e00-\u9fa5_]{0,29}$";
	wstring parten(ch);
	wregex re(parten);
	wstring str;
	while (wcin >> str)
	{
		wsmatch wsm;
		regex_search(str, wsm,re);
		wcout << wsm.str();
	}

	setlocale(LC_ALL, pre);
	char *repre = setlocale(LC_ALL, "");
	cout << repre << endl;

	return 0;
}