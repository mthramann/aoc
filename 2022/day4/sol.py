f = open("input.txt", "r")
lines = f.readlines()

def contains(i1, i2):
    i1s, i1e = i1.split('-')
    i2s, i2e = i2.split('-')
    return max(int(i1s), int(i2s)) <= min(int(i2e), int(i1e))

total = 0
for line in lines:
    r1, r2 = line.strip().split(',')
    if contains(r1, r2) or contains(r2, r1):
        total += 1
print(total)
