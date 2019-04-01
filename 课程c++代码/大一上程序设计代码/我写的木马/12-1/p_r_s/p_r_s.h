#ifndef P_R_S
#define P_R_S
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum p_r_s {paper,rock,scissor,game,help,quit};
enum outcome {win,lose,tie,error};
outcome compare (p_r_s player_choice,p_r_s machine_choice);
//void prn_final_status();
void prn_game_status();
void prn_help();
void report(outcome result);
p_r_s selection_by_machine();
p_r_s selection_by_player();
#endif
