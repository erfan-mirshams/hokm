#include "general.h"
#include "draw.h"
#include <stdio.h>
#define WIDTH 53
#define HEIGHT 21

void clear_screen () { /*clears the screen :)*/
    printf("\033[2J\033[1;1H");
}

void write_seperator (int x){
    while (x--) {
        putchar('-');
    }
    putchar('\n');
}

void whitespace (int x){
    while (x--) {
        putchar(' ');
    }
}

void inhand (int player, int *fn, int (*deck)[DECKSIZE]) { /*outputs the deck in the player's hand*/
    printf("PLAYER: %d\n", player + 1);
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

void draw_board(int *game) {
    whitespace(WIDTH / 2 + 1);
    printf("P3\n");
    whitespace(3);
    write_seperator(WIDTH);
    for (int i = 0; i < HEIGHT; i++) {
        if (i != HEIGHT / 2) {
           whitespace(2);
        }
        else {
            printf("P2");
        }
        putchar('|');
        if (!i) {
            whitespace(WIDTH / 2 - 1);
            if (~game[2]) {
                char typ[4];
                convert(game[2], typ);
                printf("%s", typ);
                whitespace(WIDTH / 2 - 1);
            }
            else {
                whitespace(WIDTH / 2 + 2);
            }
            putchar('|');
            putchar('\n');
            continue;
        }
        if (i == HEIGHT - 1) {
            whitespace(WIDTH / 2 - 1);
            if (~game[0]) {
                char typ[4];
                convert(game[0], typ);
                printf("%s", typ);
                whitespace(WIDTH / 2 - 1);
            }
            else {
                whitespace(WIDTH / 2 + 2);
            }
            putchar('|');
            putchar('\n');
            continue;
        }
        if (i == HEIGHT / 2) {
            if (~game[1]) {
                char typ[4];
                convert(game[1], typ);
                printf("%s", typ);
                whitespace(WIDTH - 6);
            }else {
                whitespace(WIDTH - 3);
            }
            if (~game[3]) {
                char typ[4];
                convert(game[3], typ);
                printf("%s", typ);
            }else {
                whitespace(3);
            }
            putchar('|');
            printf("P4\n");
            continue;
        }
        whitespace(WIDTH);
        putchar('|');
        putchar('\n');
    }
    whitespace(3);
    write_seperator(WIDTH);
    whitespace(3);
    whitespace(WIDTH / 2);
    printf("P1\n");
}
