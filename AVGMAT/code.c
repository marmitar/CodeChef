#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    short x;
    short y;
} Cell;


typedef struct _stack *Stack;

inline Stack stack_init();
void (*destroy)(Stack) = (void (*)(Stack)) free;
inline bool empty(const Stack);

inline void push(const Stack, const Cell);
inline Cell pop(const Stack);
inline void calc_dists(const Stack, short[], const Cell);

void house_distances(int N, int M) {
    Stack houses = stack_init();

    for (short i = 0; i < N; i++) {
        for (short j = 0; j < M; j++) {
            if (getchar() == '1') {
                Cell house = {.x = i, .y = j};
                push(houses, house);
            }
        }
        getchar();  // read '\n'
    }

    short *distances = calloc(N + M - 2, sizeof(short));

    while (!empty(houses)) {
        calc_dists(houses, distances, pop(houses));
    }

    destroy(houses);

    for (short i = 0; i < N + M - 3; i++) {
        printf("%d ", distances[i]);
    }
    printf("%d\n", distances[N+M-3]);

    free(distances);
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N, M;
        scanf("%d %d\n", &N, &M);

        house_distances(N, M);
    }

    return 0;
}


typedef struct _node {
    struct _node *next;
    Cell data;
} *Node;

typedef struct _stack {
    Node top;
} *Stack;

Stack stack_init() {
    return calloc(1, sizeof(struct _stack));
}

bool empty(const Stack stack) {
    return stack->top == NULL;
}

void push(const Stack stack, const Cell data) {
    Node new = malloc(sizeof(struct _node));
    new->data = data;
    new->next = stack->top;
    stack->top = new;
}

Cell pop(const Stack stack) {
    Node popped = stack->top;
    stack->top = popped->next;
    Cell top_data = popped->data;

    free(popped);
    return top_data;
}

void calc_dists(const Stack stack, short dists[], const Cell initial) {
    for (Node ptr = stack->top; ptr != NULL; ptr = ptr->next) {
        short dx = abs(initial.x - ptr->data.x);
        short dy = abs(initial.y - ptr->data.y);

        short d = dx + dy - 1;
        dists[d]++;
    }
}
