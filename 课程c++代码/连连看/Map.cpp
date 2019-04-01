#include "Map.h"

/*初始化map_size*/
int Map::mapsize = 4;

int Map::create_randnum(int n, int m)
{
	//创建出m<= <=n的随机数
	return rand() % (n - m + 1) + m;
}

void Map::set_box()
{
	//初始化/清空box，长度为20
	box.assign(pic_num, vector<int>());
	//将新地图存入box
	for (int i = 1; i <= mapsize; i++)
	{
		for (int j = 1; j <= mapsize; j++)
		{
			//注意box的行是0-pic_num-1,所以下标是new_map[i][j]-1.
			int k = new_map[i][j] - 1;
			if (k > -1)	box[k].push_back(i * 100 + j);
		}
	}
}

void Map::add_rim()
{
	//将new_map的边框设为0
	for (int i = 1; i < x_size - 1; i++)
	{
		new_map[i][0] = 0;
		new_map[i][y_size - 1] = 0;
	}
	for (int i = 0; i < y_size; i++)
	{
		new_map[0][i] = 0;
		new_map[x_size - 1][i] = 0;
	}
}

void Map::mix_up()
{
	//将new_map打乱mix_time*10次
	for (int i = 0; i < mix_time * 10; i++)
	{
		//创建1-mapsize的坐标
		int x1 = create_randnum(mapsize, 1);
		int y1 = create_randnum(mapsize, 1);
		int x2 = create_randnum(mapsize, 1);
		int y2 = create_randnum(mapsize, 1);
		if (x1 != x2 || y1 != y2)
			std::swap(new_map[x1][y1], new_map[x2][y2]);
	}
}

void Map::generate_map()
{
	if (mapsize > 4)
	{
		/*先delete掉旧的*/
		for (int i = 0; i < y_size; i++)
		{
			delete[]new_map[i];
		}
		delete[]new_map;
		/*创建新的*/
		x_size = mapsize + 2;
		y_size = mapsize + 2;
		//动态创建二维数组new_map
		new_map = new int*[x_size];
		for (int i = 0; i < x_size; i++)
			new_map[i] = new int[y_size];
	}
	
	//将0-picnum的数随机赋值给new_map的中央部分（1-18）,并且保证成对出现
	for (int i = 1; i < mapsize / 2 + 1; i++)
	{
		for (int j = 1; j <= mapsize; j++)
		{
			int a = create_randnum(pic_num, 1);//临时储存一个1-pic_num的随机数
			new_map[i][j] = a;
			new_map[mapsize - i + 1][j] = a;
		}
	}

	//为new_map加边框
	add_rim();
	//打乱
	mix_up();
	//装入box中
	set_box();
}

int Map::get_mapsize()
{
	return mapsize;
}

void Map::set_mapsize(int size)
{
	mapsize = size;
}

Map::Map():mix_time(mapsize * mapsize / 2), x_size(mapsize+2),y_size(mapsize+2),left_icon(mapsize*mapsize/2)
{
	//随机种子
	srand((unsigned int)time(NULL));
	//动态创建二维数组new_map
	new_map = new int*[x_size];
	for (int i = 0; i < x_size; i++)
		new_map[i] = new int[y_size];
	//包装过的函数,给new_map赋值并加边框，打乱。
	generate_map();
}

Map::Map(const Map &a)
{
	new_map = new int*[a.mapsize+2];
	for (int i = 0; i < a.mapsize + 2; i++)
		new_map[i] = new int[a.mapsize + 2];
	copyFrom(a);
}

void Map::copyFrom(const Map & a)
{
	for (int i = 0; i < a.mapsize + 2; i++)
	{
		for (int j = 0; j < a.mapsize + 2; j++)
		{
			new_map[i][j] = a.new_map[i][j];
		}
	}

	mix_time = a.mix_time;
	x_size = a.x_size;
	y_size = a.y_size;
	left_icon = a.left_icon;
	set_box();
}


Map::~Map()
{
	//析构函数
	for (int i = 0; i < y_size; i++)
	{
		delete[]new_map[i];
	}
	delete[]new_map;
}
