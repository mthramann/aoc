f = open("input.txt", "r")

deltas = [(-1, 0, 0), (1, 0, 0), (0, -1, 0), (0, 1, 0), (0, 0, -1), (0, 0, 1)]
cubes = set()
for line in f.readlines():
    x, y, z = [int(c) for c in line.strip().split(",")]
    cubes.add((x, y, z))

adjacent = {}
for x, y, z in cubes:
    for dx, dy, dz in deltas:
        if (t := (x + dx, y + dy, z + dz)) not in cubes:
            adjacent[t] = 1 if t not in adjacent else adjacent[t] + 1

visited = set()
stack = []
s = (-1, -1, -1) # Assume on outside
stack.append(s)
visited.add(s)
while stack:
    x, y, z = stack.pop()
    for dx, dy, dz in deltas:
        if (t := (x + dx, y + dy, z + dz)) not in cubes and \
           -1 <= t[0] <= 21 and -1 <= t[1] <= 22 and -1 <= t[2] <= 22 and \
           t not in visited:
            visited.add(t)
            stack.append(t)

exterior = sum([v for k, v in adjacent.items() if k in visited])
print(exterior)
