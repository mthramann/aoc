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
    for l, r in zip(p1, p2):
        if isinstance(l, int) and isinstance(r, int):
            if l < r:
                return -1
            elif l > r:
                return 1
        else:
            if isinstance(l, int):
                l = [l]
            if isinstance(r, int):
                r = [r]
            if res := less_than(l, r):
                return res
    
    return -1 if len(p1) < len(p2) else (1 if len(p1) > len(p2) else 0)

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
decoders = [[[2]], [[6]]]
for decoder in decoders:
    packets.append(decoder)

packets = sorted(packets, key=cmp_to_key(less_than))
prod = 1
for decoder in decoders:
    prod *= packets.index(decoder) + 1
print(f"Part 2: {prod}")
