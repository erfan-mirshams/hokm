#include <stdlib.h>
#include <time.h>
#define KHAL 4
#define CNT 4
#define DECKSIZE 13
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void shuffle(int *card);
void swap (int *a, int *b);
void sort (int *arr, int sz);
