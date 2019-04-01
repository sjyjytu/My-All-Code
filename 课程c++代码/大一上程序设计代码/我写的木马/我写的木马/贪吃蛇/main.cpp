#include<windows.h>
#include<cstdio>
#include<deque>
using namespace std;
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
int g_nScore=0,g_nFood=1,g_nBack=2,g_nDiff=200;
struct Coord:COORD
{
    Coord(int _x,int _y)
    {
        X=_x;
        Y=_y;
    }
} g_nSize(16,16),pos(1,0),food(0,0);
deque<Coord> snake(1,food);
bool die(const Coord &cd)
{
    for(deque<Coord>::iterator i=snake.begin(); i!=snake.end(); ++i)
        if(i->X==cd.X&&i->Y==cd.Y)return 1;
    return cd.X<0||cd.X>=g_nSize.X||cd.Y<0||cd.Y>=g_nSize.Y;
}
void Wdraw(Coord cd)
{
    cd.X*=2;
    SetConsoleCursorPosition(hOut,cd);
    printf("■");
}
int SetMessage(const char *word="游戏很好玩？\n请联系wu.kan@foxmail.com",
               const WORD &wAttributes=MB_ICONINFORMATION,
               HWND hWnd=NULL,
               const char *title="WuK's DOS GAME LIB")
{
    return MessageBox(hWnd,word,title,wAttributes);
}
void SetFood(const int &n)
{
    g_nBack+=g_nFood;
    char ch_title[32]="贪吃蛇",ch_score[32]="";
    itoa(g_nScore+=snake.size()/3*g_nFood,ch_score,10);
    strcat(ch_title,ch_score);
    SetConsoleTitle(ch_title);
    while(die(food))food=Coord(rand()%g_nSize.X,rand()%g_nSize.Y);
    SetConsoleCursorPosition(hOut,Coord(food.X*2,food.Y));
    printf("%d",n);
}
int main()
{
    Coord cd(g_nSize.X*2,g_nSize.Y+2);
    SMALL_RECT rc= {1,1,cd.X,cd.Y};
    SetConsoleWindowInfo(hOut,1,&rc);
    SetConsoleScreenBufferSize(hOut,cd);
    SetConsoleCursorPosition(hOut,Coord(0,g_nSize.Y));
    printf("联系帅气的作者wu.kan@foxmail.com");
    SetFood(g_nFood=1);
    for(SetMessage("←↑↓→方向移动\nSpace暂停");; Sleep(g_nDiff))
    {
        if(GetAsyncKeyState(VK_SPACE))SetMessage();
        else if(GetAsyncKeyState(VK_UP))pos= pos.Y==1?pos:Coord(0,-1);
        else if(GetAsyncKeyState(VK_DOWN))pos= pos.Y==-1?pos:Coord(0,1);
        else if(GetAsyncKeyState(VK_LEFT))pos= pos.X==1?pos:Coord(-1,0);
        else if(GetAsyncKeyState(VK_RIGHT))pos= pos.X==-1?pos:Coord(1,0);
        Coord cd(snake.front().X+pos.X,snake.front().Y+pos.Y);
        if(die(cd))break;
        snake.push_front(cd);
        Wdraw(snake.front());
        if(snake.front().X==food.X&&snake.front().Y==food.Y)SetFood(g_nFood=rand()%3+1);
        if(g_nBack)g_nBack--;else
        {
            SetConsoleCursorPosition(hOut,Coord(snake.back().X*2,snake.back().Y));
            printf("  ");
            snake.pop_back();
        }
    }
    SetMessage("Game Over");
}
