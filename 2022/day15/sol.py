import re

dist = lambda x, y: abs(x[0] - y[0]) + abs(x[1] - y[1])

LIMIT = 4_000_000

f = open("input.txt", "r")
to_check = set()
sensors = {}
for line in f.readlines():
    sx, sy, bx, by = [int(token) for token in re.findall('-?\d+', line.strip())]
    d = dist((sx, sy), (bx, by))
    sensors[(sx, sy)] = d
    for y in range(sy - d - 1, sy + d + 2):
        leftover = d - abs(sy - y)
        to_check.add((sx - leftover - 1, y))
        to_check.add((sx + leftover + 1, y))

for x, y in to_check:
    if x < 0 or x > LIMIT or y < 0 or y > LIMIT:
        continue
    found = False
    for s, d in sensors.items():
        if dist(s, (x, y)) <= d:
            found = True
            break
    if not found:
        print(f"{x * LIMIT + y}")
        break 

