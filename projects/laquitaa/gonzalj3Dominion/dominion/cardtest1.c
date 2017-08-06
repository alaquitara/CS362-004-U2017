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
//Adventurer test
int main (int argc, char** argv) {
	struct gameState G, oG;
    int k[10] = {great_hall, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, adventurer};
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0, seed =2, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	int plusCards = 1;
	int player = whoseTurn(&G);

    //initialize game state
    initializeGame(numbPlayers, k, seed, &G);

    printf("\n *****TESTING Adventurer***** \n");
	
	//testing return value for proper usage
    printf("\n TESTING RETURN VALUE:\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        val = cardEffect(adventurer, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (val != 0) {
            passFail = 0;
            break;
        }
    }
    printf("Return Value: %d, Expected: %d \n\n", val, 0);

    //testing correct number of cards  and actionsadded
    printf("\n TESTING CORRECT ACTION AND HAND COUNT\n\n");
    for (i = 0; i < x; i++) {
		player = whoseTurn(&G);
        memcpy(&oG, &G, sizeof(struct gameState));
        cardEffect(adventurer, choice1, choice2, choice3, &oG, handPos, &bonus);
        if (oG.handCount[player] < G.handCount[player]+plusCards-1){
            passFail = 0;
            break;
        }
		if(oG.numActions != G.numActions){
			passFail = 0;
			break;
		}
    }
	printf("Action Count: %d, Expected: %d \n\n", oG.numActions, G.numActions);
    printf("Hand Count: %d, Expected: > %d \n\n", oG.handCount[player], G.handCount[player]+plusCards-1);
	
	//testing treasure
	int treasure, tC;
	for(i = 0; i<x; i++){
		memcpy(&oG,&G, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &oG, handPos, &bonus);
		treasure = 0;
		int j = 0;
		
		while(j<numHandCards(&G)){
		//for (j = 0; j<numHandCards(&G; j++)
			if(handCard(j, &G) == copper){
				treasure ++;
			}
			else if(handCard(j, &G)== silver){
				treasure = treasure +2;
			}
			else if(handCard(j, &G) == gold){
				treasure = treasure+ 3;
			}
			j++;
		};
		
		tC = 0;
		int k = 0;
		for (k = 0; k<numHandCards(&oG); k++){
			if (handCard(j, &oG) == copper) {
                tC++;
            } else if (handCard(j, &oG) == silver) {
                tC += 2;
            } else if (handCard(j, &oG) == gold) {
                tC += 3;
            }
		}
		if(treasure+2 > tC){
			passFail = 0;
			break;
		}
	}
	printf("Treasure Count: %d, Expected Treasure Count: >= %d \n\n", tC, treasure+2);
	
    //check value of passFail for overall pass or fail
	assertTrue(passFail, 1);
	printf("\n\n *****Adventurer TEST COMPLETE*****\n\n");

    return 0;
};