#ifndef DECKSIZE
#define DECKSIZE 13
#endif
void clear_screen();
void write_seperator (int x);
void inhand (int player, int *fn, int (*deck)[DECKSIZE]);
void draw_board(int *game, int *score, int *round_score, int hokm);
