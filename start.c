#include "start.h"
#include "general.h"

int * distribute (int x, int *cardptr, int *fn, int (*deck)[DECKSIZE]) {
    while (x--) {
        int tmp = *(cardptr++);
        int khal = tmp / DECKSIZE;
        tmp %= DECKSIZE;
        deck[khal][fn[khal]++] = tmp;
    }
    return cardptr;
}

void set_hokm (int *hokm, int x) {
    *hokm = x;
}
