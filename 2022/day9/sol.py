f = open("input.txt", "r")

def new_tail(h, t):
    dy = h[1] - t[1]
    dx = h[0] - t[0]

    if dy > 0:
        dy -= 1
    elif dy < 0:
        dy += 1
        
    if dx > 0:
        dx -= 1
    elif dx < 0:
        dx += 1
        
    if dy or dx:
        return (h[0] - dx, h[1] - dy)
    return t
        
        
LENGTH = 10
visited = set()
knots = [(0,0) for i in range(LENGTH)]

for d, dist in [l.split() for l in f.readlines()]:
    for i in range(int(dist)):
        x, y = knots[0]
        if d == "R":
            knots[0] = (x + 1, y)
        elif d == "L":
            knots[0] = (x - 1, y)
        elif d == "U":
            knots[0] = (x, y - 1)
        elif d == "D":
            knots[0] = (x, y + 1)

        for i in range(LENGTH - 1):
            knots[i + 1] = new_tail(knots[i], knots[i + 1])
        visited.add(knots[-1])

print(len(visited))
        

