#include "head.h"

outcome compare(p_r_s player_choice,p_r_s machine_choice)
{
    outcome result;
    if (player_choice==machine_choice) return tie;
    switch (player_choice)
    {
    case paper:
        result=(machine_choice==rock)?win:lose;
        break;
    case rock:
        result=(machine_choice==scissor)?win:lose;
        break;
    case scissor:
        result=(machine_choice==paper)?win:lose;
        break;
    }
    return result;
}
