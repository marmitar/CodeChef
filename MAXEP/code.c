#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct _max {
    int coins;
    int x_upper, x_lower;

    int cost;
} *Max;

static
Max init(int limit, int cost) {
    Max new = malloc(sizeof(struct _max));

    new->coins = 1000;
    new->x_lower = 1;
    new->x_upper = limit;
    new->cost = cost;

    return new;
}


#define ERROR_EXIT(max) \
    printf("3 -1\n"); \
    free(max); \
    exit(-1)

#define WORKING  0
#define BROKEN   1
#define INVALID -1


static
void fix_panel(Max m) {
    if (m->cost > m->coins) {
        ERROR_EXIT(m);
    }

    printf("2\n");
    fflush(stdout);

    m->coins -= m->cost;
}

static
bool working_voltage(Max m, int voltage) {
    if (m->coins < 1) {
        ERROR_EXIT(m);
    }

    printf("1 %d\n", voltage);
    fflush(stdout);

    int ans;
    scanf("%d", &ans);

    if (ans == INVALID) {
        ERROR_EXIT(m);
    }

    m->coins--;

    return (ans == WORKING);
}

static inline
void reduce_search(Max max) {
    int factor = 2;
    while (max->x_upper - max->x_lower > max->coins) {
        int next = (max->x_upper-max->x_lower)/factor + max->x_lower;

        if (working_voltage(max, next)) {
            max->x_lower = next;
        } else {
            fix_panel(max);
            factor *= 2;

            max->x_upper = next;
        }
    }
}

static inline
int linear_search(Max max) {
    for (int v = max->x_lower; v < max->x_upper; v++) {
        if (! working_voltage(max, v)) {
            return v;
        }
    }

    return max->x_upper;
}

int main(void) {
    int N, c;
    scanf("%d %d", &N, &c);

    Max max = init(N, c);

    reduce_search(max);
    int x = linear_search(max);

    printf("3 %d\n", x);
    fflush(stdout);

    free(max);
    return 0;
}
