from functools import cmp_to_key

cmp = lambda x, y: (x > y) - (x < y)

def compare(p1, p2):
    for l, r in zip(p1, p2):
        if isinstance(l, int) and isinstance(r, int):
            if c := cmp(l, r):
                return c
        else:
            l = [l] if isinstance(l, int) else l
            r = [r] if isinstance(r, int) else r
            if c := compare(l, r):
                return c
    return cmp(len(p1), len(p2))


f = open("input.txt", "r")
packets = []
for lines in f.read().split("\n\n"):
    p1, p2, *_ = lines.split("\n")
    packets.append((eval(p1), eval(p2)))

correct = sum([i for i, p in enumerate(packets, start = 1) if compare(*p) == -1])
print(f"Part 1: {correct}")

packets = [p for t in packets for p in t]
packets.extend([[[2]], [[6]]])
packets = sorted(packets, key=cmp_to_key(compare))
print(f"Part 2: {(1 + packets.index([[2]])) * (1 + packets.index([[6]]))}")
