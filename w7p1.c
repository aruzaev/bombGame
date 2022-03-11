#define MAX_PATH_LENGTH 70 // setting path limit
#include <stdio.h> // standard input output library

struct PlayerInfo // struct of the infro of a player
{
	int lives; // the amount of lives they have
	char icon; // the icon that they are represented by
	int treasures; // counter for how many treasures found
	int history[MAX_PATH_LENGTH]; // the past moves of the player
};

struct GameInfo // struct for the game options
{
	int movesAllowed; // how many moves are allowed
	int pathLength; // what is the path length of the moves
	int bombs[MAX_PATH_LENGTH + 1]; // the positions of the bombs
	int treasures[MAX_PATH_LENGTH + 1]; // the positions of the treasures
};

int main()
{
	struct PlayerInfo plrInfo; // creating plrInfo of type PlayerInfo
	struct GameInfo gmInfo;

	printf("================================\n");
	printf("         Treasure Hunt!\n");
	printf("================================\n\n");

	printf("PLAYER Configuration\n");
	printf("--------------------\n");
	printf("Enter a single character to represent the player: ");
	scanf(" %c", &plrInfo.icon); // scanning for the icon

	do 
	{
		printf("Set the number of lives: ");
		scanf("%d", &plrInfo.lives); // scanning for the amount of lives
		// verifying correct input
		if (plrInfo.lives < 1 || plrInfo.lives > 10)
		{
			printf("     Must be between 1 and 10!\n");
		}
	} while (plrInfo.lives < 1 || plrInfo.lives > 10);

	printf("Player configuration set-up is complete\n\n");

	printf("GAME Configuration\n");
	printf("--------------------\n");

	do
	{
		printf("Set the path length (a multiple of 5 between 10-70): ");
		scanf("%d", &gmInfo.pathLength); // scanning for path length
		// if the path length isnt divsible by 5 or within the range
		if ((gmInfo.pathLength % 5 != 0) || (gmInfo.pathLength < 10 
					|| gmInfo.pathLength > 70)) 
		{
			printf("     Must be a multiple of 5 and between 10-70!!!\n");
		}
	} while ((gmInfo.pathLength % 5 != 0) || (gmInfo.pathLength < 10 
				|| gmInfo.pathLength > 70));

	do
	{
		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &gmInfo.movesAllowed); // scanning for moves allowed
		if (gmInfo.movesAllowed < 3 || gmInfo.movesAllowed > 26)
		{
			printf("    Value must be between 3 and 26\n");
		}
	} while (gmInfo.movesAllowed < 3 || gmInfo.movesAllowed > 26);

	printf("\nBOMB Placement\n");
	printf("--------------\n");
	printf("Enter the bomb positions in sets of 5 where a value\n");
	printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
	printf("(Example: 1 0 0 1 1) NOTE: there are 35 to set!\n");

	int steps = gmInfo.pathLength / 5; // dividing the path by 5 to split
	int i; // counter variable
	int min = 1; // min for the first loop
	int max = 5; // max for the first loop
	for (i = 1; i <= steps; i++) // loop until i is equal to the steps #
	{
		printf("   Positions [ %d- %d]: ", min, max);
		// scanning for 5 bomb positions with a space between
		scanf("%d %d %d %d %d", &gmInfo.bombs[min], &gmInfo.bombs[min + 1],
				&gmInfo.bombs[min + 2], &gmInfo.bombs[min + 3], 
				&gmInfo.bombs[min + 4]);
		
		min += 5; // incrementing min by 5
		max += 5; // incrementing max by 5
	}
	printf("BOMB placement set\n\n");

	printf("TREASURE Placement\n");
	printf("------------------\n");
	printf("Enter the treasure placements in sets of 5 where a value\n");
	printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
	printf("(Example: 1 0 0 1 1) NOTE: there are 35 to set!\n");

	min = 1; // resetting the min/max values
	max = 5;

	for (i = 1; i <= steps; i++)
	{
		printf("   Positions [ %d- %d]: ", min, max);
		scanf("%d %d %d %d %d", &gmInfo.treasures[min],
				&gmInfo.treasures[min + 1], &gmInfo.treasures[min + 2], 
				&gmInfo.treasures[min + 3], &gmInfo.treasures[min + 4]);

		min += 5;
		max += 5;
	}

	printf("TREASURE placement set\n\n"); 
	// printing out the summary
	printf("GAME configuration set-up is complete...\n\n");
	printf("------------------------------------\n");
	printf("TREASURE HUNT Configuration Settings\n");
	printf("------------------------------------\n");
	printf("Player:\n");
	printf("   Symbol     : %c\n", plrInfo.icon);
	printf("   Lives      : %d\n", plrInfo.lives);
	printf("   Treasure   : [ready for gameplay]\n");
	printf("   History    : [ready for gameplay]\n\n");
	printf("Game:\n");
	printf("   Path Length: %d\n", gmInfo.pathLength);
	printf("   Bombs      :");
	
	for (i = 1; i <= gmInfo.pathLength; i++) // loop through the path
	{
		printf(" %d", gmInfo.bombs[i]); // print the bomb positions
	}
	printf("\n   Treasure   :");
	
	for (i = 1; i <= gmInfo.pathLength; i++) 
	{
		printf(" %d", gmInfo.treasures[i]); 
	}

	printf("\n\n====================================\n");
	printf("~ Get ready to play TREASURE HUNT! ~\n");
	printf("====================================\n\n");
	return 0;
}

