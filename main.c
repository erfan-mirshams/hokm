#include "general.h"
#include "start.h"
#include <stdio.h>

int main() {
    int card[KHAL * DECKSIZE];
    int deck[CNT][KHAL][DECKSIZE];
    shuffle(card);
    for (int i = 0; i < (KHAL * DECKSIZE); i++) {
        printf("%d ", card[i]);
    }
    printf("\n");
    int ord[] = {5, 4, 4};
    int st[CNT][KHAL], fn[CNT][KHAL]; /*pointers to where the player is able to use their cards*/
    for (int i = 0; i < CNT; i++) { /*set st and fn to zero*/
        for (int j = 0; j < KHAL; j++) {
            st[i][j] = fn[i][j] = 0;
        }
    }
    int *cardptr = card;
    int hokm; /*the valuable set of cards*/
    for (int i = 0; i < CNT; i++) {
        for (int j = 0; j < 3; j++) {
            cardptr = distribute(ord[j], cardptr, fn[i], deck[i]);
            if (i == 0 && j == 0) {
                printf("Enter hokm: \n");
                char c;
                scanf("%c", &c);
                set_hokm(&hokm, c - 'A');
            }
        }
    }
    printf("HOKM: %d\n", hokm);
    return 0;
}
