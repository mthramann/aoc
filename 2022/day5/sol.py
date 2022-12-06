import re

f = open("input.txt", "r")
lines = f.readlines()

stacks = [[],
          ['L', 'N', 'W', 'T', 'D'],
          ['C', 'P', 'H'],
          ['W', 'P', 'H', 'N', 'D', 'G', 'M', 'J'],
          ['C', 'W', 'S', 'N', 'T', 'Q', 'L'],
          ['P', 'H', 'C', 'N'],
          ['T', 'H', 'N', 'D', 'M', 'W', 'Q', 'B'],
          ['M', 'B', 'R', 'J', 'G', 'S', 'L'],
          ['Z', 'N', 'W', 'G', 'V', 'B', 'R', 'T'],
          ['W', 'G', 'D', 'N', 'P', 'L']
          ]

for line in lines:
    quant, fr, to = [int(token) for token in re.findall('\d+', line.strip())]
    stacks[to].extend(stacks[fr][-quant:])
    del stacks[fr][-quant:]
for i in range(1, len(stacks)):
    print(stacks[i][-1])
