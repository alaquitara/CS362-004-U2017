#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//Steward test

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
    int choice1 = 1, choice2 = 2, choice3 = 3, bonus = 0, handPos = 0, seed =2, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	int plusCards = 2, plusActions;
	int player = whoseTurn(&G);

    //initialize game state
    initializeGame(numbPlayers, k, seed, &G);

    printf("\n *****TESTING Steward***** \n");
	memcpy(&oG, &G, sizeof(struct gameState));
	//testing return value
    printf("\n TESTING RETURN VALUE:\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        val = cardEffect(steward, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (val != 0) {
            passFail = 0;
            break;
        }
    }
    printf("Return Value: %d, Expected: %d \n\n", val, 0);
	choice1 = 1;
    //testing correct number of cards added
    printf("\n TESTING CORRECT HAND COUNT AFTER DRAW 2 CARDS\n\n");
    int newCount;
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        cardEffect(steward, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (oG.handCount[player] != G.handCount[player]+1){
            passFail = 0;
            break;
        }
    }
	
	printf("Hand Count: %d, Expected: %d \n\n", oG.handCount[player]-1, G.handCount[player]);
	printf("\n TESTING CORRECT MONEY COUNT \n\n");
	player = whoseTurn(&G);
	
	oG.coins = G.coins; 
	
	choice1 = 2;
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
		//printf("Money Count: %d, Expected <: %d \n\n", oG.coins, G.coins);
        cardEffect(steward, choice1, choice2, choice3, &oG, handPos, &bonus);
		//printf("Money Count: %d, Expected <: %d \n\n", oG.coins, G.coins);
		
        if (oG.coins > G.coins +2){
            passFail = 0;
            break;
        }
    }
	
	printf("Money Count: %d, Expected: %d \n\n", oG.coins, G.coins+2);
	
	printf("\n TESTING DISCARD \n\n");
	choice1 = 3;
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        cardEffect(steward, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (oG.handCount[player] != G.handCount[player]-3){
            passFail = 0;
            break;
        }
    }
	printf("Hand Count: %d, Expected: %d \n\n", oG.handCount[player], G.handCount[player]-3);
    //check value of passFail for overall pass or fail
	assertTrue(passFail, 1);
	printf("\n\n *****STEWARD TEST COMPLETE*****\n\n");

    return 0;
};