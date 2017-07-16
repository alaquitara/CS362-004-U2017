#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//Smithy test

void assertTrue(int a, int b){
	if(a==b)
	{
		printf("TEST PASSED\n");
	}
	else{
		printf("TEST FAILED\n");
	}
}

int main() {
    struct gameState G, oG;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, great_hall, village, baron, smithy};
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0, seed =2, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	int plusCards = 3, plusActions;
	int player = whoseTurn(&G);

    //initialize game state
    initializeGame(numbPlayers, k, seed, &G);

    printf("\n *****TESTING SMITHY***** \n");
	
	printf("\n TESTING USAGE\n\n");
	//test invalid input
	int r = playSmithy(&G, -1, 4);
	if (r == 0){
		passFail = 1;
	}

	//test valid input
	r = playSmithy( &G, 1, 4);
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
        val = cardEffect(smithy, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (val != 0) {
            passFail = 0;
            break;
        }
    }
    printf("Return Value: %d, Expected: %d \n\n", val, 0);
	player = whoseTurn(&G);
    //testing correct number of cards added
    printf("\n TESTING CORRECT HAND COUNT\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        cardEffect(smithy, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (oG.handCount[player] != G.handCount[player]+plusCards-1){
            passFail = 0;
            break;
        }
    }

    printf("Hand Count: %d, Expected: %d \n\n", oG.handCount[player], G.handCount[player]+plusCards-1);
    //check value of passFail for overall pass or fail
	assertTrue(passFail, 1);
	printf("\n\n *****SMITHY TEST COMPLETE*****\n\n");

    return 0;
};