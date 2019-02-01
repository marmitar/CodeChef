#include <stdio.h>


void ask(int question[5], int answer[2]) {
    printf("? %d %d %d %d %d\n",
        question[0], question[1],
        question[2], question[3],
        question[4]
    );
    fflush(stdout);

    scanf("%d %d", &(answer[0]), &(answer[1]));
}


int find_meatiest(int meatballs) {
    int q[5] = {1, 2, 3, 4, 5};
    int a[2];
    ask(q, a);
    return 1;
}


int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d", &N);

        int meatball = find_meatiest(N);
        printf("! %d\n", meatball);
        fflush(stdout);
    }

    return 0;
}
