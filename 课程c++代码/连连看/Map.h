#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <vector>

#define pic_num 20//不同图标的种数
using std::vector;
class Map
{
private:
	static int mapsize;//地图的长or宽，不包括边框
	int mix_time;//打乱的次数
	int x_size;//长
	int y_size;//宽
	void add_rim();//加边框
	void mix_up();//打乱
public:
	int left_icon;//保存还剩下多少对图标
	vector<vector<int> >box;//记录每种图片的位置
	static int get_mapsize();//得到地图大小
	static void set_mapsize(int);//设置地图大小
	int create_randnum(int n, int m = 0);//创建随机数
	void set_box();
	int **new_map;//二维数组，逻辑地图
	void generate_map();//更新换代
	Map();
	Map(const Map&a);
	void copyFrom(const Map&a);
	~Map();

};

#endif // !MAP_H
