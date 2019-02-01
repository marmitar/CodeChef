T = int(input())

for _ in range(T):
    N, K = (int(x) for x in input().split())

    S = [int(s) for s in input().split()]
    S.sort(reverse=True)

    qualified = sum(s >= S[K-1] for s in S)

    print(qualified)
