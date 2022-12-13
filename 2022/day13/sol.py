from functools import cmp_to_key

def parse_list(s, ind = 1):
    ans = []
    while ind < len(s) and s[ind] != ']':
        if s[ind].isdigit():
            start = ind
            while s[ind].isdigit():
                ind += 1
            ans.append(int(s[start:ind]))
        elif s[ind] == '[':
            ind += 1
            subl, ind = parse_list(s, ind)
            ans.append(subl)
            ind += 1
        else:
            ind += 1

    return ans, ind

def less_than(p1, p2):
    for i, el in enumerate(p1):
        if i >= len(p2):
            return 1
        if isinstance(el, int) and isinstance(p2[i], int):
            if el < p2[i]:
                return -1
            elif el > p2[i]:
                return 1
        else:
            l = el
            r = p2[i]
            if isinstance(l, int):
                l = [l]
            if isinstance(r, int):
                r = [r]
            if res := less_than(l, r):
                return res
    return -1 if len(p1) < len(p2) else 0


f = open("input.txt", "r")
packets = []
for lines in f.read().split("\n\n"):
    p1, p2, *_ = lines.split("\n")
    p1, _ = parse_list(p1)
    p2, _ = parse_list(p2)
    packets.append((p1, p2))

correct = 0
for ind, (p1, p2) in enumerate(packets):
    if less_than(p1, p2) == -1:
        correct += ind + 1

print(f"Part 1: {correct}")

packets = [p for t in packets for p in t]
packets.append([[2]])
packets.append([[6]])

packets = sorted(packets, key=cmp_to_key(less_than))
d2 = packets.index([[2]]) + 1
d6 = packets.index([[6]]) + 1
print(f"Part 2: {d2 * d6}")
