class File:
    def __init__(self, name, size):
        self._size = size
        self._name = name

    @property
    def size(self):
        return self._size

    @property
    def name(self):
        return self._name

class Dir:
    def __init__(self, parent, name):
        self._parent = parent
        self._name = name
        self._subdirs = {}
        self._files = []

    @property
    def parent(self):
        return self._parent

    def add_file(self, name, size):
        self._files.append(File(name, size))

    def add_dir(self, name):
        self._subdirs[name] = Dir(self, name)

    def get_dir(self, name):
        return self._subdirs[name]

    def print_dir(self, pads=""):
        print(pads + self._name)
        pads += " " * 4
        for file in self._files:
            print(pads + file.name + " - " + str(file.size))
        for dir in self._subdirs.values():
            dir.print_dir(pads)

    def get_sizes(self, totals):
        total_size = 0
        for dir in self._subdirs.values():
            total_size += dir.get_sizes(totals)
        total_size += sum([f.size for f in self._files])
        totals.append(total_size)
        return total_size
        

f = open("input.txt", "r")
lines = f.readlines()


top_level = Dir(None, "/")
curr = top_level

for line in [x.strip() for x in lines]:
    if line == "$ ls":
        pass
    elif line[0:3] == "dir":
        curr.add_dir(line[4:])
    elif line[0].isdigit():
        size, name = line.split()
        curr.add_file(name, int(size))
    elif line == "$ cd ..":
        curr = curr.parent
    elif line == "$ cd /":
        curr = top_level
    elif line[:4] == "$ cd":
        _, _, name = line.split()
        curr = curr.get_dir(name)
    else:
        print("Doing nothing for: " + line)


total_sizes = []
top_level.get_sizes(total_sizes)
p1_sum = sum([x for x in total_sizes if x <= 100000])
print("Part 1: " + str(p1_sum))

FS_CAPACITY = 70000000
UPDATE_SIZE = 30000000
update_threshold = FS_CAPACITY - UPDATE_SIZE

total_sizes.sort()
curr_size = total_sizes[-1] # assuming we don't have negative sizes
p2 = [x for x in total_sizes if x > curr_size - update_threshold][0]
print(p2)

