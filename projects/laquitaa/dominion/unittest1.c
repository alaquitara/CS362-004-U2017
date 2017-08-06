#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//handCard() test

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
               , smithy, great_hall, village, baron, steward};
    int choice1 = 1, choice2 = 2, choice3 = 3, bonus = 0, handPos = 0, seed =2, counter=0, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	initializeGame(numbPlayers, k, seed, &G);
	int player = whoseTurn(&G);
	
	printf("\n *****TESTING handCard ***** \n");
	
	//testing return value
    printf("\n TESTING RETURN VALUE:\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        val = handCard(counter, &oG);
		player = whoseTurn(&oG);
        if (val != G.hand[player][counter]) {
            passFail = 0;
            break;
        }
		counter++;
		if(counter > oG.handCount[0]){
			counter=0;
		}
    }
	printf("Return Value: %d, Expected: %d \n\n", val, 1);
	
	counter = 0;
	printf("TESTING CARD VALUES\n\n");
	for (i = 0; i < x; i++) {
		
        memcpy(&oG, &G, sizeof(struct gameState));
        //oG.whoseTurn = 0;
		player = whoseTurn(&oG);
        handCard(counter, &oG);
        counter++;
        if (counter > oG.handCount[0]) {
            counter = 0;
        }
    }
    x = G.handCount[0];
	int gValues[x], oGvalues[x];
    for (i = 0; i < x; i++ ) {
		oGvalues[i] = oG.hand[player][i];
		gValues[i] = G.hand[player][i];
	}
	printf("Original values     Copy Vaues\n");
	for(i = 0; i < x; i++ ){
		printf("     %d               %d\n",gValues[i], oGvalues[i]);
		if(gValues[i] != oGvalues[i]){
			passFail = 0;
		}
	}
	
	assertTrue(passFail, 1);
	return 0;
}