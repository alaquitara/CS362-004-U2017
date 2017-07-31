#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"


int main(){
	struct gameState G, oG;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, steward, village, baron, smithy};
    int  bonus = 0,  i, handCount, handPos=0, deckCount, pass=0, fail =0, sw ;
	
	 printf("\n *****RANDOM TESTING STEWARD***** \n");
	
	for(i = 0; i < 10000; i++){
		
		int choice1 = rand() % 3 +1;
		int choice2 = rand() % 3 + 1;
		int choice3 = rand() % 3 +1;
		int numbPlayers = rand() % 4 +1;
		unsigned int seed = rand();
		int player = rand() % numbPlayers + 1;
		initializeGame(numbPlayers, k, seed, &G);
			
		int rando = rand() %4;
		if(rando == 3){ // 1 in 5 chance that the deck is empty
			G.deckCount[player] = 0;
			deckCount = 0;
		}else{
			deckCount = rand() % MAX_DECK;
			G.deckCount[player] = deckCount;
		}
			
		handCount = rand() % MAX_HAND;
		G.handCount[player] = handCount;
		G.discardCount[player] = rand() % MAX_DECK;
		memcpy(&oG, &G, sizeof(struct gameState));
        int r = cardEffect(steward, choice1, choice2, choice3, &oG, handPos, &bonus);
        
		//testing for correct number of cards added
		if ((choice1 == 1) && (oG.handCount[player] != G.handCount[player]+1)){
            fail++;
			sw= 1;
        }
		//testing for correct number of actions
		if((choice1 == 2) && (oG.numActions != G.numActions)){
			fail++;
			sw = 2;
		}
		
		//testing discard
		if((choice1 > 2) && (oG.handCount[player] != G.handCount[player]-2)){
			fail++;
			sw=3;
		}
		//testing return value
		if(r == 0){
			pass++;
		}else{
			fail++;
			sw=4;
		}
	
		switch(sw){
			case 1:
				printf("Test for number of cards added failed\n");
				break;
			case 2:
				printf("Test for number of actions failed\n");
				break;
			case 3:
				printf("Test for number of cards discarded failed\n");
				break;
			case 4:
				printf("Test for correct return value failed\n");
				break;
			default:
				printf("All tests passed\n");
				break;
		}
		sw = 0;
	}
	if(fail == 0){
		printf("Test Passed\n");
		printf("\n\n *****STEWARD TEST COMPLETE*****\n\n");
	}else{
		printf("Test Failed\n");
		printf("\n\n *****STEWARD TEST COMPLETE*****\n\n");
	}
	return 0;
	
}