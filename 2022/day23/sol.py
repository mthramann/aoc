from collections import defaultdict

def printgrid(elves):
    ys, xs = zip(*elves.values())
    minx = min(xs)
    maxx = max(xs)
    miny = min(ys)
    maxy = max(ys)
    grid = [['.'] * (1 + maxx - minx) for _ in range(miny, maxy + 1)]
    for (y, x) in elves.values():
        grid[y - miny][x - minx] = '#'
    for row in grid:
        print("".join(row))

f = open("input.txt", "r")
elves = {}
num_elves = 0
for y, line in enumerate(f.readlines()):
    for x, char in enumerate(line):
        if char == '#':
            elves[num_elves] = (y, x)
            num_elves += 1

deltas = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
def isclear(y, x, existing):
    for dy, dx in deltas:
        if (y + dy, x + dx) in existing:
            return False
    return True

def canMove(d, y, x, existing):
    if d == "N":
        return (y - 1, x - 1) not in existing and (y - 1, x) not in existing and (y - 1, x + 1) not in existing
    elif d == "S":
        return (y + 1, x - 1) not in existing and (y + 1, x) not in existing and (y + 1, x + 1) not in existing
    elif d == "W":
        return (y - 1, x - 1) not in existing and (y, x - 1) not in existing and (y + 1, x - 1) not in existing
    elif d == "E":
        return (y - 1, x + 1) not in existing and (y, x + 1) not in existing and (y + 1, x + 1) not in existing
    return True

dir_order = ["N", "S", "W", "E"]
dirs = {"N": (-1, 0), "S": (1, 0), "W": (0, -1), "E": (0, 1)}

elfmoved = True
r = 0
while elfmoved:
    r += 1
    elfmoved = False
    existing = set(elves.values())
    new_locs = defaultdict(list)
    for id, (y, x) in elves.items():
        if isclear(y, x, existing):
            new_locs[(y, x)].append(id)
            continue
        moved = False
        for d in dir_order:
            if canMove(d, y, x, existing):
                dy, dx = dirs[d]
                moved = True
                elfmoved = True
                new_locs[(y + dy, x + dx)].append(id)
                break
        if not moved:
            new_locs[(y, x)].append(id)
    new_elves = {}

    for (y, x), ids in new_locs.items():
        if len(ids) == 1:
            new_elves[ids[0]] = (y, x)
        else:
            for id in ids:
                new_elves[id] = elves[id]
    elves = new_elves
    dir_order = dir_order[1:] + dir_order[:1]

print(r)
