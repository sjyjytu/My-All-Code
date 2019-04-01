#ifndef AI_H
#define AI_H
#include "Judge.h"
class AI
{
private:
	bool findit;
	int posk1;
	int posk2;
public:
	AI();
	~AI();
	void ai_find(Map &mymap, Judge &judge);
	bool get_findit();
	int get_posk1();
	int get_posk2();
};

#endif // !AI_H