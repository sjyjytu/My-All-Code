#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <vector>

#define pic_num 20//��ͬͼ�������
using std::vector;
class Map
{
private:
	static int mapsize;//��ͼ�ĳ�or���������߿�
	int mix_time;//���ҵĴ���
	int x_size;//��
	int y_size;//��
	void add_rim();//�ӱ߿�
	void mix_up();//����
public:
	int left_icon;//���滹ʣ�¶��ٶ�ͼ��
	vector<vector<int> >box;//��¼ÿ��ͼƬ��λ��
	static int get_mapsize();//�õ���ͼ��С
	static void set_mapsize(int);//���õ�ͼ��С
	int create_randnum(int n, int m = 0);//���������
	void set_box();
	int **new_map;//��ά���飬�߼���ͼ
	void generate_map();//���»���
	Map();
	Map(const Map&a);
	void copyFrom(const Map&a);
	~Map();

};

#endif // !MAP_H
