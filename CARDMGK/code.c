#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {SORTED, SORTABLE, UNSORTABLE} Sort;

Sort shuffle_sort(int *card, int st, int end) {
    if (end <= st + 1) {
        return SORTED;
    }

    int mid = (st + end)/2;

    Sort first = shuffle_sort(card, st, mid);
    if (first == UNSORTABLE) {
        return UNSORTABLE;
    }

    Sort last = shuffle_sort(card, mid, end);
    if (last == UNSORTABLE) {
        return UNSORTABLE;
    }

    if (first == SORTED && last == SORTED) {
        if (card[mid-1] < card[mid]) {
            return SORTED;
        } else if (card[end-1] < card[st]) {
            return SORTABLE;
        } else {
            return UNSORTABLE;
        }

    } else if ((first == SORTABLE && last == SORTED)
            || (first == SORTED && last == SORTABLE)) {

        if (card[mid-1] < card[mid] && card[end-1] < card[st]) {
            return SORTABLE;
        } else {
            return UNSORTABLE;
        }
    } else {
        return UNSORTABLE;
    }
}

bool shuffle_sort_possible(int *card, int n) {
    return shuffle_sort(card, 0, n) != UNSORTABLE;
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d\n", &N);

        int *A = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }

        if (shuffle_sort_possible(A, N)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
