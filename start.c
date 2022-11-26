#include "start.h"
#include "general.h"

int * distribute (int x, int *cardptr, int *fn, int (*deck)[DECKSIZE]) { /*distribute certain number from the array of cards to the desired player*/
    while (x--) {
        int tmp = *(cardptr++);
        int khal = tmp / DECKSIZE;
        tmp %= DECKSIZE;
        deck[khal][fn[khal]++] = tmp;
    }
    return cardptr;
}

void set_hokm (int *hokm, int x) { /*set's the hokm for human*/
    *hokm = x;
}
