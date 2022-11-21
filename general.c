#include "general.h"

void swap (int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle (int *card){
    for (int i = 0; i < (KHAL * DECKSIZE); i++) {
        *(card + i) = i; /*initializing array*/
    }
    srand(time(NULL)); /*setting a random seed*/
    for (int i = 0; i < (KHAL * DECKSIZE); i++) { /*doing n random swaps to shuffle the deck*/
        int rnd = rand() % (KHAL * DECKSIZE);
        swap(card + i, card + rnd);
    }
}
