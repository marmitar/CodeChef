#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *) b) - (*(int *) a);
}

static inline int count_qualifieds(int N, int K) {
    int *S = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    qsort(S, N, sizeof(int), cmp);

    int qualifieds = K;
    for (int i = K; i < N && S[i] == S[i-1]; i++) {
        qualifieds++;
    }

    return qualifieds;
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N, K;
        scanf("%d %d", &N, &K);

        char *line = malloc(12 * N * sizeof(char));
        scanf("%s", &line);
        printf("%s\n", line);
        break;

        int teams = count_qualifieds(N, K);
        printf("%d\n", teams);
    }

    return 0;
}
