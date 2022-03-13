/*
*****************************************************************************
                          Workshop - #7 (P2)
Full Name  : Artem Ruzaev
Student ID#: 124086216
Email      : aruzaev@myseneca.ca
Section    : NPP
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#define MAX_PATH_LENGTH 70  // setting path limit
#include <stdio.h> // standard input output library

struct PlayerInfo // struct for the player info
{
	int lives; // the amount of lives they have
	char icon; // the icon that they are represented by
	int treasures; // counter for how many treasures found
	int history[MAX_PATH_LENGTH + 1]; // past moves of the player
};

struct GameInfo // struct for game info
{
	int movesAllowed; // how many moves are allowed
	int pathLength; // what is the path length of the moves
	int bombs[MAX_PATH_LENGTH + 1]; // positions of bombs
	int treasures[MAX_PATH_LENGTH + 1]; // positions of treasures
};
// prototype, passing modifiable player and game info, as well as move tracker
void printStats(struct PlayerInfo* pi, struct GameInfo* gi, int lastMove,
        int movesLeft);

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

    plrInfo.history[MAX_PATH_LENGTH + 1] = 0; // clearing history of junk
	plrInfo.treasures = 0; // clearing amount of treasures found of junk
	printf("Player configuration set-up is complete\n\n");

	printf("GAME Configuration\n");
	printf("------------------\n");

	do
	{
		printf("Set the path length (a multiple of 5 between 10-70): ");
		scanf("%d", &gmInfo.pathLength); // scanning for path length
		// if the path length isnt divisible by 5 or within range
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
		if (gmInfo.movesAllowed < 3 || gmInfo.movesAllowed > 15)
		{
			printf("    Value must be between 3 and 15\n");
		}
	} while (gmInfo.movesAllowed < 3 || gmInfo.movesAllowed > 15);

	printf("\nBOMB Placement\n");
	printf("--------------\n");
	printf("Enter the bomb positions in sets of 5 where a value\n");
	printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
	printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gmInfo.pathLength);

	int steps = gmInfo.pathLength / 5; // spliting steps into 5
	int i;  
	int min = 1; // min for the loop
	int max = 5; // max for the loop
	for (i = 1; i <= steps; i++)
	{
		printf("   Positions [%2d-%2d]: ", min, max);
		scanf("%d %d %d %d %d", &gmInfo.bombs[min], &gmInfo.bombs[min + 1],
				&gmInfo.bombs[min + 2], &gmInfo.bombs[min + 3], 
				&gmInfo.bombs[min + 4]);
		
		min += 5; // incrementing min and max
		max += 5;
	}
	printf("BOMB placement set\n\n");

	printf("TREASURE Placement\n");
	printf("------------------\n");
	printf("Enter the treasure placements in sets of 5 where a value\n");
	printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
	printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gmInfo.pathLength);

	min = 1; // resetting min and max
	max = 5;

	for (i = 1; i <= steps; i++)
	{
		printf("   Positions [%2d-%2d]: ", min, max);
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
	printf("   Bombs      : ");
	
	for (i = 1; i <= gmInfo.pathLength; i++)
	{
		printf("%d", gmInfo.bombs[i]);
	}
	printf("\n   Treasure   : ");
	
	for (i = 1; i <= gmInfo.pathLength; i++)
	{
		printf("%d", gmInfo.treasures[i]);
	}

	printf("\n\n====================================\n");
	printf("~ Get ready to play TREASURE HUNT! ~\n");
	printf("====================================\n");
	for (i = 0; i < gmInfo.pathLength; i++)
	{ // replacing every element in history with -
		plrInfo.history[i + 1] = '-';
	}
    int movesCounter = 0; // counting the moves
    int movePosition = 0; // user selected position

    do
    {   // calling function to print out stats
        printStats(&plrInfo, &gmInfo, movePosition, 
                gmInfo.movesAllowed - movesCounter);   
        do
        {   // prompting for the move and verifying
            printf("Next Move [1-%d]: ", gmInfo.pathLength);
            scanf("%d", &movePosition);
            if (movePosition < 1 || movePosition > 20)
                printf("  Out of Range!!!\n");

        } while (movePosition < 1 || movePosition > 20);

		// if the history has any symbols, then the player has 
		// already been to that position
		if (plrInfo.history[movePosition] == '!' || 
		    plrInfo.history[movePosition] == '$' ||
			plrInfo.history[movePosition] == '.' ||
			plrInfo.history[movePosition] == '&') 
			{
				printf("\n===============> Dope! You've been here "
					   "before!\n\n");
					   // not adding moves
			}
			// if there is a bomb and a treasure in specified position
			else if (gmInfo.bombs[movePosition] == 1 &&
					 gmInfo.treasures[movePosition] == 1)
			{
				printf("\n===============> [&] !!! BOOOOOM !!! [&]\n");
            	printf("===============> [&] $$$ Life Insurance Payout!!! "
                    "[&]\n\n");
				plrInfo.treasures++; // increase amount of treasures
				plrInfo.lives--; // decrease lives
				movesCounter++; // increase moves made
			}
			// if there is a bomb and no treasure
			else if (gmInfo.bombs[movePosition] == 1 &&
			         gmInfo.treasures[movePosition] == 0)
			{
				printf("\n===============> [!] !!! BOOOOOM !!! [!]\n\n");
				plrInfo.lives--; // decrease lives
				movesCounter++; // increase moves made

			}
			// if there is no bomb and a treasure
			else if (gmInfo.bombs[movePosition] == 0 &&
			         gmInfo.treasures[movePosition] == 1)
			{
				printf("\n===============> [$] $$$ Found Treasure! $$$ [$]\n\n");
				plrInfo.treasures++; // increase treasure 
				movesCounter++; // increase moves made
			}
			else
			{
				// if there is nothing found
				printf("\n===============> [.] ...Nothing found here... [.]\n\n");
				movesCounter++; // increase moves found
			}
			// execute loop while there are lives left and the move counter
			// doesn't exceed the moves allowdd
    } while (plrInfo.lives > 0 && movesCounter < gmInfo.movesAllowed); 

	if (plrInfo.lives == 0) // if there are no move lives left
	{
		printf("No more LIVES remaining!\n\n");
		printStats(&plrInfo, &gmInfo, movePosition,  // print stats
                gmInfo.movesAllowed - movesCounter);
	}

	printf("\n##################\n");
	printf("#   Game over!   #\n");
	printf("##################\n");
	printf("\nYou should play again and try to beat your score!\n");
	return 0;
}
// initializing function
void printStats(struct PlayerInfo* pi, struct GameInfo* gi, int lastMove,
        int movesLeft)
{
	int i; 
	if (lastMove > 0) // if the move selected is greater than 0
	{
		printf(" ");
		// loop through the path length
		for (i = 1; i < gi->pathLength + 1; i++)
		{
			printf(" "); // print space if not equal

			if (i == lastMove) // if the counter is equal to selected move
			{
				printf("%c", pi->icon); // print user's icon
				i = gi->pathLength + 1;
			}
		}
		printf("\n");
	}
	else
	{
		printf("\n");
	}
	// setting the symbols to the outcomes
	if (gi->bombs[lastMove] == 1 && gi->treasures[lastMove] == 1)
	{
		pi->history[lastMove] = '&';
	}
	else if (gi->bombs[lastMove] == 1 && gi->treasures[lastMove] == 0)
	{
		pi->history[lastMove] = '!';
	}
	else if (gi->bombs[lastMove] == 0 && gi->treasures[lastMove] == 1)
	{
		pi->history[lastMove] = '$';
	}
	else
	{
		pi->history[lastMove] = '.';
	}
	
	printf("  ");
	for (i = 1; i < gi->pathLength + 1; i++)
	{
		printf("%c", pi->history[i]); // printing the history
	}
	printf("\n");

	printf("  ");
	// printing the 1st ruler
	for (i = 1; i <= gi->pathLength; i++)
	{
		if (i % 10 == 0) // if counter is divisible by 10
		{
			printf("%d", i / 10); // print the first number without the 0
		}
		else
		{
			printf("|"); // or else print a line
		}
	}
	printf("\n");

	printf("  ");
	// printing the 2nd ruler
	for (i = 1; i <= gi->pathLength; i++)
	{
		printf("%d", i % 10); // print the remainder
	}
	// stats
	printf("\n+---------------------------------------------------+\n");
	printf("  Lives:  %d  | Treasures:  %d  |  Moves Remaining: %2d\n", pi->lives, pi->treasures, movesLeft);
	printf("+---------------------------------------------------+\n");

}


