#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <time.h>
/* COMPILE ERROR
#ifdef __unix__
    #include <sys/syscall.h>
    #ifdef SYS_getrandom
        #include <sys/random.h>
    #endif
#endif
*/

static inline
unsigned gen_seed(void) {
    #ifdef SYS_getrandom
    unsigned seed;
    if (getrandom(&seed, sizeof(seed), GRND_RANDOM | GRND_NONBLOCK) == sizeof(seed)) {
        return seed;
    } else if (getrandom(&seed, sizeof(seed), GRND_NONBLOCK) == sizeof(seed)) {
        return seed;
    }
    #endif

    return time(NULL);
}


#define printff(...) \
    printf(__VA_ARGS__); \
    fflush(stdout)


static inline
int choose_first(void) {
    return 1 + rand() % 3;
}

static inline
bool change(void) {
    return true;
}

#define CHOOSE_OTHER(X, Y) \
    ((1+2+3) - (X+Y))

int main(void) {
    srand(gen_seed());

    int chosen = choose_first();
    printff("%d\n", chosen);

    int opened;
    scanf("%d", &opened);

    if (change()) {
        chosen = CHOOSE_OTHER(chosen, opened);
    }
    printff("%d\n", chosen);

    return 0;
}