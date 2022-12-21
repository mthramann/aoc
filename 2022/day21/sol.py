from sympy import solve

monkeys = {}
f = open("input.txt", "r")
for l in f.readlines():
    vals = l.strip().split()
    monkey = vals[0].strip(":")
    if len(vals) == 2:
        monkeys[monkey] = int(vals[1])
        continue
    assert(len(vals) == 4)
    monkeys[monkey] = tuple(vals[1:])
monkeys["humn"] = "x"

def expand(monkey):
    if isinstance(monkeys[monkey], int) or isinstance(monkeys[monkey], str):
        return monkeys[monkey]
    l, op, r = monkeys[monkey]
    lval = expand(l)
    rval = expand(r)
    if isinstance(lval, str) or isinstance(rval, str):
        val = "(" + str(lval) + " " + op + " " + str(rval) + ")"
    elif op == '+':
        val = lval + rval
    elif op == '*':
        val = lval * rval
    elif op == '-':
        val = lval - rval
    elif op == '/':
        val = lval / rval
    monkeys[monkey] = val
    return val
zhms = expand("zhms")
qqqz = expand("qqqz")

zhms += f" - {int(qqqz)}"
print(int(solve(zhms)[0]))

