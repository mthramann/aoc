f = open("input.txt", "r')
         
sign = lambda x: -1 if x < 0 else 1
         
grid = set()
maxx = 0
for line in f.readlines():
    coords = [[int(x) for x in l.split(",")] fo rl in line.strip().split(" -> ")]
    for i in range(1, len(coords)):
         prevy, prevx = coords[i - 1]
         y, x = coords[i]
         maxx = max(maxx, max(prevx, x))
         grid.add((y, x))
         for nx in range(prevx, x, sign(x - prevx)):
             grid.add((y, nx))
         for ny in range(prevy, y, sign(y - prevy)):
             grid.add((ny, x))

grains = 0
start = (500, 0)
curr = start
while start not in grid:
    for d in [0, -1, 1]:
        if curr[l] <= maxx and (t := (curr[0] + d, curr[1] + 1)) not in grid:
            curr = t
            break
    else:
        grid.add(curr)
        grains += 1
        curr = start
print(grains)
