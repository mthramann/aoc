# Stitch the remaining 7 cube edges together.
wrapping = {}
for i in range(0, 50):
    wrapping[(i, 49, 2)] = (149 - i, 0, 0)
    wrapping[(149 - i, -1, 2)] = (i, 50, 0)
    wrapping[(i, 150, 0)] = (149 - i, 99, 2)
    wrapping[(149 - i, 100, 0)] = (i, 149, 2)
for i in range(50, 100):
    wrapping[(-1, i, 3)] = (100 + i, 0, 0)
    wrapping[(100 + i, -1, 2)] = (0, i, 1)
    wrapping[(i, 49, 2)] = (100, i - 50, 1)
    wrapping[(99, i - 50, 3)] = (i, 50, 0)
    wrapping[(150, i, 1)] = (100 + i, 49, 2)
    wrapping[(100 + i, 50, 0)] = (149, i, 3)
for i in range(100, 150):
    wrapping[(-1, i, 3)] = (199, i - 100, 3)
    wrapping[(200, i - 100, 1)] = (0, i, 1)
    wrapping[(50, i, 1)] = (i - 50, 99, 2)
    wrapping[(i - 50, 100, 0)] = (49, i, 3)

import re
f = open("input.txt", "r")
grid = []
directions = []
for line in f.readlines():
    if "L" in line:
        directions.extend(re.split("(R|L)", line.strip()))
    else:
        grid.append(list(line)[:-1])

directions = [int(x) if x.isdigit() else x for x in directions]
deltas = {0: (0, 1), 1: (1, 0), 2: (0, -1), 3: (-1, 0)}

facing = 0
row = 0
col = 0
while grid[row][col] == ' ':
    col += 1

for d in directions:
    if isinstance(d, str):
        if d == 'R':
            facing += 1
        if d == 'L':
            facing += 3
        facing %= 4
        continue
    for _ in range(d):
        dr, dc = deltas[facing]
        nr = row + dr
        nc = col + dc
        nf = facing
        if (t := (nr, nc, facing)) in wrapping:
            nr, nc, nf = wrapping[t]

        if grid[nr][nc] == '#':
            break

        facing = nf
        row = nr
        col = nc
print(1000 * (row + 1) + 4 * (col + 1) + facing)


