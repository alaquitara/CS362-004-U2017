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
               , remodel, great_hall, village, baron, smithy};
    int  bonus = 0,  i, handCount, handPos=0, deckCount, pass=0, fail =0, plusCards = 1, sw = 0 ;
	
	 printf("\n *****RANDOM TESTING ADVENTURER***** \n");
	
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
        int r = cardEffect(adventurer, choice1, choice2, choice3, &oG, handPos, &bonus);
        
		//testing for correct hand count
		if (oG.handCount[player] < G.handCount[player]+plusCards-1){
            fail++;
			sw=1;
        }
		//testing for correct number of actions
		if(oG.numActions != G.numActions){
			fail++;
		}
		
		//testing correct treasure added
		int treasure = 0;
		int j = 0;
		
		while(j<numHandCards(&G)){
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
		
		int tC = 0;
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
			fail++;
			sw =2;
		}
		//test return value
		if(r == 0){
			pass++;
		}else{
			fail++;
			sw = 3;
		}
		switch(sw){
			case 1:
				printf("Test for number of cards added failed\n");
				break;
			case 2:
				printf("Test for treasure failed\n");
				break;
			case 3:
				printf("Test for return value failed\n");
				break;
			default:
				printf("All tests passed\n");
				break;
		}
		sw = 0;
	}
	
	
	if(fail == 0){
		printf("Test Passed\n");

	}else{
		printf("Test Failed\n");
	
	}
	printf("\n\n *****ADVENTURER TEST COMPLETE*****\n\n");
	return 0;
	
	
}