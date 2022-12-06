buffer = open("input.txt", "r").readline()

for i in range(0, len(buffer) - 14):
    if len(set(buffer[i:i+14])) == 14:
        print(i + 14)
        break
