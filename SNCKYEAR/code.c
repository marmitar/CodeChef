#include <stdio.h>
#include <stdbool.h>

bool codechef_hosted(int year) {
    const int years[] = {2010, 2015, 2016, 2017, 2019};
    const int years_sz = sizeof(years)/sizeof(int);

    for (int i = 0; i < years_sz; i++) {
        if (year == years[i]) {
            return true;
        }
    }

    return false;
}

int main(void) {

    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d", &N);

        if (codechef_hosted(N)) {
            printf("HOSTED\n");
        } else {
            printf("NOT HOSTED\n");
        }
    }

    return 0;
}