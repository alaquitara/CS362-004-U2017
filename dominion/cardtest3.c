#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertTrue(int a, int b){
	if(a==b)
	{
		printf("TEST PASSED\n");
	}
	else{
		printf("TEST FAILED\n");
	}
}
//greathall test
int main (int argc, char** argv) {
	struct gameState G, oG;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0, seed =2, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	int plusCards = 1, plusActions=1;
	int player = whoseTurn(&G);

    //initialize game state
    initializeGame(numbPlayers, k, seed, &G);

    printf("\n *****TESTING Great Hall***** \n");
	
	printf("\n TESTING USAGE\n\n");
	//test invalid input
	int r = playGreat_hall(&G, -1, 4);
	if (r == 0){
		passFail = 1;
	}

	//test valid input
	r = playGreat_hall( &G, 1, 4);
	if(r==0){
		passFail = 1;
		if(passFail == 1){
			printf("USAGE TEST PASSED\n\n");
		}
	}
	
	//testing return value
    printf("\n TESTING RETURN VALUE:\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        val = cardEffect(great_hall, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (val != 0) {
            passFail = 0;
            break;
        }
    }
    printf("Return Value: %d, Expected: %d \n\n", val, 0);

    //testing correct number of cards  and actionsadded
    printf("\n TESTING CORRECT ACTION AND HAND COUNT\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        cardEffect(great_hall, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (oG.handCount[player] != G.handCount[player]+plusCards-1){
            passFail = 0;
            break;
        }
		if(oG.numActions != G.numActions){
			passFail = 0;
			break;
		}
    }
	printf("Action Count: %d, Expected: %d \n\n", oG.numActions, G.numActions+1);
    printf("Hand Count: %d, Expected: %d \n\n", oG.handCount[player], G.handCount[player]+plusCards-1);
    //check value of passFail for overall pass or fail
	assertTrue(passFail, 1);
	printf("\n\n *****Great Hall TEST COMPLETE*****\n\n");

    return 0;
};