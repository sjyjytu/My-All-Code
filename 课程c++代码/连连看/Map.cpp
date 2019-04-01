#include "Map.h"

/*��ʼ��map_size*/
int Map::mapsize = 4;

int Map::create_randnum(int n, int m)
{
	//������m<= <=n�������
	return rand() % (n - m + 1) + m;
}

void Map::set_box()
{
	//��ʼ��/���box������Ϊ20
	box.assign(pic_num, vector<int>());
	//���µ�ͼ����box
	for (int i = 1; i <= mapsize; i++)
	{
		for (int j = 1; j <= mapsize; j++)
		{
			//ע��box������0-pic_num-1,�����±���new_map[i][j]-1.
			int k = new_map[i][j] - 1;
			if (k > -1)	box[k].push_back(i * 100 + j);
		}
	}
}

void Map::add_rim()
{
	//��new_map�ı߿���Ϊ0
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
	//��new_map����mix_time*10��
	for (int i = 0; i < mix_time * 10; i++)
	{
		//����1-mapsize������
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
		/*��delete���ɵ�*/
		for (int i = 0; i < y_size; i++)
		{
			delete[]new_map[i];
		}
		delete[]new_map;
		/*�����µ�*/
		x_size = mapsize + 2;
		y_size = mapsize + 2;
		//��̬������ά����new_map
		new_map = new int*[x_size];
		for (int i = 0; i < x_size; i++)
			new_map[i] = new int[y_size];
	}
	
	//��0-picnum���������ֵ��new_map�����벿�֣�1-18��,���ұ�֤�ɶԳ���
	for (int i = 1; i < mapsize / 2 + 1; i++)
	{
		for (int j = 1; j <= mapsize; j++)
		{
			int a = create_randnum(pic_num, 1);//��ʱ����һ��1-pic_num�������
			new_map[i][j] = a;
			new_map[mapsize - i + 1][j] = a;
		}
	}

	//Ϊnew_map�ӱ߿�
	add_rim();
	//����
	mix_up();
	//װ��box��
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
	//�������
	srand((unsigned int)time(NULL));
	//��̬������ά����new_map
	new_map = new int*[x_size];
	for (int i = 0; i < x_size; i++)
		new_map[i] = new int[y_size];
	//��װ���ĺ���,��new_map��ֵ���ӱ߿򣬴��ҡ�
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
	//��������
	for (int i = 0; i < y_size; i++)
	{
		delete[]new_map[i];
	}
	delete[]new_map;
}
