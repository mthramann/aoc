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

visited = {}
stack = []
group = 0
outside = -1
for adj in adjacent:
    if adj in visited:
        continue
    group += 1
    stack.append(adj)
    visited[adj] = group
    while stack:
        x, y, z = stack.pop()
        if x == -1 and y == -1 and z == -1:
            outside = group
        for dx, dy, dz in deltas:
            if (t := (x + dx, y + dy, z + dz)) not in cubes and \
               -1 <= t[0] <= 21 and -1 <= t[1] <= 22 and -1 <= t[2] <= 22 and \
               t not in visited:
                visited[t] = group
                stack.append(t)

exterior = sum([v for k, v in adjacent.items() if visited[k] == outside])
print(exterior)
