#include <iostream>
#include <string>
#include <cstring>
#include "Soccer_League_Management_System_dec.h"
#pragma warning (disable:4996)
#define MAX_SIZE_NAME 25 
using namespace std;

//This function add players to the league
void addPlayers(Player*& p_Player, char player_name[], int salary, int& numOfPlayer)
{
	Player* temp = new Player[numOfPlayer + 1]; //temp array of structs player. in this array i add a new player  
	int i = 0;
	for (; i < numOfPlayer; i++)
	{
    temp[i] = p_Player[i]; // temp point to the same place that player point
	}
	temp[i].playerName = new char[strlen(player_name) + 1];
	strcpy(temp[i].playerName, player_name); //Initializing player his name
	temp[i].playerPrice = salary; //Initializing player price
	temp[i].hisTeam = NULL; //Initializing player his team
	delete[] p_Player;
	p_Player = temp; // p_Player point to the same place temp point
	++numOfPlayer;
}

//This function add players to the league
void addTeams(Team*& p_Team, char team_name[], int budget, int& numOfTeam)
{
	Team* temp = new Team[numOfTeam + 1]; //temp array of structs team. in this array i add a new team
	int i = 0;
	for (; i < numOfTeam; i++)
	{
		temp[i] = p_Team[i]; // temp point to the same place that team point
	}
	temp[i].countPlayers = 0; //Initializing the number of player in team
	temp[i].TeamPlayers = NULL; //Initializing the name of player in team
	temp[i].TeamName = new char[strlen(team_name) + 1];
	strcpy(temp[i].TeamName, team_name); //Initializing team name
	temp[i].TeamAccount = budget; //Initializing team account
	delete[] p_Team;
	p_Team = temp; //p_Team point to the same place temp point
	++numOfTeam;
}

//This function delete player from array of structs of player
void deletePlayers(Team*& p_Team, Player*& p_Player, char name[], int& numOfTeam, int& numOfPlayer)
{
	int i = 0;
	int j = 0;
	for (; j < numOfPlayer; ++j) 
	{
		if (!(strcmp(p_Player[j].playerName, name))) //check if the name of player in array is desirable 
		{
			if (p_Player[j].hisTeam != NULL) //check if this player is belongs to any team
			{
				int index = findTeam(p_Team, p_Player[j].hisTeam, numOfTeam); //if player have a team i check the index of his team
				removePlayers(p_Team, p_Player, p_Team[index].TeamName, name, numOfTeam, numOfPlayer); //remove player from team
			}
			delete[] p_Player[j].playerName;
		}
		else
		{
			p_Player[i] = p_Player[j]; // if name is not desirable 
			++i;
		}
	}
	numOfPlayer--;
}

//This function delete team from array of struct of team
void deleteTeams(Team*& p_Team, Player* p_Player, char name[], int& numOfTeam, int& numOfPlayer)
{
	int i = 0;
	int j = 0;
	for (; j < numOfTeam; ++j)
		{
			if (!strcmp(p_Team[j].TeamName, name)) //check if name is desirable
			{
				for (int n = 0; n < numOfPlayer; n++)
				{
					if (p_Player[n].hisTeam != NULL) //check if player is in the team that we want to delete
					{
						if (!(strcmp(name, p_Player[n].hisTeam)))
						{
							delete[] p_Player[n].hisTeam;
							p_Player[n].hisTeam = NULL; //initialize his team
						}
					}
				}
				delete[] p_Team[i].TeamName;
				for (int m = 0; m < p_Team[i].countPlayers; m++)
				{
					delete[] p_Team[i].TeamPlayers[m]; //delete players from team
				}
			}
			else
			{
				p_Team[i] = p_Team[j]; // if name is not desirable 
				++i;
			}
		}
		numOfTeam--;
}

