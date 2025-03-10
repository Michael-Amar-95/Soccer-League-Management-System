#ifndef Soccer_League_Management_System_DEC_H
#define Soccer_League_Management_System_DEC_H

#include <iostream>
#include <string>
#include <cstring>
#include "Soccer_League_Management_System_dec.h"
#pragma warning (disable:4996)
#define MAX_SIZE_NAME 25 
using namespace std;

typedef struct Player {
	char* playerName;
	int playerPrice;
	char* hisTeam;
} Player;

typedef struct Team {
	char* TeamName;
	char** TeamPlayers;
	int TeamAccount;
	int countPlayers;
} Team;

void addPlayers(Player*& p_Player, char player_name[], int salary, int& numOfPlayer);
void addTeams(Team*& p_Team, char team_name[], int budget, int& numOfTeam);
void deletePlayers(Team*& p_Team, Player*& p_Player, char name[], int& numOfTeam, int& numOfPlayer);
void deleteTeams(Team*& p_Team, Player* p_Player, char name[], int& numOfTeam, int& numOfPlayer);
void playerRecommendations(Team* p_Team, Player* p_Player, char team_name[], int numOfTeam, int numOfPlayer);
void buyPlayers(Team*& p_Team, Player*& p_Player, int& numOfTeam, int& numOfPlayer);
bool removePlayers(Team*& p_Team, Player*& p_Player, char team_name[], char player_name[], int& numOfTeam, int& numOfPlayer);
void printPlayerBySalary(Player* p_Player, int numOfPlayer);
void printTeamByBudget(Team* p_Team, int numOfTeam);
void playersInTeam(Team* p_team, char team_name[], int numOfTeam);

int findPlayer(Player* p_Player, char name[], int numOfPlayer);
int findTeam(Team* p_Team, char name[], int numOfTeam);
bool isTradePossible(Team* p_Team, Player* p_Player, int numOfTeam, int numOfPlayer, char team_name[], char player_name[], int indexTeam, int indexPlayer);
void trade(Team*& p_Team, Player*& p_Player, int numOfTeam, int numOfPlayer, char team_name[], char player_name[], int indexTeam, int indexPlayer);
#endif //Soccer_League_Management_System_DEC_H