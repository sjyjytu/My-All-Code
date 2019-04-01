#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>

#define FrameX 4   //��Ϸ�������Ͻǵ�X������
#define FrameY 4   //��Ϸ�������Ͻǵ�Y������
#define Frame_height  20 //��Ϸ���ڵĸ߶�
#define Frame_width   20 //��Ϸ���ڵĿ��
//����ȫ�ֱ���
int i, j;
int a[2];     //���ڼ�ס��β���꣬����a[0]��a[1]�ֱ��ʾ�ᡢ������
struct Snake		//�����ߵĽṹ��
{
	int x[100];    //�ߵĺ����꣬x[0]��ʾ��β�ĺ����꣬x[N-1]��ʾ��ͷ�ĺ�����
	int y[100];    //�ߵ������꣬y[0]��ʾ��β�������꣬y[N-1]��ʾ��ͷ��������
	int count;    //�߳�$�ĸ���
	int length;    //�ߵĳ���
	int speed;    //�ߵ��ٶ�
};
struct Food
{
	int x;     //ʳ��ĺ�����
	int y;     //ʳ���������
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
	COORD pos;		//������
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);	//����궨λ���Ǹ�λ��
}

void make_frame() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 13);
	printf("��Esc �˳���Ϸ");
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 15);
	printf("���������������");
	gotoxy(hOut, FrameX, FrameY);
	printf("�X");
	gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY);
	printf("�[");
	gotoxy(hOut, FrameX, FrameY + Frame_height);
	printf("�^");
	gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + Frame_height);
	printf("�a");
	for (i = 2; i < 2 * Frame_width - 2; i += 2)
	{
		gotoxy(hOut, FrameX + i, FrameY);
		printf("�T");         //��ӡ�Ϻ��
	}
	for (i = 2; i < 2 * Frame_width - 2; i += 2)
	{
		gotoxy(hOut, FrameX + i, FrameY + Frame_height);
		printf("�T");         //��ӡ�º��
	}
	for (i = 1; i < Frame_height; i++)
	{
		gotoxy(hOut, FrameX, FrameY + i);
		printf("�U");         //��ӡ������
	}
	for (i = 1; i < Frame_height; i++)
	{
		gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + i);
		printf("�U");         //��ӡ������
	}
	gotoxy(hOut, FrameX + Frame_width - 5, FrameY - 2);
	printf("̰���� Version 1.0.0 Coder.@");
}
void GameOver() {
	system("cls");		//����
	printf("\n\n\n\n\n\n\n\n\t\t\t\tGameOver\n\n\n");
	Sleep(2000);
	_getch();
}
void printInformation(HANDLE hOut, struct Snake *snake, struct Food *food)
{
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 1);
	printf("level : %d", snake->count / 5 + 1);    //��ӡ��Ϸ�ȼ�
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 3);
	printf("score : %d", 10 * snake->count);    //��ӡ��Ϸ�÷�
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 5);
	printf("eat food : %d", snake->count);    //��ӡ����ʳ�����
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 7);
	printf("speed : %dms", snake->speed);    //��ӡ��Ϸ�ٶ�
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
			printf("��");		//β��
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
			if (food->x == snake->x[i] && food->y == snake->y[i]) {		//�ж��Ƿ��������غ�
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
		snake->length++;		//�����ˣ���
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
		snake->y[snake->length - 1] = FrameY + Frame_height - 1; //�ϴ�ǽ
	}
	if (ch == 80 && snake->y[snake->length - 1] == FrameY + Frame_height)
	{
		snake->y[snake->length - 1] = FrameY + 1;    //�´�ǽ
	}
	if (ch == 75 && snake->x[snake->length - 1] == FrameX)
	{
		snake->x[snake->length - 1] = FrameX + 2 * Frame_width - 4; //��ǽ
	}
	if (ch == 77 && snake->x[snake->length - 1] == FrameX + 2 * Frame_width - 2)
	{
		snake->x[snake->length - 1] = FrameX + 2;    //�Ҵ�ǽ
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
				snake->y[snake->length - 1] -= 1; //��
				break;
			}
			case 80:{
				movement(hOut, snake);
				snake->y[snake->length - 1] += 1; //��
				break;
			}
			case 75:{
				movement(hOut, snake);
				snake->x[snake->length - 1] -= 2; //��
				break;
			}
			case 77:{
				movement(hOut, snake);
				snake->x[snake->length - 1] += 2; //��
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
