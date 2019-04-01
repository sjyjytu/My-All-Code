#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <time.h>
#include <sstream>
#include <codecvt>
#include <Windows.h>
#include <locale>
#include <iomanip>

using namespace std;

std::wstring s2ws(const std::string& str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

struct man
{
	wstring buyername;
	int ordernum = 0;
	double payamount = 0;
	int orderNum[8] = { 0 };  //每个weekday下单数
	double payAmount[8] = { 0 };  //每个weekday总花费
	man() {}
	man(wstring ws) :buyername(ws) {}
};
struct gmsg
{
	string goodname;
	double price;
	int orderNum = 0;  //订单数
	int saledNum = 0;  //销量
	gmsg(){}
	gmsg(string s, double d):goodname(s),price(d){}
};
struct ordermsg
{
	string goodid;
	wstring buyerid;
	int amount;
	int weekday;
	ordermsg() {}
	ordermsg(string gid, wstring bid, int am, int wd) :goodid(gid), buyerid(bid), amount(am),weekday(wd) {}
};
struct GBlist
{
	map<string, gmsg> Good;
	map<wstring, man> Buyer;
	GBlist(){}
	void addGood(string gid,int am,string gname)
	{
		if (Good.find(gid) == Good.end())
			Good.insert(pair<string, gmsg>(gid, gmsg()));
		Good[gid].goodname = gname;
		Good[gid].saledNum += am;
	}
	void addBuyer(wstring buyerid, wstring buyername, double totalamount)
	{
		if (Buyer.find(buyerid) == Buyer.end())
			Buyer.insert(pair<wstring, man>(buyerid, man()));
		Buyer[buyerid].buyername = buyername;
		Buyer[buyerid].ordernum++;
		Buyer[buyerid].payamount += totalamount;
	}
	void top3good()
	{
		string top1id = "", top2id = "", top3id = "";
		int t1 = 0, t2 = 0, t3 = 0;
		map<string, gmsg>::iterator it;
		it = Good.begin();
		while (it != Good.end())
		{
			int num = it->second.saledNum;
			if (num > t3)
			{
				if (num > t2)
				{
					if (num > t1)
					{
						t3 = t2;
						top3id = top2id;
						t2 = t1;
						top2id = top1id;
						t1 = num;
						top1id = it->first;
					}
					else
					{
						t3 = t2;
						top3id = top2id;
						t2 = num;
						top2id = it->first;
					}
				}
				else
				{
					t3 = num;
					top3id = it->first;
				}
			}
			it++;
		}
		cout << setw(30) << top1id << setw(10) << t1 << setw(30) << Good[top1id].goodname << endl;
		cout << setw(30) << top2id << setw(10) << t2 << setw(30) << Good[top2id].goodname << endl;
		cout << setw(30) << top3id << setw(10) << t3 << setw(30) << Good[top3id].goodname << endl;
	}

	void top3buyer()
	{
		wstring top1id = L"", top2id = L"", top3id = L"";
		double t1 = 0, t2 = 0, t3 = 0;
		map<wstring, man>::iterator it;
		it = Buyer.begin();
		while (it != Buyer.end())
		{
			double num = it->second.payamount;
			if (num > t3)
			{
				if (num > t2)
				{
					if (num > t1)
					{
						t3 = t2;
						top3id = top2id;
						t2 = t1;
						top2id = top1id;
						t1 = num;
						top1id = it->first;
					}
					else
					{
						t3 = t2;
						top3id = top2id;
						t2 = num;
						top2id = it->first;
					}
				}
				else
				{
					t3 = num;
					top3id = it->first;
				}
			}
			it++;
		}
		wcout.imbue(locale("chs"));
		wcout << setw(30) << Buyer[top1id].buyername << setw(20) << Buyer[top1id].ordernum << setw(30) << t1 << endl;
		wcout << setw(30) << Buyer[top2id].buyername << setw(20) << Buyer[top2id].ordernum << setw(30) << t2 << endl;
		wcout << setw(30) << Buyer[top3id].buyername << setw(20) << Buyer[top3id].ordernum << setw(30) << t3 << endl;
	}
};
struct YMD  //年月日
{
	int year;
	int month;
	int day;
	YMD(){}
	YMD(int y,int m,int d):year(y),month(m),day(d){}
	string dateId()
	{
		stringstream s;
		s.clear();
		s << year << month << day;
		return s.str();
	}
};
void connectbuyeridname(map<wstring, man> &Buyer,string line, int i = 0)
{
	wstring_convert<codecvt_utf8<wchar_t>> conv;
	wstring linecontent = conv.from_bytes(line);
	size_t found = linecontent.find(L"buyerid:");
	if (found != std::wstring::npos)
		linecontent.erase(0, found + 8);
	else
	{
		cerr << "buyer" << i << ":not found buyerid!" << endl;
	}
	wstringstream ss;
	ss.clear();
	ss.str(linecontent);
	wstring buyerid;
	ss >> buyerid;

	found = linecontent.find(L"buyername:");
	if (found != std::wstring::npos)
		linecontent.erase(0, found + 10);
	else
	{
		cerr << "buyer" << i << ":not found buyername!" << endl;
		cerr << "line:" << line << endl;
	}
	ss.clear();
	ss.str(linecontent);
	wstring buyername;
	ss >> buyername;
	
	Buyer.insert(pair<wstring, man>(buyerid, man(buyername)));
}
void connectgoodidmsg(map<string, gmsg> &Good, string linecontent, int i = 0)
{
	size_t found = linecontent.find("goodid:");
	if (found != std::string::npos)
		linecontent.erase(0, found + 7);
	else
	{
		cerr << "good" << i << ":not found goodid!!" <<endl;
	}
	stringstream ss;
	ss.clear();
	ss.str(linecontent);
	string goodid;
	ss >> goodid;

	found = linecontent.find("good_name:");
	if (found != std::string::npos)
		linecontent.erase(0, found + 10);
	else
	{
		cerr << "good" << i << ":not found good_name!" << endl;
	}
	
	ss.clear();
	ss.str(linecontent);
	string goodname;
	ss >> goodname;

	found = linecontent.find("price:");
	if (found != std::string::npos)
		linecontent.erase(0, found + 6);
	else
	{
		cerr << "good" << i << ":not found price!" << endl;
	}
	
	ss.clear();
	ss.str(linecontent);
	double price;
	ss >> price;
	Good.insert(pair<string, gmsg>(goodid, gmsg(goodname, price)));
}
int main()
{
	wcout.setf(ios::left, ios::adjustfield);
	cout.setf(ios::left, ios::adjustfield);  //默认左对齐
	/*处理Buyer,得到的是wstring*/
	map<wstring, man> Buyer;  //buyerid,buyername
	ifstream file(L"buyer.0.0", ios::in);
	if (!file)
		cerr << "open buyer.0.0 fail!";
	string linecontent;
	while (!file.eof())
	{
		getline(file, linecontent);
		connectbuyeridname(Buyer, linecontent,0);
	}
	file.close();
	file.open(L"buyer.1.1", ios::in);
	if(!file)
		cerr << "open buyer.1.1 fail!";
	while (!file.eof())
	{
		getline(file, linecontent);
		connectbuyeridname(Buyer, linecontent,1);
	}
	file.close();

	/*处理Good,得到string*/
	map<string, gmsg> Good;
	for (int i = 0; i < 3; i++)
	{
		stringstream stream;
		stream << i;
		string fileName = "good." + stream.str() + "." + stream.str();
		file.open(fileName, ios::in);
		if (!file)
			cerr << "open good.txt fail!";
		while (!file.eof())
		{
			getline(file, linecontent);
			connectgoodidmsg(Good, linecontent,i);
		}
		file.close();
	}

	/*处理order*/
	map<string, ordermsg> Order;
	map<string, GBlist> Date;
	for (int i = 0; i < 4; i++)
	{
		stringstream stream;
		stream.clear();
		stream << i;
		string fileName = "order" + stream.str() + ".txt";
		file.open(fileName, ios::in);
		if (!file)
			cerr << "open order" << i << " fail!";
		while (!file.eof())
		{
			getline(file, linecontent);
			size_t found = linecontent.find("orderid:");
			if (found != std::string::npos)
				linecontent.erase(0, found + 8);
			else
			{
				cerr << "order" << i << ":not found orderid!" << endl;
			}
			stringstream ss;
			ss.clear();
			ss.str(linecontent);
			string orderid;
			ss >> orderid;

			found = linecontent.find("createtime:");
			if (found != std::string::npos)
				linecontent.erase(0, found + 11);
			else
			{
				cerr << "order" << i << ":not found createtime!" <<endl;
			}
			ss.clear();
			ss.str(linecontent);
			time_t createtime;
			ss >> createtime;

			found = linecontent.find("buyerid:");
			if (found != std::string::npos)
				linecontent.erase(0, found + 8);
			else
			{
				cerr << "order" << i << ":not found buyerid!"<<endl;
			}
			ss.clear();
			ss.str(linecontent);
			string buyerid;
			ss >> buyerid;
			wstring Buyerid = s2ws(buyerid);  //转换为wstring类型

			found = linecontent.find("goodid:");
			if (found != std::string::npos)
				linecontent.erase(0, found + 7);
			else
			{
				cerr << "order" << i << ":not found goodid!!"<<endl;
			}
			ss.clear();
			ss.str(linecontent);
			string goodid;
			ss >> goodid;

			found = linecontent.find("amount:");
			if (found != std::string::npos)
				linecontent.erase(0, found + 7);
			else
			{
				cerr << "order" << i << "not found amount!" << endl;
			}
			ss.clear();
			ss.str(linecontent);
			int amount;
			ss >> amount;
			Good[goodid].orderNum++;
			Good[goodid].saledNum += amount;
			struct tm *local;
			local = gmtime(&createtime);
			int weekday = local->tm_wday;
			Buyer[Buyerid].orderNum[weekday]++;
			Buyer[Buyerid].ordernum++;
			int total_amount = amount * Good[goodid].price;
			Buyer[Buyerid].payAmount[weekday] += total_amount;
			Buyer[Buyerid].payamount += total_amount;
			Order.insert(pair<string, ordermsg>(orderid, ordermsg(goodid, Buyerid, amount,weekday)));

			YMD ymd(local->tm_year, local->tm_mon, local->tm_mday);
			string tmp = ymd.dateId();
			/*记录每一天*/
			if (Date.find(tmp) != Date.end())
				Date.insert(pair<string, GBlist>(tmp, GBlist()));  //如果没有那一天，则+上
			Date[tmp].addGood(goodid, amount,Good[goodid].goodname);
			Date[tmp].addBuyer(Buyerid, Buyer[Buyerid].buyername, total_amount);
		}
		file.close();
	}
	
	double totaltime;
	/*用户交互*/
	while (true)
	{
		cout << endl;
		cout << "The functions are as follows:" << endl;
		cout << "1.Calculate the total number of orders" << endl;
		cout << "2.Query an order detail by a given orderid" << endl;
		cout << "3.Query a buyer's data by a given buyerid" << endl;
		cout << "4.Query a good's data by a given goodid" << endl;
		cout << "5.Comsumption information of each weekday" << endl;
		cout << "6.Get Top3" << endl;
		cout << "Please choose:";
		int i;
		cin >> i;
		string id;
		wstring buyerid;
		clock_t start, finish;
		
		switch (i)
		{
		case 1:
			start = clock();
			cout << "get out here please." << endl;
			break;
		case 2:
			cout << "input orderid:";
			cin >> id;
			start = clock();
			if (Order.find(id) != Order.end())
			{
				cout << "orderid:" << id << endl;
				wcout.imbue(locale("chs"));
				wcout << L"buyername:" << Buyer[Order[id].buyerid].buyername << endl;
				cout << "goodname:" << Good[Order[id].goodid].goodname << endl;
				cout << "amount:" << Order[id].amount << endl;
				cout << "price:" << Good[Order[id].goodid].price << endl;
				cout << "total money:" << Order[id].amount *Good[Order[id].goodid].price << endl;
			}
			else
				cout << "Not Found" << endl;
			break;
		case 3:
			cout << "input buyerid:";
			wcin >> buyerid;
			start = clock();
			wcout.imbue(locale("chs"));
			if (Buyer.find(buyerid) != Buyer.end())
			{
				wcout << L"buyerid:" << buyerid << endl;
				wcout << L"buyername:" << Buyer[buyerid].buyername << endl;
				cout << "order number:" << Buyer[buyerid].ordernum << endl;
				cout << "total consume:" << Buyer[buyerid].payamount << endl;
			}
			else
				cout << "Not Found" << endl;
			break;
		case 4:
			cout << "input goodid:";
			cin >> id;
			start = clock();
			if (Good.find(id) != Good.end())
			{
				cout << "goodid:" << id << endl;
				cout << "goodname:" << Good[id].goodname << endl;
				cout << "order number:" << Good[id].orderNum << endl;
				cout << "saled number:" << Good[id].saledNum << endl;
			}
			else
				cout << "Not Found" << endl;
			break;
		case 5:
			cout << "input buyerid:";
			wcin >> buyerid;
			start = clock();
			wcout.imbue(locale("chs"));
			if (Buyer.find(buyerid) != Buyer.end())
			{
				wcout << L"buyerid:" << buyerid << endl;
				wcout << L"buyername:" << Buyer[buyerid].buyername << endl;
				for (int i = 1; i < 8; i++)
				{
					double average = 0;
					if (Buyer[buyerid].orderNum[i] != 0)
						average = Buyer[buyerid].payAmount[i] / Buyer[buyerid].orderNum[i];
					wcout << L"星期" << i << ":" << Buyer[buyerid].orderNum[i] << "  " << Buyer[buyerid].payAmount[i] << "  " << average << endl;
				}
			}
			else
				cout << "Not Found" << endl;
			break;
		case 6:
		{
			cout << "input date as:xxxx xx xx"<<endl;
			int y, m, d;
			cin >> y >> m >> d;
			start = clock();
			y -= 1900;
			m -= 1;
			YMD date(y, m, d);
			string tmp = date.dateId();
			if (Date.find(tmp) == Date.end())
				cout << "no order" << endl;
			else
			{
				cout << setw(30) << "Most popular good" << setw(20) << "Quantity" << setw(30) << "Good name" << endl;
				Date[tmp].top3good();
				cout << endl;
				cout << setw(30) << "Richest buyer" << setw(20) << "order number" << setw(30) << "total amount" << endl;
				Date[tmp].top3buyer();
			}
		}
		break;
		default:
			start = clock();
			cout << "input wrong!!";
			break;
		}
		finish = clock();
		totaltime = finish - start;
		cout << "time consuming:" << totaltime << "ms" << endl;
	}
	system("pause");
	return 0;
}


