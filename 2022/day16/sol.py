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

TIMER = 30

# (Node, tp) -> (visited -> val)
dp = {(k, 0): {0: 0} for k in valves}
for tp in range(1, TIMER + 1):
    for src, (ind, rate, dests) in valves.items():
        release = (tp - 1) * rate
        updates = {}
        for dest, dist in dests.items():
            if tp - dist < 0:
                continue
            for visited, val in dp[(dest, tp - dist)].items():
                updates[visited] = max(updates.get(visited, 0), val)
                
            if tp - dist == 0:
                continue
            for visited, val in dp[(dest, tp - dist - 1)].items():
                if not visited & (1 << ind):
                    visited |= (1 << ind)
                    updates[visited] = max(updates.get(visited, 0), val + release)
                    
        dp[(src, tp)] = updates

maxv = 0
for vis, val in dp[("AA", TIMER)].items():
    maxv = max(maxv, val)
print(maxv)


