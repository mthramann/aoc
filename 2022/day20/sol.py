f = open("input.txt", "r")

nums = []
for line in f.readlines():
    nums.append(int(line.strip()))
N = len(nums)

KEY = 811589153
nums = [(ind, val * KEY) for ind, val in enumerate(nums)]

newl = nums.copy()
for _ in range(10):
    for ind, val in nums:
        target = newl.index((ind, val))
        i, curr = newl.pop(target)
        newl.insert((target + curr) % (N - 1), (i, curr))

zero_ind = [i for i in range(N) if newl[i][1] == 0].pop()
print(sum([newl[(i + zero_ind) % N][1] for i in range(1000, 3001, 1000)]))

