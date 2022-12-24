from collections import defaultdict, deque

f = open("input.txt", "r")
grid = defaultdict(list)
for y, l in enumerate(f.readlines()):
    for x, c in enumerate(l.strip()):
        if c == "#":
            grid[(y, x)] = "#"
        elif c != ".":
            grid[(y, x)].append(c)

ys, xs = zip(*grid)
R = max(ys)
C = max(xs)

def lcm(a, b):
    y = b
    x = a
    while y:
        x, y = y, x % y
    return (a * b) // x

period = lcm(R - 1, C - 1)

winds = {">": (0, 1), "<": (0, -1), "^": (-1, 0), "v": (1, 0)}

def inc(grid):
    newgrid = defaultdict(list)
    for (y, x), els in grid.items():
        if els == "#":
            newgrid[(y, x)] = "#"
            continue
        for b in els:
            dy, dx = winds[b]
            ny = y + dy
            nx = x + dx
            if (ny, nx) in grid and grid[(ny, nx)] == "#":
                if ny == 0:
                    ny = R - 1
                if ny == R:
                    ny = 1
                if nx == 0:
                    nx = C - 1
                if nx == C:
                    nx = 1
            newgrid[(ny, nx)].append(b)
    return newgrid

grids = []
for _ in range(period):
    grids.append(grid)
    grid = inc(grid)

deltas = [(-1, 0), (1, 0), (0, 0), (0, -1), (0, 1)]

def traverse(start, end, start_period):
    visited = set()
    time = 0
    q = deque()
    q.append(start)
    visited.add((*start, start_period))
    while True:
        num_spots = len(q)
        nq = deque()
        time += 1
        currgrid = grids[(time + start_period) % period]
        for _ in range(num_spots):
            y, x = q.popleft()
            if (y, x) == end:
                return time - 1
            for dy, dx in deltas:
                ny = y + dy
                nx = x + dx
                if (ny, nx) not in currgrid and \
                   nx >= 0 and ny >= 0 and \
                   nx <= C and ny <= R and \
                   (t := (ny, nx, (time + start_period + 1) % period)) not in visited:
                    visited.add(t)
                    nq.append((ny, nx))
        q = nq

start = (0, 1)
end = (R, C - 1)
leg1 = traverse(start, end, 0)
leg2 = traverse(end, start, leg1 % period)
leg3 = traverse(start, end, (leg1 + leg2) % period)
print(leg1 + leg2 + leg3)
