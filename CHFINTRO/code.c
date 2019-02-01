#include <stdio.h>

int main(void) {
    int N, r;
    scanf("%d %d\n", &N, &r);

    for (; N > 0; N--) {
        int R;
        scanf("%d\n", &R);

        printf("%s boi\n", R >= r? "Good" : "Bad");
    }

    return 0;
}
