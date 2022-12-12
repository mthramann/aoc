from queue import Queue

f = open("input.txt", "r")

grid = []
for line in f.readlines():
    l = line.strip()
    if "S" in l:
        start = (len(grid), l.index("S"))
        l = l.replace("S", "a")
    if "E" in l:
        end = (len(grid), l.index("E"))
        l = l.replace("E", "z")
    grid.append(l)

deltas = [(0, 1), (0, -1), (-1, 0), (1, 0)]
visited = set()

q = Queue()
q.put((end, 0))
visited.add(end)

while not q.empty():
    (y, x), d = q.get()
    if grid[y][x] == "a":
        print(f"Found one in dist: {d}")
        break
    for dy, dx in deltas:
        ny = y + dy
        nx = x + dx
        if ny >= 0 and ny < len(grid) and \
           nx >= 0 and nx < len(grid[0]) and \
           ord(grid[y][x]) - 1 <= ord(grid[ny][nx]) and \
           (ny, nx) not in visited:
            q.put(((ny, nx), d + 1))
            visited.add((ny, nx))
