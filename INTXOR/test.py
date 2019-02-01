def cycler(func):
    def cycle(n):
        tuples = set()

        x = 1
        for _ in range(n):
            t = set()
            for _ in range(3):
                t.add(x)
                x = func(x, n)
            tuples.add(frozenset(t))

        return tuples

    return cycle
