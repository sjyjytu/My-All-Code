#include "head.h"

int main(void)
{
    outcome result;
    p_r_s player_choice,machine_choice;
    srand(time(NULL));

    while((player_choice=selection_by_player())!=quit)
      switch(player_choice){
        case paper:   case rock:   case scissor:
           machine_choice=selection_by_machine();
           result=compare(player_choice,machine_choice);
           report(result);break;
        case game:prn_game_status();break;
        case help:prn_help();break;}
    prn_game_status();
  return 0;
}
