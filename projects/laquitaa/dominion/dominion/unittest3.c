#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//shuffle() test

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
    int choice1 = 1, choice2 = 2, choice3 = 3, bonus = 0, handPos = 0, seed =3, counter=0, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	initializeGame(numbPlayers, k, seed, &G);
	int player = whoseTurn(&G);
	
	printf("\n *****TESTING shuffle() ***** \n");
	
	//testing return value
    printf("\n TESTING RETURN VALUE:\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        val = shuffle(player, &oG);
        if (val != 0) {
            passFail = 0;
            break;
        }
    }
	printf("Return Value: %d, Expected: %d \n\n", val, 0);
	//testing suffle functionality
	printf("\n TESTING DECK IS SHUFFLED:\n\n");
	int oGvalues[G.deckCount[player]];
	int gValues[G.deckCount[player]];
	
	printf("VALUES BEFORE SHUFFLE:\n");
	for(i=0; i<G.deckCount[player]; i++){
		printf("%d\n",G.deck[player][i] );
		gValues[i] = G.deck[player][i];
	}
	
	printf("VALUES AFTER SHUFFLE:\n");
	shuffle(player, &G);
	for(i=0; i<G.deckCount[player]; i++){
		printf("%d\n",G.deck[player][i] );
		oGvalues[i] = G.deck[player][i];
	}
	if(gValues == oGvalues){
		passFail = 0;
	}
	assertTrue(passFail, 1);
	return 0;
}