//This function check witch players a specific team can buy
void playerRecommendations(Team* p_Team, Player* p_Player, char team_name[], int numOfTeam, int numOfPlayer)
{
	int account = 0; // Amount of available player
	int index;
	if (findTeam(p_Team, team_name, numOfTeam) >= 0)
	{
		index = findTeam(p_Team, team_name, numOfTeam); //find team in array if team exist
		for (int j = 0; j < numOfPlayer; j++)
		{
			if (p_Team[index].TeamAccount >= p_Player[j].playerPrice) //check if there is at least one player to buy
			{
				++account;
				break;
			}
		}
		if (account > 0) //if there is at least one player to buy
		{
			cout << "The players " << team_name << " can acquire:\n";
			for (int j = 0; j < numOfPlayer; j++)
			{
				if (p_Team[index].TeamAccount >= p_Player[j].playerPrice)
				{
					cout << p_Player[j].playerName << endl;
					++account;
				}
			}
		}
		else
		{
			cout << "Team " << team_name << " is unable to afford any players in the database.\n";
		}
	}
	else
	{
		cout << "Team " << team_name << " does not exist in the database.\n";
	}
}

//This function do the command of buying
void buyPlayers(Team*& p_Team, Player*& p_Player, int& numOfTeam, int& numOfPlayer)
{
	char team_name[MAX_SIZE_NAME];
	char* player_name = new char[MAX_SIZE_NAME];
	cout << "Enter name of Team:\n";
	cin >> team_name;
	int indexTeam = findTeam(p_Team, team_name, numOfTeam);
	if (indexTeam >= 0)
	{
		cout << "Enter name of Player:\n";
		cin >> player_name;
		int indexPlayer = findPlayer(p_Player, player_name, numOfPlayer);
		if ( indexPlayer >= 0)
		{
			if (isTradePossible(p_Team, p_Player, numOfTeam, numOfPlayer, team_name, player_name, indexTeam, indexPlayer)) //check if trade is possible
			{
				trade(p_Team, p_Player, numOfTeam, numOfPlayer, team_name, player_name, indexTeam, indexPlayer);
			}
			else
			{
				cout << "Team " << team_name << " can't buy " << player_name << ". Not enough budget.\n";
			}
		}
		else
		{
			cout << player_name << "does not exist in the database.\n";
		}
	}
	else
	{
		cout << " Team " << team_name << " does not exist in the database.\n";
	}
}

//This function remove player from team
bool removePlayers(Team*& p_Team, Player*& p_Player, char team_name[], char player_name[], int& numOfTeam, int& numOfPlayer)
{
	int i = 0;
	for (; i < numOfTeam; i++)
	{
		if (!strcmp(p_Team[i].TeamName, team_name)) //check if name is desirable
		{
			int j = 0;
			for (; j < p_Team[i].countPlayers; j++)
			{
				if (!(strcmp(p_Team[i].TeamPlayers[j], player_name))) //search the player in the field of players
				{
					p_Team[i].TeamAccount = p_Team[i].TeamAccount + p_Player[findPlayer(p_Player, player_name, numOfPlayer)].playerPrice; //update team acoount
					delete[]p_Team[i].TeamPlayers[j];
					cout << player_name << " has been removed from the " << team_name << " team.\n";
					for (int n = j + 1; n < p_Team[i].countPlayers; n++) //narrow the array
					{
						p_Team[i].TeamPlayers[j] = p_Team[i].TeamPlayers[n];
					}
					p_Team[i].countPlayers = p_Team[i].countPlayers - 1;
					return true;
				}
			}
			cout << "No player named " << player_name << " on " << team_name << " team.\n";
		}
	}
	return true;
}

//This function print players in ascending order by there price
void printPlayerBySalary(Player* p_Player, int numOfPlayer)
{
	Player* temp = new Player [numOfPlayer];
	Player player;
	cout << "Player Budget\n";
	for (int i = 0; i < numOfPlayer; i++)
	{
		temp[i] = p_Player[i]; //temp point to the same place that player point
	}

	for (int i = 0; i < numOfPlayer; i++)
	{
		for (int j = i; j < numOfPlayer; j++)
		{
			if (temp[i].playerPrice > temp[j].playerPrice)
			{
				player = temp[j];
				temp[j] = temp[i];
				temp[i] = player;
			}
		}
	}

	for (int i = 0; i < numOfPlayer; i++)
	{
		cout << temp[i].playerName << " " << temp[i].playerPrice << endl;
	}
	delete[] temp;
}

