#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>
#include <sys/random.h>

#define N_MAX 150000
#define c_MAX 150

bool grader(int N, int c, int x, FILE *in, FILE *out);


typedef struct _pipe {
    int output[2];
    int input[2];
} Pipe;


int program_process(Pipe pipes) {
    dup2(pipes.output[1], STDOUT_FILENO);
    close(pipes.output[1]);
    close(pipes.output[0]);

    dup2(pipes.input[0], STDIN_FILENO);
    close(pipes.input[1]);
    close(pipes.input[0]);

    execl("./main", "./main", NULL);
}

#define GENRANDOM(val) \
    (getrandom(&(val), sizeof(val), GRND_RANDOM | GRND_NONBLOCK) >= sizeof(val))
#define GENPRAND(val) \
    (getrandom(&(val), sizeof(val), GRND_NONBLOCK) >= sizeof(val))

int interactive_process(Pipe pipes, int argc, char *argv[]) {
    FILE *in = fdopen(pipes.output[0], "r");
    FILE *out = fdopen(pipes.input[1], "w");

    unsigned seed;
    if (!GENRANDOM(seed) && !GENPRAND(seed)) {
        seed = time(NULL);
    }
    srand(seed);

    int N = rand() % N_MAX + 1;
    int c = rand() % c_MAX + 1;
    int x = rand() % N + 1;

    switch (argc) {
        case 3:
            x = atoi(argv[2]);
        case 2:
            c = atoi(argv[1]);
        case 1:
            N = atoi(argv[0]);
    }

    fprintf(stderr, "GRADING:  N = %d,  c = %d,  x = %d\n", N, c, x);
    if (!grader(N, c, x, in, out)) {
        fprintf(stderr, "WRONG!\n");
    }


    fclose(in);
    fclose(out);

    close(pipes.input[1]);
    close(pipes.input[0]);
    close(pipes.output[1]);
    close(pipes.output[0]);

    wait(NULL);
}


int main(int argc, char *argv[]) {
    Pipe pipes;
    pipe(pipes.output);
    pipe(pipes.input);

    pid_t pid = fork();

    switch (pid) {
        case -1:
            fprintf(stderr, "Fork failed\n");
        break;
        case 0:
            program_process(pipes);
        break;
        default:
            interactive_process(pipes, argc-1, &(argv[1]));
    }

    return pid < 0;
}


typedef enum _op {
    CONNECT = 1,
    FIX = 2,
    ANSWER = 3
} Operation;

Operation read_op(FILE *in, int *value) {
    Operation op;
    if(fscanf(in, "%d", &op) < 1) {
        *value = -1;
        return ANSWER;
    }

    if (op != FIX) {
        fscanf(in, "%d", value);
    }

    return op;
}


typedef enum _st {
    WORKING = 0,
    BROKEN = 1,
    INVALID = -1
} State;


static inline
void answer(FILE *out, State panel) {
    fprintf(out, "%d\n", (int) panel);
    fflush(out);
}

bool op_connect(FILE *out, State *panel, int N, int coins, int x, int value) {
    bool has_coins = (coins > 0);
    bool panel_working = (*panel == WORKING);
    bool value_in_range = ((value > 0) && (value < N));

    if (!has_coins || !panel_working || !value_in_range) {
        answer(out, INVALID);
        return false;
    }

    if (value < x) {
        answer(out, WORKING);
    } else {
        answer(out, BROKEN);
        *panel = BROKEN;
    }
    return true;
}

bool op_fix(State panel, int coins, int c) {
    bool has_coins = (coins >= c);
    bool panel_broken = (panel == BROKEN);

    return has_coins && panel_broken;
}


bool grader(int N, int c, int x, FILE *in, FILE *out) {
    fprintf(out, "%d %d\n", N, c);
    fflush(out);

    int coins = 1000;
    State current = WORKING;

    int value;
    for (Operation op = read_op(in, &value); op != ANSWER; op = read_op(in, &value)) {
        if (op == CONNECT) {
            if (op_connect(out, &current, N, coins, x, value)) {
                coins--;
            }
        } else {
            if (op_fix(current, coins, c)) {
                current = WORKING;
                coins -= c;
            }
        }
    }

    fprintf(stderr, "\tVAL = %d,  COINS = %d\n", value, coins);
    return (value == x);
}
