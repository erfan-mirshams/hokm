#include "general.h"
#include "play.h"

int play (int base, int card, int *game, int *fn, int (*deck)[DECKSIZE]) {
    int khal = card / DECKSIZE;
    if (khal != base && fn[base]) {
        return 1;
    }
    *game = card;
    card %= DECKSIZE;
    int flag = 1;
    for (int i = 0; i < fn[khal]; i++) {
        if(deck[khal][i] == card) {
            for (int j = i; j < fn[khal] - 1; j++) {
                swap(deck[khal] + j, deck[khal] + j + 1);
            }
            deck[khal][fn[khal] - 1] = 0;
            fn[khal]--;
            flag = 0;
            break;
        }
    }
    return flag;
}

int winner (int base, int hokm, int *game){
    int mxind = -1, mxval = -1, mxkhal = base;
    for (int i = 0; i < CNT; i++) {
        int khal = game[i] / DECKSIZE, val = game[i] % DECKSIZE;
        if (mxkhal == hokm && khal != mxkhal) {
            continue;
        }
        if (mxkhal != hokm && khal == hokm) {
            mxind = i;
            mxval = val;
            mxkhal = khal;
            continue;
        }
        if (mxkhal == khal && val > mxval) {
            mxind = i;
            mxval = val;
            mxkhal = khal;
        }
    }
    return mxind;
}
