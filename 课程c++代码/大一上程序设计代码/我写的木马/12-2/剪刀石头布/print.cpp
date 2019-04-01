#include "head.h"

static int win_cnt=0,lose_cnt=0,tie_cnt=0;
void prn_game_status()
{
    cout<<endl;
    cout<<"game status:"<<endl;
    cout<<"win:"<<win_cnt<<endl;
    cout<<"lose:"<<lose_cnt<<endl;
    cout<<"tie:"<<tie_cnt<<endl;
    cout<<"total:"<<win_cnt+lose_cnt+tie_cnt<<endl;
}

void prn_help()
{
    cout<<endl
        <<"the following characters can be used:\n"
        <<"p for paper\n"
        <<"r for rock\n"
        <<"s for scissor\n"
        <<"h for help\n"
        <<"g for game status\n"
        <<"q quit the game\n";
}
void report (outcome result)
{
    switch(result)
    {
        case win : ++win_cnt;cout<<"you win."<<endl;break;
        case lose : ++lose_cnt;cout<<"you lose."<<endl;break;
        case tie : ++tie_cnt;cout<<"a tie."<<endl;break;
    }
}
