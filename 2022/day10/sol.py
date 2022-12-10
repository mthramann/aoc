f = open("input.txt", "r")

MONITOR_WIDTH = 40
MONITOR_HEIGHT = 6

def draw_cycle(cycle, reg, monitor):
    crt_draw = (cycle - 1) % MONITOR_WIDTH
    if abs(crt_draw - reg) < 2:  # Sprite is 3 wide centered on reg
            monitor[(cycle - 1) // MONITOR_WIDTH][crt_draw] = '#'

def record_cycle(cycle, reg, monitor, signal_strength):
    signal_strength.append(cycle * reg)
    draw_cycle(cycle, reg, monitor)

cycle = 0
reg = 1
signal_strength = []
monitor = [[' '] * MONITOR_WIDTH for j in range(MONITOR_HEIGHT)]
    
for line in f.readlines():
    if line.strip() == "noop":
        cycle += 1
        record_cycle(cycle, reg, monitor, signal_strength)
    else:
        _, v = line.split()
        cycle += 1
        record_cycle(cycle, reg, monitor, signal_strength)
        cycle += 1
        record_cycle(cycle, reg, monitor, signal_strength)
        reg += int(v)


sssum = 0
for i in range(19, 220, 40):
    sssum += signal_strength[i]
print(sssum)

for row in monitor:
    print("".join(row))
