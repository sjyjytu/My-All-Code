#ifndef PRESS_POS
#define PRESS_POS
class press_pos
{
public:
	press_pos(int a = 0, int b = 0);
	~press_pos();
	void set_pos(int a, int b);
	bool operator==(const press_pos &pos1)const;
	bool operator!=(const press_pos &pos1)const;
	const int getx();
	const int gety();
private:
	int x;
	int y;
};

#endif // !PRESS_POS