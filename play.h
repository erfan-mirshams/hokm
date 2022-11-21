#ifndef DECKSIZE
#define DECKSIZE 13
#endif
int play (int base, int card, int *game, int *fn, int (*deck)[DECKSIZE]);
int winner (int base, int hokm, int *game);
