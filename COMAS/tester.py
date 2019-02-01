from subprocess import Popen, PIPE
import random
import sys


class Program(Popen):
    def __init__(self, args):
        super().__init__(args=args, stdin=PIPE, stdout=PIPE, text=True)

    def print(self, *args, **kwargs):
        kwargs['file'] = self.stdin
        kwargs['flush'] = True
        print(*args, **kwargs)

    def input(self, prompt=None):
        if prompt is not None:
            self.print(prompt)
        return self.stdout.readline().strip()



def has_question(program, answer):
    question = program.input().split()
    values = [int(x) for x in question[1:]]

    answer.append(values)
    return question[0] == '?'


def grader(program, meatball):
    meat = lambda i: meatball[i-1]

    questions = 0

    ans = []
    while has_question(program, ans):
        questions += 1

        balls = ans.pop()
        meatiests = sorted(balls, key=meat, reverse=True)
        program.print(meatiests[2], meatiests[1])

    ans = ans.pop()[0]
    right = ans == max(range(len(meatball)), key=meat)
    return ans, right, questions


if __name__ == "__main__":

    if sys.argv[1:]:
        N = int(sys.argv[1])
    else:
        N = random.randint(6, 100)

    m = list(range(N))
    random.shuffle(m)

    print(m, file=sys.stderr)


    try:
        with Program(['/home/marmis/Documents/Projects/CodeChef/COMAS/main']) as code:
            code.print(1)
            code.print(N)

            ans, right, q = grader(code, m)

            print(f"\ti_m = {ans}")
            if q > N + 3:
                subtasks = "none"
            elif q > 4 + N//2:
                subtasks = "partial"
            else:
                subtasks = "all"
            print(f"\t{q} questions", f"({subtasks})")
            if not right:
                print('Wrong')

    except BrokenPipeError:
        print("Child died", file=sys.stderr)
