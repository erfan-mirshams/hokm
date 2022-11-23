#ifndef DECKSIZE
#define DECKSIZE 13
#endif
int bot_set_hokm(int *fn);
int bot_start(int *fn, int (*deck)[DECKSIZE], int hokm);
int bot_play (int ind, int base, int *game, int *fn, int (*deck)[DECKSIZE], int hokm);
int play (int base, int card, int *game, int *fn, int (*deck)[DECKSIZE]);
int winner (int base, int hokm, int *game);
