#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>

#define FrameX 4   //游戏窗口左上角的X轴坐标
#define FrameY 4   //游戏窗口左上角的Y轴坐标
#define Frame_height  20 //游戏窗口的高度
#define Frame_width   20 //游戏窗口的宽度
//定义全局变量
int i, j;
int a[2];     //用于记住蛇尾坐标，其中a[0]、a[1]分别表示横、竖坐标
struct Snake		//声明蛇的结构体
{
	int x[100];    //蛇的横坐标，x[0]表示蛇尾的横坐标，x[N-1]表示蛇头的横坐标
	int y[100];    //蛇的竖坐标，y[0]表示蛇尾的竖坐标，y[N-1]表示蛇头的竖坐标
	int count;    //蛇吃$的个数
	int length;    //蛇的长度
	int speed;    //蛇的速度
};
struct Food
{
	int x;     //食物的横坐标
	int y;     //食物的竖坐标
};
void GameStart();
void GameOver();
int main() {
	system("cls");
	GameStart();
	GameOver();
	return 0;
}
void gotoxy(HANDLE hOut, int x, int y) {
	COORD pos;		//定义光标
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);	//将光标定位到那个位置
}

void make_frame() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 13);
	printf("按Esc 退出游戏");
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 15);
	printf("长按方向键：加速");
	gotoxy(hOut, FrameX, FrameY);
	printf("╔");
	gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY);
	printf("╗");
	gotoxy(hOut, FrameX, FrameY + Frame_height);
	printf("╚");
	gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + Frame_height);
	printf("╝");
	for (i = 2; i < 2 * Frame_width - 2; i += 2)
	{
		gotoxy(hOut, FrameX + i, FrameY);
		printf("═");         //打印上横框
	}
	for (i = 2; i < 2 * Frame_width - 2; i += 2)
	{
		gotoxy(hOut, FrameX + i, FrameY + Frame_height);
		printf("═");         //打印下横框
	}
	for (i = 1; i < Frame_height; i++)
	{
		gotoxy(hOut, FrameX, FrameY + i);
		printf("║");         //打印左竖框
	}
	for (i = 1; i < Frame_height; i++)
	{
		gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + i);
		printf("║");         //打印右竖框
	}
	gotoxy(hOut, FrameX + Frame_width - 5, FrameY - 2);
	printf("贪吃蛇 Version 1.0.0 Coder.@");
}
void GameOver() {
	system("cls");		//清屏
	printf("\n\n\n\n\n\n\n\n\t\t\t\tGameOver\n\n\n");
	Sleep(2000);
	_getch();
}
void printInformation(HANDLE hOut, struct Snake *snake, struct Food *food)
{
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 1);
	printf("level : %d", snake->count / 5 + 1);    //打印游戏等级
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 3);
	printf("score : %d", 10 * snake->count);    //打印游戏得分
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 5);
	printf("eat food : %d", snake->count);    //打印产生食物个数
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 7);
	printf("speed : %dms", snake->speed);    //打印游戏速度
}
void origin_snake(struct Snake *snake) {
	snake->x[0] = FrameX + 2;
	snake->y[0] = FrameY + Frame_height / 2;
	snake->speed = 300;
	snake->length = 3;
	snake->count = 0;
	for (i = 1; i < snake->length; i++) {
		snake->x[i] = snake->x[i - 2] + 2;
		snake->y[i] = snake->y[i - 1];
	}
}
void movement(HANDLE hOut, struct Snake *snake) {
	gotoxy(hOut, snake->x[0], snake->y[0]);
	printf(" ");
	for (i = 1; i < snake->length; i++) {
		snake->x[i - 1] = snake->x[i];
		snake->y[i - 1] = snake->y[i];
	}
}
void PrintSnake(HANDLE hOut, struct Snake *snake) {
	for (i = 0; i < snake->length; i++) {
		gotoxy(hOut, snake->x[i], snake->y[i]);
		if (i == 0) {
			printf("·");		//尾部
		}
		else if (i == snake->length - 1) {
			printf("@");
		}
		else {
			printf("*");
		}
	}
}
void put_food(HANDLE hOut, struct Snake *snake, struct Food *food) {
	srand((unsigned)time(NULL));
	while (1) {
		food->x = rand() % (Frame_width - 1);
		food->y = rand() % Frame_height;
		if (food->x == 0 || food->y == 0) {
			continue;
		}
		food->x = 2 * food->x + FrameX;
		food->y += FrameY;
		for (i = 0; i < snake->length; i++) {
			if (food->x == snake->x[i] && food->y == snake->y[i]) {		//判断是否与蛇身重合
				break;
			}
		}
		if (i == snake->length) {
			gotoxy(hOut, food->x, food -> y);
			printf("$");
			break;
		}
	}
}
void eat_food(HANDLE hOut, struct Snake *snake, struct Food *food) {
	if (snake->x[snake->length - 1] == food->x&&snake->y[snake->length - 1] == food->y) {
		snake->length++;		//长大了！！
		for (i = snake->length - 1; i >= 1; i--) {
			snake->x[i] = snake->x[i - 1];
			snake->y[i] = snake->y[i - 1];
		}
		snake->x[0] = a[0];
		snake->y[0] = a[1];
		put_food(hOut, snake, food);
		snake->count++;
		if (snake->count % 5 == 0) {
			snake->speed -= 50;
		}
	}
}
void through_wall(HANDLE hOut, struct Snake *snake, char ch)
{
	if (ch == 72 && snake->y[snake->length - 1] == FrameY)
	{
		snake->y[snake->length - 1] = FrameY + Frame_height - 1; //上穿墙
	}
	if (ch == 80 && snake->y[snake->length - 1] == FrameY + Frame_height)
	{
		snake->y[snake->length - 1] = FrameY + 1;    //下穿墙
	}
	if (ch == 75 && snake->x[snake->length - 1] == FrameX)
	{
		snake->x[snake->length - 1] = FrameX + 2 * Frame_width - 4; //左穿墙
	}
	if (ch == 77 && snake->x[snake->length - 1] == FrameX + 2 * Frame_width - 2)
	{
		snake->x[snake->length - 1] = FrameX + 2;    //右穿墙
	}
}
int life(struct Snake *snake) {
	for (i = 0; i < snake->length - 1; i++) {
		if (snake->x[snake->length - 1] == snake->x[i] && snake->y[snake->length - 1] == snake->y[i]) {
			return 0;
		}
	}
	return 1;
}
void GameStart() {
	unsigned char ch = 77;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	struct Snake s, *snake = &s;
	struct Food f, *food = &f;
	make_frame();
	origin_snake(snake);
	put_food(hOut, snake, food);
	while (1) {
		printInformation(hOut, snake, food);
		a[0] = snake->x[0];
		a[1] = snake->y[0];
		j = 0;
		if (_kbhit()) {
			ch = _getch();
			if (_kbhit()) {
				Sleep(20);
				j = 1;
			}
		}
		switch (ch) {
			case 72:{
				movement(hOut, snake);
				snake->y[snake->length - 1] -= 1; //上
				break;
			}
			case 80:{
				movement(hOut, snake);
				snake->y[snake->length - 1] += 1; //下
				break;
			}
			case 75:{
				movement(hOut, snake);
				snake->x[snake->length - 1] -= 2; //左
				break;
			}
			case 77:{
				movement(hOut, snake);
				snake->x[snake->length - 1] += 2; //右
				break;
			}
		}
		through_wall(hOut, snake, ch);
		eat_food(hOut, snake, food);
		PrintSnake(hOut, snake);
		if (life(snake) == 0 ||ch == 27 || snake->speed == 50) {
			gotoxy(hOut, FrameX + Frame_width - 2, FrameY + Frame_height / 2 - 1);
			printf("GG");
			Sleep(2000);
			break;
		}
		if (j == 0) {
			Sleep(snake->speed);
		}
		else {
			Sleep(10);
		}
	}
}
