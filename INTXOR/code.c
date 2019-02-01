#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


static inline
int ask(int base, int i, int j, int k) {
    printf("1 %d %d %d\n", base+i, base+j, base+k);
    fflush(stdout);

    int answer;
    scanf("%d", &answer);
    if (answer < 0) {
        exit(-1);
    }

    return answer;
}

static inline
void find_four(int *a, int b) {
    int xor123 = ask(b, 1, 2, 3);
    int xor234 = ask(b, 2, 3, 4);
    int xor341 = ask(b, 3, 4, 1);
    int xor412 = ask(b, 4, 1, 2);

    a[b+0] = xor341 ^ xor412 ^ xor123;
    a[b+1] = xor412 ^ xor123 ^ xor234;
    a[b+2] = xor123 ^ xor234 ^ xor341;
    a[b+3] = xor234 ^ xor341 ^ xor412;
}

static
void find_five(int *a, int b) {
    int xor123 = ask(b, 1, 2, 3);
    int xor234 = ask(b, 2, 3, 4);
    int xor345 = ask(b, 3, 4, 5);
    int xor451 = ask(b, 4, 5, 1);
    int xor512 = ask(b, 5, 1, 2);

    a[b+0] = xor512 ^ xor234 ^ xor345;
    a[b+1] = xor123 ^ xor345 ^ xor451;
    a[b+2] = xor234 ^ xor451 ^ xor512;
    a[b+3] = xor345 ^ xor512 ^ xor123;
    a[b+4] = xor451 ^ xor123 ^ xor234;
}

static
void find_six(int *a, int b) {
    int xor125 = ask(b, 1, 2, 5);
    int xor341 = ask(b, 3, 4, 1);
    int xor563 = ask(b, 5, 6, 3);
    int xor126 = ask(b, 1, 2, 6);
    int xor342 = ask(b, 3, 4, 2);
    int xor564 = ask(b, 5, 6, 4);

    a[b+0] = xor341 ^ xor563 ^ xor564;
    a[b+1] = xor342 ^ xor563 ^ xor564;
    a[b+2] = xor563 ^ xor125 ^ xor126;
    a[b+3] = xor564 ^ xor125 ^ xor126;
    a[b+4] = xor125 ^ xor341 ^ xor342;
    a[b+5] = xor126 ^ xor341 ^ xor342;
}

static
void find_seven(int *a, int b) {
    int xor124 = ask(b, 1, 2, 4);
    int xor347 = ask(b, 3, 4, 7);
    int xor567 = ask(b, 5, 6, 7);
    int xor126 = ask(b, 1, 2, 6);
    int xor345 = ask(b, 3, 4, 5);
    int xor562 = ask(b, 5, 6, 2);
    int xor137 = ask(b, 1, 3, 7);

    a[b+1] = xor124 ^ xor347 ^ xor137;
    a[b+5] = xor567 ^ xor347 ^ xor345;

    a[b+0] = xor126 ^ a[b+1] ^ a[b+5];
    a[b+4] = xor562 ^ a[b+1] ^ a[b+5];

    a[b+3] = xor124 ^ a[b+0] ^ a[b+1];
    a[b+2] = xor345 ^ a[b+3] ^ a[b+4];
    a[b+6] = xor567 ^ a[b+4] ^ a[b+5];
}

static
int *find_ints(int n) {
    int *a = malloc(sizeof(int) * n);

    int simple = ((n/4)-1) * 4;
    for (int i = 0; i < simple; i += 4) {
        find_four(a, i);
    }

    int last_case = n % 4 + 4;
    switch (last_case) {
        case 4:
            find_four(a, simple);
        break;
        case 5:
            find_five(a, simple);
        break;
        case 6:
            find_six(a, simple);
        break;
        case 7:
            find_seven(a, simple);
        break;
        default:
            exit(-1);
    }

    return a;
}

static
bool right_answer(int *answer, int n) {
    printf("2");
    for (int i = 0; i < n; i++) {
        printf(" %d", answer[i]);
    }
    printf("\n");
    fflush(stdout);

    free(answer);

    int result;
    scanf("%d", &result);

    return (result > 0);
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d", &N);
        if (N < 4) {
            exit(-2);
        }

        int *val = find_ints(N);
        if (! right_answer(val, N)) {
            exit(-1);
        }
    }

    return 0;
}
