#include "general.h"
#include <stdio.h>

static int card[NUMBEROFCARDS];
static int deck[KHAL][DECKSIZE];

int main() {
    shuffle(card);
    for (int i = 0; i < NUMBEROFCARDS; i++) {
        printf("%d ", card[i]);
    }
    printf("\n");
    return 0;
}
