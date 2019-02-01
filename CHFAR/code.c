#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool possible_sqsum(int *values, int size, int changes) {
    int needed_changes = 0;
    for (int i = 0; i < size; i++) {
        if (values[i] > 1) {
            needed_changes++;

            if (needed_changes > changes) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N, K;
        scanf("%d %d", &N, &K);

        int *A = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }

        if (possible_sqsum(A, N, K)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

        free(A);
    }

    return 0;
}