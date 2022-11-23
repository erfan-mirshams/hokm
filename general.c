#include "general.h"
#include <stdio.h>

void swap (int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle (int *card){
    for (int i = 0; i < (KHAL * DECKSIZE); i++) {
        *(card + i) = i; /*initializing array*/
    }
    srand(time(NULL)); /*setting a random seed*/
    for (int i = 0; i < (KHAL * DECKSIZE); i++) { /*doing n random swaps to shuffle the deck*/
        int rnd = rand() % (KHAL * DECKSIZE);
        swap(card + i, card + rnd);
    }
}

void delay()
{
    for(int i = 0; i < 1000;i++){
        for (int j = 0; j < 1000; j++) {
            for(int k = 0; k < 1000; k++);
        }
    }
}

void sort (int *arr, int sz) { /*bubble sort algorithm*/
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

void convert(int x, char *ans){
    ans[0] = 'A' + (x / DECKSIZE);
    x %= DECKSIZE;
    x++;
    ans[1] = '0' + (x / 10);
    ans[2] = '0' + (x % 10);
    ans[3] = '\0';
}

int ind_to_card(int *fn, int (*deck)[DECKSIZE], int ind) {
    for (int i = 0; i < KHAL; i++) {
        if (ind >= fn[i]) {
            ind -= fn[i];
            continue;
        }
        return i * DECKSIZE + deck[i][ind];
    }
    return 0;
}

void flush() {
    while(getchar() != '\n');
}
