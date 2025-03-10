### Soccer League Management System

### Overview
The Soccer League Management System is a C++ program that manages a football league consisting of teams and players. Each player has a market value, and each team has a budget allocated for acquiring players. Teams can buy and sell players while maintaining their budget constraints.

### Features
* **Player Management**
  * Add a new player with a specified market value.
  * Delete an existing player.
* **Team Management**
  * Add a new team with an initial budget.
  * Delete an existing team.
* **Player Transfers**
  * Teams can view player recommendations based on their budget.
  * Teams can buy players from other teams if they can afford them.
  * Teams can remove players from their roster.
* **Sorting and Displaying Information**
  * Print a list of all players sorted by their salary.
  * Print a list of all teams sorted by their budget.
  * Print a list of players for a specific team.

### Data Structures
The system utilizes a dynamic array of structures called `Team`, which includes:
* **Players** - An array of pointers to player names, representing the players in each team.
* **Budget** - The team's available funds.
* **Team Names** - The names of all the teams.

### Business Logic
* Each player can belong to only one team or remain unassigned.
* Teams have no player limit.
* Teams can acquire new players from other teams by transferring funds to the seller.
* Free-agent players can be purchased, but the funds will not be transferred to any team.

### Menu Options
```
Welcome to Soccer League Management System
Choose one of the following options:
1. Add a Player
2. Add a Team
3. Delete a Player
4. Delete a Team
5. Team: Player Recommendations
6. Team: Buy a player
7. Team: Remove a player
8. Print list of all Players sorted by their salary
9. Print a list of all Teams sorted by their budget
10. Print a list of players for a specific team
11. Exit
```

### Installation and Usage
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/soccer-league.git
   ```
2. Compile the program using a C++ compiler:
   ```bash
   g++ -o soccer_league main.cpp
   ```
3. Run the program:
   ```bash
   ./soccer_league
   ```

### License
This project is licensed under the MIT License.


