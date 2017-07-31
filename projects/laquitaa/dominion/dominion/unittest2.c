#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//numHandCards() test

void assertTrue(int a, int b){
	if(a==b)
	{
		printf("TEST SUCCESSFULLY COMPLETED\n");
	}
	else{
		printf("TEST FAILED\n");
	}
}

int main() {
	struct gameState G, oG;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , smithy, great_hall, village, baron, steward};
    int choice1 = 1, choice2 = 2, choice3 = 3, bonus = 0, handPos = 0, seed =2, counter=0, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	initializeGame(numbPlayers, k, seed, &G);
	int player = whoseTurn(&G);
	int correctNumb = G.handCount[player];
	printf("hand count %d\n", correctNumb);
	
	printf("\n *****TESTING numHandCard ***** \n");
	
	
	//testing return value
    printf("\n TESTING RETURN VALUE:\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        val = numHandCards(&oG);
		player = whoseTurn(&oG);
        if (val != correctNumb) {
            passFail = 0;
            break;
        }
    }
	printf("Return Value: %d, Expected: %d \n\n", val, correctNumb);
	//testing after adding
	printf(" TESTING AFTER ADDING CARD:\n\n");
	correctNumb = G.handCount[player]+1;
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        drawCard(player, &oG);
		val = numHandCards(&oG);
		player = whoseTurn(&oG);
        if (val != correctNumb) {
            passFail = 0;
            break;
        }
    }
	printf("Return Value: %d, Expected: %d \n\n", val, correctNumb);
	
	//testing after removing
	printf(" TESTING AFTER REMOVING CARD:\n\n");
	correctNumb = G.handCount[player]-1;
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        discardCard(1,player, &oG,0);
		val = numHandCards(&oG);
		player = whoseTurn(&oG);
        if (val != correctNumb) {
            passFail = 0;
            break;
        }
    }
	printf("Return Value: %d, Expected: %d \n\n", val, correctNumb);
	assertTrue(passFail, 1);
	return 0;
}