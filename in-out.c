#include "general.h"
#include "in-out.h"

int yes_no(char *c){
    char tmp = getchar();
    char kmp = getchar();
    if (kmp != '\n' || (tmp != 'y' && tmp != 'n')) {
        return 1;
    }
    else {
        *c = tmp;
    }
    return 0;
}

int hokm_input(char *c){
    char tmp = getchar();
    if (getchar() != '\n' || (tmp - 'A' < 0 && tmp - 'A' >= CNT)) {
        return 1;
    }
    else {
        *c = tmp;
    }
    return 0;
}

void flush() {
    while(getchar() != '\n');
}
