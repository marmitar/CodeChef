import random
import sys


# max_size = 10
max_value = 100
possible_values = list(range(max_value))

# size = random.randrange(4, max_size+1)
size = int(input())
a = random.sample(possible_values, k=size)
print(a, file=sys.stderr)

while True:
        i, j, k = [int(x)-1 for x in input().split()]
        print(a[i] ^ a[j] ^ a[k])
