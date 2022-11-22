#include "general.h"
#include "start.h"
#include "play.h"
#include "draw.h"
#include <stdio.h>

int main() {
    int card[KHAL * DECKSIZE];
    int deck[CNT][KHAL][DECKSIZE];
    shuffle(card);
    int ord[] = {5, 4, 4};
    int fn[CNT][KHAL]; /*pointers to where the player is able to use their cards*/
    for (int i = 0; i < CNT; i++) { /*set fn to zero*/
        for (int j = 0; j < KHAL; j++) {
            fn[i][j] = 0;
        }
    }
    int *cardptr = card;
    int hokm; /*the valuable set of cards*/
    for (int i = 0; i < CNT; i++) {
        for (int j = 0; j < 3; j++) {
            cardptr = distribute(ord[j], cardptr, fn[i], deck[i]);
            if (i == 0 && j == 0) {
                for (int k = 0; k < KHAL; k++) {
                    sort(deck[i][k], fn[i][k]);
                }
                inhand(i, fn[i], deck[i]);
                printf("Enter hokm: \n");
                char c;
                scanf("%c", &c);
                getchar();
                set_hokm(&hokm, c - 'A');
            }
        }
    }

    clear_screen();

    for (int i = 0; i < CNT; i++) { /*sort the cards based on value*/
        //printf("PLAYER: %d\n", i);
        for (int j = 0; j < KHAL; j++) {
            //printf("KHAL: %d\n", j);
            sort(deck[i][j], fn[i][j]);
            /* for (int k = 0; k < fn[i][j]; k++) { */
            /*     printf("%d ", deck[i][j][k]); */
            /* } */
            /* printf("\n"); */
        }
    }


    printf("HOKM: %d\n", hokm);
    int score[2] = {0, 0};
    int starter = 0; /*the person who starts the round*/
    while(MAX(score[0], score[1]) <= DECKSIZE / 2){
        int base = -1; /*what khal is the base in the begining it's determined by the starter*/
        int game[CNT] = {-1, -1, -1, -1}; /*state of the game*/
        for (int i = 0; i < CNT; i++) {
            clear_screen();
            draw_board(game);
            int cur = (starter + i) % CNT; /*current player*/
            int cardind, cardplayed;
            int khal;
            inhand(cur, fn[cur], deck[cur]);
            do{
                printf("PLAY YOUR CARD: \n");
                scanf("%d", &cardind);
                cardplayed = ind_to_card(fn[cur], deck[cur], cardind);
                khal = cardplayed/ DECKSIZE;
                if(!i){
                    base = khal;
                }
            } while (play(base, cardplayed, game + cur, fn[cur], deck[cur]));
        }
        clear_screen();
        draw_board(game);
        starter = winner(base, hokm, game); /*winner is the starter of the next round*/
        score[starter & 1]++; /*add score of the winning team*/
    }
    int champ = (score[0] == (DECKSIZE / 2 + 1) ? 0 : 1);
    printf("THE WINNER IS %d\n", champ);
    return 0;
}
