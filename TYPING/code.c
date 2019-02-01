#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char Word[20+1];

int repeated(Word this, Word *words, int n) {
    for (int i = 0; i < n; i++) {
        if (strncmp(this, words[i], 20) == 0) {
            return i;
        }
    }

    return -1;
}

#define same_hand(letter, next) \
    (abs(letter - next) < 3)

int type_time(Word word) {
    int ttime = 2;
    for (int i = 1; word[i] != '\0'; i++) {
        if (same_hand(word[i-1], word[i])) {
            ttime += 4;
        } else {
            ttime += 2;
        }
    }

    return ttime;
}

int chef_type_time(int n) {
    int *times = malloc(n * sizeof(int));
    Word *words = malloc(n * sizeof(Word));

    for (int i = 0; i < n; i++) {
        scanf("%20s", words[i]);

        int r = repeated(words[i], words, i);
        if (r >= 0) {
            times[i] = times[r]/2;
        } else {
            times[i] = type_time(words[i]);
        }
    }

    int full_time = 0;
    for (int i = 0; i < n; i++) {
        full_time += times[i];
    }

    free(words);
    free(times);

    return full_time;
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d\n", &N);

        int ttime = chef_type_time(N);
        printf("%d\n", ttime);
    }

    return 0;
}
