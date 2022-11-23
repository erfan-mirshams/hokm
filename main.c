#include "general.h"
#include "start.h"
#include "play.h"
#include "draw.h"
#include <stdio.h>

int main() {
    int card[KHAL * DECKSIZE];
    int bot[CNT] = {-1, -1, -1, -1};
    int deck[CNT][KHAL][DECKSIZE];
    shuffle(card);
    int ord[] = {5, 4, 4};
    int fn[CNT][KHAL]; /*pointers to where the player is able to use their cards*/
    for (int i = 0; i < CNT; i++) {
        printf("Is player %d human? (y for yes n for no)\n", i + 1);
        char c;
        scanf("%c", &c);
        flush();
        bot[i] = (c == 'y' ? 0 : 1);
    }
    //clear_screen();
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
                if(bot[i]) {
                    set_hokm(&hokm, bot_set_hokm(fn[i]));
                    continue;
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
        for (int j = 0; j < KHAL; j++) {
            sort(deck[i][j], fn[i][j]);
        }
    }

    int score[2] = {0, 0};
    int starter = 0; /*the person who starts the round*/
    while(MAX(score[0], score[1]) <= DECKSIZE / 2){
        int base = -1; /*what khal is the base in the begining it's determined by the starter*/
        int game[CNT] = {-1, -1, -1, -1}; /*state of the game*/
        for (int i = 0; i < CNT; i++) {
            clear_screen();
            draw_board(game, score, hokm);
            int cur = (starter + i) % CNT; /*current player*/
            int cardind, cardplayed;
            int khal;
            if (bot[cur]) {
                //inhand(cur, fn[cur], deck[cur]);
                delay();
                if (!i) {
                    cardplayed = bot_start(fn[cur], deck[cur], hokm);
                    khal = cardplayed / DECKSIZE;
                    base = khal;
                    play(base, cardplayed, game + cur, fn[cur], deck[cur]);
                    //printf("CARDPLAYED: %d\n", cardplayed);
                    continue;
                }
                cardplayed = bot_play(cur, base, game, fn[cur], deck[cur], hokm);
                play(base, cardplayed, game + cur, fn[cur], deck[cur]);
                //printf("CARDPLAYED: %d\n", cardplayed);
                continue;
            }
            int flag = 0;
            inhand(cur, fn[cur], deck[cur]);
            do{
                if (flag) {
                    printf("YOU CANNOT PLAY THAT CARD.\n");
                    flag = 0;
                }
                printf("PLAY YOUR CARD: \n");
                scanf("%d", &cardind);
                cardplayed = ind_to_card(fn[cur], deck[cur], cardind);
                khal = cardplayed/ DECKSIZE;
                if(!i){
                    base = khal;
                }
                flag = 1;
            } while (play(base, cardplayed, game + cur, fn[cur], deck[cur]));
        }
        clear_screen();
        draw_board(game, score, hokm);
        delay();
        starter = winner(base, hokm, game); /*winner is the starter of the next round*/
        score[starter & 1]++; /*add score of the winning team*/
    }
    int champ = (score[0] == (DECKSIZE / 2 + 1) ? 1 : 2);
    printf("THE WINNER IS Team%d!!!\n", champ);
    return 0;
}
