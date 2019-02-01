#include <stdio.h>

int main(void) {
    int T;
    for (scanf("%d\n", &T); T > 0; T--) {
        int n, m;
        scanf("%d %d\n", &n, &m);

        for (int i = 0; i < m; i++) {
            scanf("%*[^\n]\n");
        }

        if (n%2 == 0) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    return 0;
}
