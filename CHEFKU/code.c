#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct {
    int left;
    int right;
} Segment;

static inline void subset_init(int *subset, int K) {
    for (int i = 0; i < K; i++) {
        subset[i] = i;
    }
}

static inline bool subset_increment(int *subset, int K, int N, int at) {
    for (int i = K-at-1; i < K; i++) {
        subset[K-i-1]++;
        if (subset[K-i-1] < N-i) {
            for (int j = K-i; j < K; j++) {
                subset[j] = subset[j-1]+1;
            }
            return true;
        }
    }
    return false;
}

static inline int calc_intersec(Segment *seg, int *subset, int K) {
    int max_l = 0;
    int min_r = 1000000001;

    for (int i = 0; i < K; i++) {
        if (seg[subset[i]].left > max_l) {
            max_l = seg[subset[i]].left;
        }
        if (seg[subset[i]].right < min_r) {
            min_r = seg[subset[i]].right;
        }
        if (min_r <= max_l) {
            return -i;
        }
    }

    return min_r - max_l;
}

static inline int max_intersection(Segment *segs, int segments, int subset_sz, int *subsets) {
    int max = 0;

    subset_init(subsets, subset_sz);
    bool subsets_left = true;
    do {
        int intersec = calc_intersec(segs, subsets, subset_sz);
        if (intersec > max) {
            max = intersec;
        }

        subsets_left = subset_increment(subsets, subset_sz, segments, intersec < 0? -intersec : subset_sz-1);
    } while (subsets_left);

    return max;
}

int main(void) {
    int T;
    scanf("%d", &T);

    Segment *S = malloc(100000 * sizeof(Segment));
    int *subsets = malloc(100000 * sizeof(int));

    for (int t = 0; t < T; t++) {
        int N, K;
        scanf("%d %d", &N, &K);

        for (int i = 0; i < N; i++) {
            scanf("%d %d", &(S[i].left), &(S[i].right));
        }

        printf("%d\n", max_intersection(S, N, K, subsets));
    }

    free(S);
    free(subsets);
    return 0;
}