//This function print teams in ascending order by there acoount
void printTeamByBudget(Team* p_Team, int numOfTeam)
{
	Team* temp = new Team[numOfTeam];
	Team team;
	cout << "Team Budget\n";
    for (int i = 0; i < numOfTeam; i++)
	{
		temp[i] = p_Team[i]; //temp point to the same place that team point
	}
    for (int i = 0; i < numOfTeam; i++)
	{
		for (int j = i; j < numOfTeam; j++)
		{
			if (temp[i].TeamAccount > temp[j].TeamAccount)
			{
				team = temp[j];
				temp[j] = temp[i];
				temp[i] = team;
			}
		}
	}

	for (int i = 0; i < numOfTeam; i++)
	{
		cout << temp[i].TeamName << " " << temp[i].TeamAccount << endl;
	}
	delete[] temp;
}

//This function print all players in team
void playersInTeam(Team* p_team, char team_name[], int numOfTeam)
{
	if (findTeam(p_team, team_name, numOfTeam) == -1) //check if team exist
	{
		cout << "Team " << team_name << " do not exist.\n";
	}
	else // if exist check
	{
		int index = findTeam(p_team, team_name, numOfTeam);
		if (p_team[index].countPlayers == 0) //check if there are any players in team
		{
			cout << "There are no players in " << team_name << " Team.\n";
		}
		else
		{
			cout << "The players on the " << team_name << " Team:\n";
			int j = 0;
			for (; j < p_team[index].countPlayers; j++) //print players
			{
				cout << p_team[index].TeamPlayers[j] << endl;
			}
		}
	}
}

//This function search the player and return his index if he exists 
int findPlayer(Player* p_Player, char name[], int numOfPlayer)
{
	for (int i = 0; i < numOfPlayer; i++)
	{
		if (!strcmp(p_Player[i].playerName, name))
		{
			return i;
		}
	}
	return -1;
}

//This function search the team and return his index if he exists
int findTeam(Team* p_Team, char name[], int numOfTeam)
{
	for (int i = 0; i < numOfTeam; i++)
	{
		if (!strcmp(p_Team[i].TeamName, name))
		{
			return i;
		}
	}
	return -1;
}

//This function check if trade is possible and return true if it could be
bool isTradePossible(Team* p_Team, Player* p_Player, int numOfTeam, int numOfPlayer, char team_name[], char player_name[], int indexTeam, int indexPlayer)
{
	if (p_Team[indexTeam].TeamAccount >= p_Player[indexPlayer].playerPrice)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This function do the trade bettwen the team
void trade(Team*& p_Team, Player*& p_Player, int numOfTeam, int numOfPlayer, char team_name[], char player_name[], int indexTeam, int indexPlayer)
{
	char** temp = new char* [p_Team[indexTeam].countPlayers + 1];  
	int placeOfHisTeam;
	if (p_Player[indexPlayer].hisTeam != NULL) //check if player have a team
	{
		placeOfHisTeam = findTeam(p_Team, p_Player[indexPlayer].hisTeam, numOfTeam); //if player have a team i search him in the array
		for (int i = 0; i < p_Team[placeOfHisTeam].countPlayers; ++i)
		{
			if (!strcmp(p_Team[placeOfHisTeam].TeamPlayers[i], player_name)) //check if this is the place of the player that we want to remove
			{
				removePlayers(p_Team, p_Player, p_Team[placeOfHisTeam].TeamName, player_name, numOfTeam, numOfPlayer);
				break;
			}
		}
	}
	p_Player[indexPlayer].hisTeam = new char[strlen(p_Team[indexTeam].TeamName) + 1]; //initialize hus team
	strcpy(p_Player[indexPlayer].hisTeam, p_Team[indexTeam].TeamName); 
	int i = 0;
	for (; i < p_Team[indexTeam].countPlayers; i++)
	{
		temp[i] = p_Team[indexTeam].TeamPlayers[i]; // temp point to the same place that teamplayers point
	}
	delete [] p_Team[indexTeam].TeamPlayers;
	temp[i] = player_name; // add player to the field
	p_Team[indexTeam].TeamPlayers = temp;
	cout << player_name << " has been added to the " << p_Team[indexTeam].TeamName << " team.\n";
	p_Team[indexTeam].TeamAccount = p_Team[indexTeam].TeamAccount - p_Player[indexPlayer].playerPrice;
	cout << p_Team[indexTeam].TeamName << " remaining budget: " << p_Team[indexTeam].TeamAccount << endl;
	p_Team[indexTeam].countPlayers = p_Team[indexTeam].countPlayers + 1;
}
