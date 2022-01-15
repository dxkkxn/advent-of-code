def shift_clock(clock):
    x = clock.pop(0)
    clock.append(x)

def insert (alist, sublist, index):
    return alist[:index+1]+sublist+alist[index+1:]

def crab_move(n, clock):
    i = 0
    while(i<n):
        curr_cup = clock[0]
        picked_cups = clock[1:4]
        clock.pop(1)
        clock.pop(1)
        clock.pop(1)
        destination = curr_cup - 1
        while destination in picked_cups:
            destination -= 1
        if destination<=0:
            destination = max(clock)
        clock = insert(clock, picked_cups, clock.index(destination))
        shift_clock(clock)
        i+=1
    i = clock.index(1)
    print(clock[i+1], clock[i+2])

def crab_move_linked_list(n):
    i = 0
    while(i<n):
        curr_cup = clock[0]
        picked_cups = clock[1:4]
        clock.pop(1)
        clock.pop(1)
        clock.pop(1)
        destination = curr_cup - 1
        while destination in picked_cups:
            destination -= 1
        if destination<=0:
            destination = max(clock)
        clock = insert(clock, picked_cups, clock.index(destination))
        shift_clock(clock)
        i+=1
    i = clock.index(1)
    print(clock[i+1], clock[i+2])

def enhanced_crab_move(tours, curr_cup, clock):
    i = 0
    while(i<tours):
        picked_cups = []
        n = curr_cup
        for _ in range(3):
            picked_cups.append(clock[n])
            n = clock[n]

        destination = curr_cup - 1
        while destination in picked_cups:
            destination -= 1
        if destination<=0:
            max_key = -1
            for key in clock.keys():
                if key not in picked_cups and key>max_key:
                    max_key = key
            destination = max_key

        clock[curr_cup] = clock[picked_cups[-1]]
        tmp = clock[destination]
        clock[destination] = picked_cups[0]
        clock[picked_cups[-1]] = tmp
        curr_cup = clock[curr_cup]
        i+=1
    x = clock[1]
    print(clock[1]* clock[x])

with open("23input.txt") as f:
    clock_s = (f.read().strip())
    clock = []
    for char in clock_s:
        clock.append(int(char))
    print(clock)
    max_c = max(clock)

    #part 2
    clock = {}
    n = len(clock_s)
    for i in range(n-1):
        clock[int(clock_s[i])] = int(clock_s[i+1])

    x = int(clock_s[-1])
    for i in range(max_c, 1_000_000):
        clock[x] = i+1
        x = i+1
    clock[1_000_000] = int(clock_s[0])
    enhanced_crab_move(10_000_000, 4, clock)
