#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    struct _node *next;
    short x, y;
} *Node;

typedef struct {
    short x, y;
} Point;

int find_houses(Point *houses, const short N, const short M) {
    char *chefland = malloc(N * (M + 1) * sizeof(char));
    fread(chefland, sizeof(char), N * (M + 1), stdin);

    int total_houses = 0;
    for (short i = 0; i < N; i++) {
        for (short j = 0; j < M; j++) {
            if (chefland[(M+1)*i + j] == '1') {
                houses[total_houses++] = (Point) {.x = i, .y = j};
            }
        }
    }

    free(chefland);
    return total_houses;
}

void calc_distances(short *dist, const Point *house, const int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            dist[abs(house[i].x - house[j].x) + abs(house[i].y - house[j].y) - 1]++;
        }
    }
}

#define N 8
void print_vec(short *vec, short n) {
    short i = 0;
    for (; i < n-1-N; i += N) {
        printf("%d %d %d %d %d %d %d %d ", vec[i], vec[i+1], vec[i+2], vec[i+3], vec[i+4], vec[i+5], vec[i+6], vec[i+7]);
    }
    for (; i < n-1; i++) {
        printf("%d ", vec[i]);
    }
    printf("%d\n", vec[n-1]);
}
#undef N

int main(void) {
    int T = getchar() - '0';
    fseek(stdin, 1, SEEK_CUR);

    for (; T > 0; T--) {
        int N, M;
        scanf("%d %d\n", &N, &M);

        Point *houses = malloc(N * M * sizeof(Point));
        int n_houses = find_houses(houses, N, M);

        short *distances = calloc(N + M - 2, sizeof(short));
        calc_distances(distances, houses, n_houses);
        free(houses);

        print_vec(distances, N + M - 2);
        free(distances);
    }

    return 0;
}
