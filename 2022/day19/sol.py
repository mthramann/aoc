import re
f = open("input.txt", "r")

class Blueprint:
    def __init__(self,
                 ind,
                 ore_cost,
                 clay_cost,
                 obsidian_ore_cost,
                 obsidian_clay_cost,
                 geode_ore_cost,
                 geode_obsidian_cost):
        self.ind = ind
        self.ore_cost = ore_cost
        self.clay_cost = clay_cost
        self.obsidian_ore_cost = obsidian_ore_cost
        self.obsidian_clay_cost = obsidian_clay_cost
        self.geode_ore_cost = geode_ore_cost
        self.geode_obsidian_cost = geode_obsidian_cost

    def max_opened_in(self, minutes):
        self.cache = {}
        self.max_geodes = dict((m, 0) for m in range(minutes + 1))
        return self.traverse((1, 0, 0, 0), (0, 0, 0), minutes)

    def traverse(self, robots, resources, minutes):
        if minutes == 0:
            return 0
        if robots[3] < self.max_geodes[minutes]:
            return 0
        else:
            self.max_geodes[minutes] = robots[3]
        if (robots, resources, minutes) in self.cache:
            return self.cache[(robots, resources, minutes)]

        new_ore = resources[0] + robots[0]
        new_clay = resources[1] + robots[1]
        new_obs = resources[2] + robots[2]
        total_geodes = 0
        rolist = list(robots)
        geode = False
        if self.geode_ore_cost <= resources[0] and self.geode_obsidian_cost <= resources[2]:
            rolist[3] += 1
            total_geodes = max(total_geodes, (minutes - 1) + self.traverse(tuple(rolist), (new_ore - self.geode_ore_cost, new_clay, new_obs - self.geode_obsidian_cost), minutes - 1))
            rolist[3] -= 1
            geode = True
        elif self.obsidian_ore_cost <= resources[0] and self.obsidian_clay_cost <= resources[1]:
            rolist[2] += 1
            total_geodes = max(total_geodes, self.traverse(tuple(rolist),
                                          (new_ore - self.obsidian_ore_cost, new_clay - self.obsidian_clay_cost, new_obs),
                                          minutes - 1))
            rolist[2] -= 1
            geode = True
        if not geode and resources[0] >= self.clay_cost:
            rolist[1] += 1
            total_geodes = max(total_geodes, self.traverse(tuple(rolist),
                                          (new_ore - self.clay_cost, new_clay, new_obs),
                                          minutes - 1))
            rolist[1] -= 1
        if not geode and resources[0] >= self.ore_cost:
            rolist[0] += 1
            total_geodes = max(total_geodes, self.traverse(tuple(rolist),
                                          (new_ore - self.ore_cost, new_clay, new_obs),
                                          minutes - 1))
            rolist[0] -= 1
        if not geode:
            total_geodes = max(total_geodes, self.traverse(robots, (new_ore, new_clay, new_obs), minutes - 1))
        
        self.cache[(robots, resources, minutes)] = total_geodes
        return total_geodes
    
    def quality_level(self):
        return self.ind * self.max_opened_in(24)
    
blueprints = []
for line in f.readlines():
    nums = [int(x) for x in re.findall("\d+", line)]
    b = Blueprint(*nums)
    blueprints.append(b)

TIME = 32
prod = 1
for b in blueprints[:3]:
    prod *= b.max_opened_in(TIME)
print(prod)
