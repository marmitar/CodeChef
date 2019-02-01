#include <stdlib.h>
#include <stdio.h>

#define cap(a) ((a) > 0? (a) : 0)

int cmp(const void *a, const void *b) {
    return (*(int*) a)-(*(int*) b);
}

static inline int wait_time(int queue, int when, int wait) {
    return cap((queue + 1) * wait - when);
}

static inline int min_wait(int wait, int max_time, int waiting, int coming, int *when) {
    int min_wt = wait_time(waiting + coming, max_time, wait);
    if (min_wt <= 0) {
        return 0;
    }

    for (int i = 0; i < coming; i++) {
        int w_time = wait_time(waiting + i, when[i], wait);
        if (w_time <= 0) {
            return 0;
        } else if (w_time < min_wt) {
            min_wt = w_time;
        }
    }

    return min_wt;
}

int main(void) {
    int T;
    scanf("%d", &T);

    int *A = malloc(100000 * sizeof(int));

    for (int t = 0; t < T; t++) {
        int N, M, K, L;
        scanf("%d %d %d %d", &N, &M, &K, &L);

        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }

        qsort(A, N, sizeof(int), cmp);

        printf("%d\n", min_wait(L, K, M, N, A));
    }

    free(A);
    return 0;
}