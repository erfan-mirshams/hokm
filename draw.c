#include "general.h"
#include "draw.h"
#include <stdio.h>

void clear_screen () { /*clears the screen :)*/
    printf("\033[2J\033[1;1H");
}

void write_seperator (int x){
    while (x--) {
        putchar('-');
    }
    putchar('\n');
}

void inhand (int player, int *fn, int (*deck)[DECKSIZE]) { /*outputs the deck in the player's hand*/
    printf("PLAYER: %d\n", player);
    int tot = 0;
    for (int i = 0; i < KHAL; i++) {
        tot += fn[i];
    }
    write_seperator(tot * 4 + 1);
    printf("|");
    for (int j = 0; j < KHAL; j++) {
        for (int k = 0; k < fn[j]; k++) {
            printf(" %c |", 'A' + j);
        }
    }
    printf("\n");
    write_seperator(tot * 4 + 1);
    printf("|");
    for (int j = 0; j < KHAL; j++) {
        for (int k = 0; k < fn[j]; k++) {
            printf("%3d|", deck[j][k] % DECKSIZE + 1);
        }
    }
    printf("\n");
    write_seperator(tot * 4 + 1);
    printf("|");
    int counter = 0;
    for (int j = 0; j < KHAL; j++) {
        for (int k = 0; k < fn[j]; k++) {
            printf("%3d|", counter++);
        }
    }
    printf("\n");
}
