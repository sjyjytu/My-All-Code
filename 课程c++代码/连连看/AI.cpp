#include "AI.h"



AI::AI():findit(0),posk1(0),posk2(0)
{
}


AI::~AI()
{
}

void AI::ai_find(Map & mymap, Judge & judge)
{
	findit = 0;
	for (int i = 0; i < pic_num; i++)
	{
		if (!mymap.box[i].empty())
		{
			for (int j = 0; j < mymap.box[i].size(); ++j)
			{
				for (int k = j + 1; k < mymap.box[i].size(); ++k)
				{
					judge.have_a_judge(press_pos(mymap.box[i][j] / 100, mymap.box[i][j] % 100), press_pos(mymap.box[i][k] / 100, mymap.box[i][k] % 100), mymap.new_map);
					if (judge.get_isok())
					{
						findit = 1;
						posk1 = mymap.box[i][j];
						posk2 = mymap.box[i][k];
						return;
					}
				}
			}
		}
	}
}

bool AI::get_findit()
{
	return findit;
}

int AI::get_posk1()
{
	return posk1;
}

int AI::get_posk2()
{
	return posk2;
}
