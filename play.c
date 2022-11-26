#include "general.h"
#include "play.h"

int bepar(int *fn, int (*deck)[DECKSIZE], int hokm) { /*least valuable card from the deck with the minimum card (with exception of hokm)*/
    int ind = -1;
    int mnval = DECKSIZE + 1;
    for (int i = 0; i < KHAL; i++) {
        int cur = (hokm + i + 1) % KHAL;
        if (cur == hokm && ind != -1) {
            break;
        }
        if (fn[cur] < mnval && fn[cur]) {
            mnval = fn[cur];
            ind = cur;
        }
    }
    return ind * DECKSIZE + deck[ind][0];
}

int mx_card(int *fn, int (*deck)[DECKSIZE], int hokm) { /*most valuable card from the deck with the minimum card (with exception of hokm)*/
    int ind = -1;
    int mxval = 0;
    for (int i = 0; i < KHAL; i++) {
        int cur = (hokm + i + 1) % KHAL;
        if (cur == hokm && ind != -1) {
            break;
        }
        if (fn[cur] > mxval && fn[cur]) {
            mxval = fn[cur];
            ind = cur;
        }
    }
    return ind * DECKSIZE + deck[ind][fn[ind] - 1];
}

int bot_set_hokm(int *fn) { /*how the bot would set hokm*/
    int ind = -1, val = 0;
    for (int i = 0; i < KHAL; i++) {
        if (fn[i] > val) {
            ind = i;
            val = 0;
        }
    }
    return ind;
}

int bot_start(int *fn, int (*deck)[DECKSIZE], int hokm) { /*how the bot would start the round*/
    int card = mx_card(fn, deck, hokm);
    return ((card % DECKSIZE) < 11 ? bepar(fn, deck, hokm) : card);
}

int bot_play (int ind, int base, int *game, int *fn, int (*deck)[DECKSIZE], int hokm){ /*the algorithm of how the bot would play*/
    int yar = ind ^ 2;
    int cur_win = winner(base, hokm, game);

    int mn_base = -1, mx_base = -1;
    if (fn[base]) {
        mn_base = deck[base][0];
        mx_base = deck[base][fn[base] - 1];
    }
    int mn_hokm = -1;
    if (fn[hokm]) {
        mn_hokm = deck[hokm][0];
    }

    if (cur_win == yar) { /*when the teammate's card is the winner*/
        if (mn_base != -1){
            return base * DECKSIZE + mn_base;
        }
        return bepar(fn, deck, hokm);
    }
    int winner_card = game[cur_win];
    int winner_khal = game[cur_win] / DECKSIZE;
    if (winner_khal == base && mx_base != -1) { /*normal circumstance*/
        return base * DECKSIZE + (mx_base > (winner_card % DECKSIZE) ? mx_base : mn_base);
    }
    if (winner_khal == base && mn_hokm != -1) { /*cutting with hokm*/
        return hokm * DECKSIZE + mn_hokm;
    }
    if (winner_khal == hokm && mn_base != -1) { /*if the winner has cut*/
        return base * DECKSIZE + mn_base;
    }

    return bepar(fn, deck, hokm); /*other circumstances*/
}

int play (int base, int card, int *game, int *fn, int (*deck)[DECKSIZE]) { /*checks whether the card is valid and adds it to the game state*/
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

int winner (int base, int hokm, int *game){ /*returns the winner of this rotation*/
    int mxind = -1, mxval = -1, mxkhal = base;
    for (int i = 0; i < CNT; i++) {
        if (game[i] == -1) {
            continue;
        }
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
