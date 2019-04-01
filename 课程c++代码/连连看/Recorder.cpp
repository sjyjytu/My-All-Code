#include "Recorder.h"



Recorder::Recorder():last_pos(0)
{
}


Recorder::~Recorder()
{
}

void Recorder::clear_operation(int n)
{
	stringstream ss;
	ss << n;
	string add = "operation" + ss.str() + ".txt";
	file.open(add, fstream::out | ios_base::trunc);
	if (!file) {
		cerr << "open operation.txt wrong!";
		return;
	}
	file.close();
}

void Recorder::save_operation(Judge &judge,int n)
{
	stringstream ss;
	ss << n;
	string add = "operation" + ss.str() + ".txt";
	file.open(add, ios::app);
	if (!file) {
		cerr << "open operation.txt wrong!";
		return;
	}
	for (int i = 0; i < 5; i++)
	{
		file << judge.current_salient[i] << "  ";
	}
	file << endl;
	file.close();
}

void Recorder::save_now(Map & mymap,int temp_time,int scores,int lv, int pn, int bn, int pt, int svn)
{
	stringstream ss;
	ss << svn;
	if (pt == 0)//保存读档
	{
		string add = "save_map" + ss.str() + ".txt";
		file.open(add, fstream::out | ios_base::trunc);//打开并清空
		if (!file) {
			cerr << "open save_map.txt wrong!";
			return;
		}
	}
	else if (pt == 1)//保存回放
	{
		string add = "replay_map" + ss.str() + ".txt";
		file.open(add, fstream::out | ios_base::trunc);;//打开并清空
		if (!file) {
			cerr << "open save_map.txt wrong!";
			return;
		}
	}
	
	/*存地图大小 left_icon  tempt_time scores level promp_num bomb_num*/
	file << mymap.get_mapsize() << ' '<<mymap.left_icon << ' '<<temp_time<< ' ' <<scores<< ' ' << lv << ' ' << pn << ' ' << bn <<endl;
	/*存有边框的*/
	for (int i = 0; i < mymap.get_mapsize() + 2; i++)
	{
		for (int j = 0; j < mymap.get_mapsize() + 2; j++)
		{
			file <<' '<< mymap.new_map[i][j];
		}
		file << endl;
	}
	
	
	file.close();
}

void Recorder::read_map(Map &mymap,int &temp_time, int &scores,int &lv, int &pn, int &bn,int pattern,int readn)
{
	/*int 转 string*/
	stringstream ss;
	ss << readn;
	if (pattern == 0)//打开save_map(readn).txt,读档模式
	{
		/*读档，有边框*/
		string add = "save_map" + ss.str() + ".txt";
		file.open(add, ios::in);//打开
		if (!file) {
			cerr << "open save_map.txt wrong!";
			return;
		}
	}
	if (pattern == 1)//打开map(readn).txt,回放模式
	{
		/*读档，有边框*/
		
		string add = "replay_map" + ss.str() + ".txt";
		file.open(add, ios::in);//打开第readn个map.txt
		if (!file) {
			cerr << "open map wrong!";
			return;
		}
	}
	
	/*先delete掉旧的*/
	for (int i = 0; i < mymap.get_mapsize()+2; i++)
	{
		delete[]mymap.new_map[i];
	}
	delete[]mymap.new_map;
	/*读地图大小 left_icon  tempt_time scores level promp_num bomb_num*/
	int map_size;
	file >> map_size;
	mymap.set_mapsize(map_size);
	file >> mymap.left_icon >> temp_time >> scores >> lv >> pn >> bn;
	/*创建新的*/
	mymap.new_map = new int*[map_size+2];
	for (int i = 0; i < map_size + 2; i++)
		mymap.new_map[i] = new int[map_size + 2];

	/*读地图数值*/
	for (int i = 0; i < mymap.get_mapsize() + 2; i++)
	{
		for (int j = 0; j < mymap.get_mapsize() + 2; j++)
		{
			file >> mymap.new_map[i][j];
		}
	}
	/*还原box*/
	mymap.set_box();
	file.close();
}

void Recorder::read_oper(int n)
{
	stringstream ss;
	ss << n;
	string add = "operation" + ss.str() + ".txt";
	file.open(add, ios::in);
	file.seekg(last_pos, ios::beg);
	for (int i = 0; i < 5; i++)
	{
		file >> operations[i];
	}
	last_pos = file.tellg();
	file.close();
}
