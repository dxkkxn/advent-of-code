import copy
with open("24input.txt") as f:
   data = f.read().strip().split("\n")

all_coords = []
for line in data:
    coords = []
    i = 0
    while i < len(line):
        if line[i] == 'e' or line[i] == 'w':
            coords.append(line[i])
        elif line[i] == 's' or line[i] == 'n':
            coords.append(line[i]+line[i+1])
            i+=1
        i+=1
    all_coords.append(coords)
# 0 - white 1 - black
tiles = {}
tiles[(0,0)] = 0
moves = {'e' : (1,0), 'w':(-1,0), 'ne':(1,-1), 'nw':(0,-1), 'sw':(-1,1), 'se':(0,1)}
for coord in all_coords:
    x, y = 0, 0
    for direction in coord:
        x+= moves[direction][0]
        y+= moves[direction][1]
    if (x,y) not in tiles:
        tiles[(x,y)] = 1
    else:
        if tiles[(x,y)] == 1:
            tiles[(x,y)] = 0
        else:
            tiles[(x,y)] = 1


cpt = 0
black_tiles = []
for coord, color in tiles.items():
    print(coord, color)
    if color == 1:
        black_tiles.append(coord)
        cpt+=1
print(cpt)
print((black_tiles))
#part 2
for _ in range(100):
    black_neigh = {}
    for coord in black_tiles:
        for pos in moves.values():
            x = coord[0]+ pos[0]
            y = coord[1]+ pos[1]
            if (x,y) not in black_neigh.keys():
                black_neigh[(x,y)] = 1
            else:
                black_neigh[(x,y)] += 1

    for coord in black_tiles:
        if coord not in black_neigh:
            black_neigh[coord] = 0

    add_black = []
    remove_black = []
    for coord, bn in black_neigh.items():
        # black
        if coord in black_tiles :
            if bn == 0 or bn>2:
                remove_black.append(coord)
        # white
        else:
            if bn == 2:
                add_black.append(coord)
    black_tiles.extend(add_black)
    for coord in remove_black:
        black_tiles.remove(coord)

    print(len(black_tiles), len(set(black_tiles)))
