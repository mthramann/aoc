import re

valves = {}
f = open("input.txt", "r")
for line in f.readlines():
    terms = line.strip().split()
    src = terms[1]
    rate = int(re.findall("\d+", terms[4])[0])
    dests = {d.strip(","): 1 for d in terms[9:]}
    valves[src] = (rate, dests)

# Remove rate=0 valves from graph, instead adding edges with dist > 1
zeros = True
while zeros:
    zeros = False
    for src, (rate, dests) in valves.items():
        newm = {}
        to_remove = set()
        for dest, dist in dests.items():
            if valves[dest][0] != 0:
                continue
            zeros = True
            to_remove.add(dest)
            for nd, ndist in valves[dest][1].items():
                if nd == src:
                    continue
                if nd not in dests:
                    newm[nd] = dist + ndist
                else:
                    dests[nd] = min(dests[nd], ndist + dist)
        dests |= newm
        for d in to_remove:
            del dests[d]

rate_zero = set(v for v, (r, ds) in valves.items() if r == 0)
for d in rate_zero:
    if d != "AA":
        del valves[d]

# Add indices for visited bitset
def add_inds(d):
    newdict = {}
    ind = 0
    for k, values in d.items():
        newdict[k] = (ind, *values)
        ind += 1
    return newdict
valves = add_inds(valves)

dp = {}
def traverse(pos, visited, minutes, elph):
    # Credit to several reddit comments pointing out you could serialize
    # the traversals:
    if minutes == 0:
        return 0 if elph else traverse("AA", visited, 26, True)
    k = (pos, visited, minutes, elph)
    if k in dp:
        return dp[k]

    ind, rate, dests = valves[pos]
    res = 0
    if rate > 0 and not visited & (1 << ind):
        visited |= (1 << ind)
        res = max(res, (minutes - 1) * rate + traverse(pos, visited, minutes - 1, elph))
        visited &= ~(1 << ind)

    for dest, dist in dests.items():
        if dist <= minutes:
            res = max(res, traverse(dest, visited, minutes - dist, elph))
    dp[k] = res
    return res

print(traverse("AA", 0, 26, False))
