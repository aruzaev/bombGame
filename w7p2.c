#define MAX_PATH_LENGTH 70
#include <stdio.h>

struct PlayerInfo
{
	int lives;
	char icon;
	int treasures;
	int history[MAX_PATH_LENGTH + 1]; // needs to be predicated on pathLength
};

struct GameInfo
{
	int movesAllowed;
	int pathLength;
	int bombs[MAX_PATH_LENGTH + 1];
	int treasures[MAX_PATH_LENGTH + 1];
};

void printStats(struct PlayerInfo* pi, struct GameInfo* gi, int lastMove,
        int movesLeft);

int main()
{
	struct PlayerInfo plrInfo;
	struct GameInfo gmInfo;

	printf("================================\n");
	printf("        Treasure Hunt!\n");
	printf("================================\n\n");

	printf("PLAYER Configuration\n");
	printf("--------------------\n");
	printf("Enter a single character to represent the player: ");
	scanf(" %c", &plrInfo.icon);

	do 
	{
		printf("Set the number of lives: ");
		scanf("%d", &plrInfo.lives);
		if (plrInfo.lives < 1 || plrInfo.lives > 10)
		{
			printf("    Must be between 1 and 10!\n");
		}
	} while (plrInfo.lives < 1 || plrInfo.lives > 10);

    plrInfo.history[MAX_PATH_LENGTH] = 0;
	printf("Player configuration set-up is complete\n\n");

	printf("GAME Configuration\n");
	printf("--------------------\n");

	do
	{
		printf("Set the path length (a multiple of 5 between 10-70): ");
		scanf("%d", &gmInfo.pathLength);
		if ((gmInfo.pathLength % 5 != 0) || (gmInfo.pathLength < 10 
					|| gmInfo.pathLength > 70)) 
		{
			printf("    Must be a multiple of 5 and between 10-70!!!\n");
		}
	} while ((gmInfo.pathLength % 5 != 0) || (gmInfo.pathLength < 10 
				|| gmInfo.pathLength > 70));

	do
	{
		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &gmInfo.movesAllowed);
		if (gmInfo.movesAllowed < 3 || gmInfo.movesAllowed > 15)
		{
			printf("    Value must be between 3 and 15\n");
		}
	} while (gmInfo.movesAllowed < 3 || gmInfo.movesAllowed > 15);

    
    int a;
    int move;
    for (a = 0; a < gmInfo.pathLength; a++)
    {
        printf("Enter n to put into the nth element of the array: ");
        scanf("%d", &plrInfo.history[a]);
    }
    for (a = 0; a < gmInfo.pathLength; a++)
    {
        printf("%d", plrInfo.history[a]);
    }

	printf("\nBOMB Placement\n");
	printf("--------------\n");
	printf("Enter the bomb positions in sets of 5 where a value\n");
	printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
	printf("(Example: 1 0 0 1 1) NOTE: there are 35 to set!\n");

	int steps = gmInfo.pathLength / 5;
	int i;
	int min = 1;
	int max = 5;
	for (i = 1; i <= steps; i++)
	{
		printf("Positions [ %d-%1d]: ", min, max);
		scanf("%d %d %d %d %d", &gmInfo.bombs[min], &gmInfo.bombs[min + 1],
				&gmInfo.bombs[min + 2], &gmInfo.bombs[min + 3], 
				&gmInfo.bombs[min + 4]);
		
		min += 5;
		max += 5;
	}
	printf("BOMB placement set\n\n");

	printf("TREASURE Placement\n");
	printf("------------------\n");
	printf("Enter the treasure placemnts in sets of 5 where a value\n");
	printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
	printf("(Example: 1 0 0 1 1) NOTE: there are 35 to set!\n");

	min = 1;
	max = 5;

	for (i = 1; i <= steps; i++)
	{
		printf("Positions [ %d-%1d]:  ", min, max);
		scanf("%d %d %d %d %d", &gmInfo.treasures[min],
				&gmInfo.treasures[min + 1], &gmInfo.treasures[min + 2], 
				&gmInfo.treasures[min + 3], &gmInfo.treasures[min + 4]);

		min += 5;
		max += 5;
	}

	printf("TREASURE placement set\n\n");

	printf("GAME configuration set-up is complete...\n\n");
	printf("------------------------------------\n");
	printf("TREASURE HUNT Configuration Settings\n");
	printf("------------------------------------\n");
	printf("Player:\n");
	printf("    Symbol     : %c\n", plrInfo.icon);
	printf("    Lives      : %d\n", plrInfo.lives);
	printf("    Treasure   : [ready for gameplay]\n");
	printf("    History    : [ready for gameplay]\n\n");
	printf("Game:\n");
	printf("    Path Length: %d\n", gmInfo.pathLength);
	printf("    Bombs      :");
	
	for (i = 1; i <= gmInfo.pathLength; i++)
	{
		printf("%d", gmInfo.bombs[i]);
	}
	printf("\n    Treasure   :");
	
	for (i = 1; i <= gmInfo.pathLength; i++)
	{
		printf("%d", gmInfo.treasures[i]);
	}

	printf("\n\n====================================\n");
	printf("~ Get ready to play TREASURE HUNT! ~\n");
	printf("====================================\n\n");

    int movesCounter = 0;
    int movePosition = 0;
    // history[movePosition]

        printf("\n--------------------\n");
        printf("|||||||||1|||||||||2\n");
        printf("12345678901234567890\n");

        printf("+---------------------------------------------------+\n");
        printf(" Lives: %2d | Treasures: %2d | Moves Remaining: %2d\n", 
                plrInfo.lives, plrInfo.treasures, 
                gmInfo.movesAllowed - movesCounter);
        printf("+---------------------------------------------------+\n");

    do
    {
        // passing addy of structrues means that something needs to be changed
        printStats(&plrInfo, &gmInfo, movePosition, 
                gmInfo.movesAllowed - movesCounter);
        
        do
        {
            printf("Next Move [1-%d]: ", gmInfo.pathLength);
            scanf("%d", &movePosition);
            if (movePosition < 1 || movePosition > 20)
                printf("   Out of Range!!!\n");

        } while (movePosition < 1 || movePosition > 20);



        if (gmInfo.bombs[movePosition] == 0 && 
                gmInfo.treasures[movePosition] == 0)
        {
            printf("===============> [.] ...Nothing found here... [.]\n\n");
        }
        else if (gmInfo.bombs[movePosition] == 1 &&
                gmInfo.treasures[movePosition == 1])
        {
            plrInfo.treasures++;
            plrInfo.lives--;
            movesCounter++;
            printf("===============> [&] !!! BOOOOOM !!! [&]\n");
            printf("===============> [&] $$$ Life Insurance Payout!!! "
                    "[&]\n\n");
        }
        else if (gmInfo.bombs[movePosition] == 1 &&
                gmInfo.treasures[movePosition == 0])
        {
            plrInfo.lives--;
            movesCounter++;
            printf("===============> [&] !!! BOOOOOM !!! [&]\n\n"); 
        }
        else if (gmInfo.bombs[movePosition] == 0 &&
                gmInfo.treasures[movePosition] == 1)
        {
            plrInfo.treasures++;
            movesCounter++;
            printf("===============> [$] $$$ Found Treasure! $$$ [$]\n\n");
        }
    } while (plrInfo.lives > 0 && movesCounter < gmInfo.movesAllowed); 
	return 0;
}

void printStats(struct PlayerInfo* pi, struct GameInfo* gi, int lastMove,
        int movesLeft)
{
     lastMove = 0;

}

