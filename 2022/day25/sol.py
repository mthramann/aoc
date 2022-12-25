from functools import reduce
from itertools import zip_longest

f = open("input.txt", "r")
fuels = []
for l in f.readlines():
    digits = [-2 if x == '=' else -1 if x == '-' else int(x) for x in l.strip()]
    digits.reverse()
    fuels.append(digits)

def add(a, b):
    newnum = []
    carry = 0
    for l, r in zip_longest(a, b, fillvalue=0):
        d = l + r + carry
        carry, d = (1, d - 5) if d > 2 else (-1, d + 5) if d < -2 else (0, d)
        newnum.append(d)
    if carry:
        newnum.append(carry)
    return newnum

s = ['=' if d == -2 else '-' if d == -1 else str(d) for d in reduce(add, fuels)]
s.reverse()
print("".join(s))
