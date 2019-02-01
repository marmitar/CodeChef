#include <stdio.h>

const long prime = 1000000000 + 7;

#define cap(x) (((x % prime) * ((x-1) % prime)) % prime)

static inline int max_prod(int sum, int nums) {
    int smallest_sum = ((nums + 1) * nums) / 2;

    int free_nums = sum - smallest_sum;
    if (free_nums < 0) {
        return -1;
    } else if (free_nums < nums) {
        return 0;
    }

    int rolls = (free_nums-1) / nums;
    int last_roll = nums - (free_nums-1) % nums;

    long prod = 1;
    for (long i = 1; i <= nums; i++) {
        if (i == last_roll) {
            prod *= cap(nums + rolls + 1);
        } else {
            prod *= cap(i + rolls);
        }
        if (prod > prime) {
            prod %= prime;
        }
    }

    return prod % prime;
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int N, K;
        scanf("%d %d", &N, &K);

        printf("%d\n", max_prod(N, K));
    }

    return 0;
}