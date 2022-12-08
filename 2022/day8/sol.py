f = open("input.txt", "r")
grid = []
for line in f.readlines():
    grid.append([int(x) for x in line.strip()])

visible = set()
colmaxs = [-1] * len(grid[0])
rowmaxs = [-1] * len(grid)
for r in range(0, len(grid)):
    for c in range(0, len(grid[0])):
        if grid[r][c] > colmaxs[c]:
            visible.add((r, c))
            colmaxs[c] = grid[r][c]
        if grid[r][c] > rowmaxs[r]:
            visible.add((r, c))
            rowmaxs[r] = grid[r][c]
            
colmaxs = [-1] * len(grid[0])
rowmaxs = [-1] * len(grid)
for r in range(len(grid) - 1, -1, -1):
    for c in range(len(grid[0]) - 1, -1, -1):
        if grid[r][c] > colmaxs[c]:
            visible.add((r, c))
            colmaxs[c] = grid[r][c]
        if grid[r][c] > rowmaxs[r]:
            visible.add((r, c))
            rowmaxs[r] = grid[r][c]

print(len(visible))

max_scenic = 0
# Only consider the interior. Edges are always 0.
for r in range(1, len(grid) - 1):
    for c in range(1, len(grid[0]) - 1):
        scenic = 1
        v = 0
        while r - v > 0:
            v += 1
            if grid[r][c] <= grid[r - v][c]:
                break
        scenic *= v
        v = 0
        while r + v < len(grid) - 1:
            v += 1
            if grid[r][c] <= grid[r + v][c]:
                break
        scenic *= v
        v = 0
        while c + v < len(grid[0]) - 1:
            v += 1
            if grid[r][c] <= grid[r][c + v]:
                break
        scenic *= v
        v = 0
        while c - v > 0:
            v += 1
            if grid[r][c] <= grid[r][c - v]:
                break
        scenic *= v
        max_scenic = max(max_scenic, scenic)
print(max_scenic)
        
