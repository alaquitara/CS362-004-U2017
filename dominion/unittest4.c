#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//isGameOver() test

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
    int seed =3, numbPlayers = 2, x = 1000, i, val, passFail = 1;
	initializeGame(numbPlayers, k, seed, &G);
	
	
	printf("\n *****TESTING isGameOver ***** \n");
	
	//testing return value
    printf("\n TESTING RETURN VALUE FOR GAME NOT OVER:\n\n");
    for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        val = isGameOver(&oG);
        if (val != 0) {
            passFail = 0;
            break;
        }
    }
	printf("Return Value: %d, Expected: %d \n\n", val, 0);
	
	printf("\n TESTING FOR 0 PROVINCE CARD GAME OVER:\n\n");
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        oG.supplyCount[province]= 0;
		val = isGameOver(&oG);
        if (val == 0) {
			passFail = 0;
            break;
		}
	}
	oG.supplyCount[province]= 3;
	printf("Return Value: %d, Expected: %d \n\n", val, 1);
	printf("\n TESTING FOR 1 SUPPLY COUNT 0:\n\n");
	
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        oG.supplyCount[1]= 0;
		val = isGameOver(&oG);
		if (val == 1) {
			passFail = 0;
			break;
		}
	}
	printf("Return Value: %d, Expected: %d \n\n", val, 0);
	
	printf("\n TESTING FOR 2 SUPPLY COUNT 0:\n\n");
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        oG.supplyCount[1]= 0;
		oG.supplyCount[2] = 0;
		val = isGameOver(&oG);
		if (val == 1) {
			passFail = 0;
			break;
		}
	}
	printf("Return Value: %d, Expected: %d \n\n", val, 0);
	
	printf("\n TESTING FOR 3 SUPPLY COUNT 0:\n\n");
	
	for (i = 0; i < x; i++) {
        memcpy(&oG, &G, sizeof(struct gameState));
        oG.supplyCount[0]= 0;
		oG.supplyCount[1] = 0;
		oG.supplyCount[2]= 0;
		val = isGameOver(&oG);
		if (val == 0) {
			passFail = 0;
			break;
		}
	}
	printf("Return Value: %d, Expected: %d \n\n", val, 1);
	
	
	assertTrue(passFail, 1);
	
	return 0;
}

