f = open("input.txt", "r")

sign = lambda x: -1 if x < 0 else 1

grid = set()

maxx = 0
miny = 500
maxy = 500
for line in f.readlines():
    coords = [[int(x) for x in l.split(",")] for l in line.strip().split(" -> ")]
    for i in range(1, len(coords)):
        prevy, prevx = coords[i - 1]
        y, x = coords[i]
        maxx = max(maxx, max(prevx, x))
        maxy = max(maxy, max(prevy, y))
        miny = min(miny, min(prevy, y))
        grid.add((prevy, prevx))
        grid.add((y, x))
        if prevy == y:
            for nx in range(prevx, x, sign(x - prevx)):
                grid.add((y, nx))
        if prevx == x:
            for ny in range(prevy, y, sign(y - prevy)):
                grid.add((ny, x))
        
grains = 0
start = (500, 0)
curr = start
while start not in grid:
    if curr[1] == maxx + 1:
        grid.add(curr)
        grains += 1
        curr = start
    elif (t := (curr[0], curr[1] + 1)) not in grid:
        curr = t
    elif (t := (curr[0] - 1, curr[1] + 1)) not in grid:
        curr = t
    elif (t := (curr[0] + 1, curr[1] + 1)) not in grid:
        curr = t
    else:
        grid.add(curr)
        grains += 1
        curr = start

print(grains)
