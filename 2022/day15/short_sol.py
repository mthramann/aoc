import re

LIMIT = 4_000_000

f = open("input.txt", "r")
sensors = []
for line in f.readlines():
    sx, sy, bx, by = [int(token) for token in re.findall('-?\d+', line.strip())]
    sensors.append((sx, sy, abs(sx - bx) + abs(sy - by)))

a = set(x-y+r+1 for x,y,r in sensors).intersection(x-y-r-1 for x,y,r in sensors).pop()
b = set(x+y+r+1 for x,y,r in sensors).intersection(x+y-r-1 for x,y,r in sensors).pop()

print(LIMIT * (a + b) // 2 + (b - a) // 2)
