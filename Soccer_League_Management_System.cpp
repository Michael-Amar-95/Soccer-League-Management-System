#include <iostream>
#include <string>
#include <cstring>
#include "Soccer_League_Management_System_dec.h"
#pragma warning (disable:4996)
#define MAX_SIZE_NAME 25 
using namespace std;

int main()
{
	int choose;
	int budget;
	int salary;
	int numOfTeam = 0;
	int numOfPlayer = 0;
	Team* p_Team = new Team[numOfTeam + 1];
	Player* p_Player = new Player[numOfPlayer + 1];
	do
	{
		cout << "Welcome to Soccer League Management System \n" << " Choose one of the following options:\n" <<
			"(1) Add a Player\n" << "(2) Add a Team\n" << "(3) Delete a Player\n" << "(4) Delete a Team\n" << "(5) Team: Player Recommendations\n" <<
			"(6) Team: Buy a player\n" << "(7) Team: Remove a player\n" << "(8) Print list of all Players sorted by their salary\n" <<
			"(9) Print a list of all Teams sorted by their budget\n" << "(10) Print a list of players for a specific team\n" <<
			"(11) Exit\n\n";

		cin >> choose;
		char team_name[MAX_SIZE_NAME];
		char player_name[MAX_SIZE_NAME];
		switch (choose)
		{
		case 1:
			cout << "Enter name of Player:\n";
			cin >> player_name;
			cout << "Enter player salary:\n";
			cin >> salary;
			while (salary <= -1)
			{
				cout << "Try again: ";
				cin >> salary;
			}
			addPlayers(p_Player, player_name, salary, numOfPlayer);
			break;
		case 2: cout << "Enter name of Team:\n";
			cin >> team_name;
			cout << "Enter starting budget:\n";
			cin >> budget;
			while (budget <= -1)
			{
				cout << "Try again: ";
				cin >> budget;
			}
		    addTeams(p_Team, team_name, budget, numOfTeam);
			break;
		case 3:	cout << "Enter name of Player:\n";
			cin >> player_name;
			if (findPlayer(p_Player, player_name, numOfPlayer) == -1)
			{
				cout << player_name << " does not exist in the database.\n";
			}
			else
			{
				deletePlayers(p_Team, p_Player, player_name, numOfTeam, numOfPlayer);
				cout << player_name << " has been deleted from the database.\n";
			}
			break;
		case 4: cout << "Enter name of Team:\n";
			cin >> team_name;
			if (findTeam(p_Team, team_name, numOfTeam) == -1)
			{
				cout << team_name << " does not exist in the database.\n";
			}
			else
			{
				deleteTeams(p_Team, p_Player, team_name, numOfTeam, numOfPlayer);
				cout << team_name << " team has been deleted from the database.\n";
			}
			break;
		case 5:cout << "Enter name of Team:\n";
			cin >> team_name;
			playerRecommendations(p_Team, p_Player, team_name, numOfTeam, numOfPlayer);
			break;
		case 6: buyPlayers(p_Team, p_Player, numOfTeam, numOfPlayer);
			break;
		case 7:	cout << "Enter name of Team:\n";
			cin >> team_name;
			if (findTeam(p_Team, team_name, numOfTeam) == -1)
			{
				cout << team_name << " does not exist in the database.\n";
			}
			else
			{
				char player_name[MAX_SIZE_NAME];
				cout << "Enter name of Player:\n";
				cin >> player_name;
				if (findPlayer(p_Player, player_name, numOfPlayer) >= 0)
				{
					removePlayers(p_Team, p_Player, team_name, player_name, numOfTeam, numOfPlayer);
				}
				else
				{
					cout << player_name << " does not exist in the database.\n";
				}
			}
			break;
		case 8: if (numOfPlayer == 0)
		{
			cout << "There are no players in database.\n";
		}
				else
		{
			printPlayerBySalary(p_Player, numOfPlayer);
			break;
		}
		case 9: if (numOfTeam == 0)
		{
			cout << "There are no players in database.\n";
		}
				else
		{
			printTeamByBudget(p_Team, numOfTeam);
			break;
		}
		case 10: cout << "Enter name of Team:\n";
			cin >> team_name;
			if (findTeam(p_Team, team_name, numOfTeam) == -1)
			{
				cout << "Team " << team_name << " does not exist in database.\n";
			}
			else
			{
				playersInTeam(p_Team, team_name, numOfTeam);
			}
			break;
		case 11: cout << "Goodbye!\n";
			break;
		default: cout << "Error: Try Again!\n";
			break;
		}
		cout << endl;
	} while (choose != 11);
	
	//Here i delete all the dynamic memory
	for (int i = 0; i < numOfTeam; i++)
	{
		delete[] p_Team[i].TeamName;
		for (int j = 0; j < p_Team[i].countPlayers; j++)
		{
			delete[] p_Team[i].TeamPlayers[j];
		}
		delete[] p_Team[i].TeamPlayers;
	}
	delete[] p_Team;
	for (int i = 0; i < numOfPlayer; i++)
	{
		delete[] p_Player[i].hisTeam;
		delete[] p_Player[i].playerName;
	}
	delete[] p_Player;
}

