from functools import reduce

items = [[54, 98, 50, 94, 69, 62, 53, 85],
         [71, 55, 82],
         [77, 73, 86, 72, 87],
         [97, 91],
         [78, 97, 51, 85, 66, 63, 62],
         [88],
         [87, 57, 63, 86, 87, 53],
         [73, 59, 82, 65]]
ops = [lambda x : x * 13,
       lambda x : x + 2,
       lambda x : x + 8,
       lambda x : x + 1,
       lambda x : x * 17,
       lambda x : x + 3,
       lambda x : x * x,
       lambda x : x + 6]
test = [3, 13, 19, 17, 5, 7, 11, 2]
edges = [(2, 1), (7, 2), (4, 7), (6, 5), (6, 3), (1, 0), (5, 0), (4, 3)]

prod = reduce((lambda x, y: x * y), test)
    
num_inspected = [0] * 8
for i in range(10000):
    for curr, objects in enumerate(items):
        for object in objects:
            num_inspected[curr] += 1
            new_priority = ops[curr](object) % prod
            dest = edges[curr][new_priority % test[curr] != 0]
            items[dest].append(new_priority)
        items[curr].clear()

num_inspected.sort()
print(num_inspected[-1] * num_inspected[-2])
