def score(c):
    return ord(c) - 96 if c.islower() else ord(c) - 38

f = open("input.txt", "r")
lines = f.readlines()

total = 0
for i in range(0, len(lines), 3):
    sack1 = lines[i].strip()
    sack2 = lines[i + 1].strip()
    sack3 = lines[i + 2].strip()

    dups = set(sack1) & set(sack2) & set(sack3)
    assert len(dups) == 1
    total += score(dups.pop())
print(total)
