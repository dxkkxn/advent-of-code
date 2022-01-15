import time
import pdb
import copy
class Tile:
    def update_matbycol(self):
        mat2 = []
        for i in range(len(self.matbylines[0])):
            str_col = ""
            for j in range(len(self.matbylines)):
                str_col += self.matbylines[j][i]
            mat2.append(str_col)
        self.matbycol = mat2

    def nord(self):
        return self.matbylines[0]
    def south(self):
        return self.matbylines[-1]
    def west(self):
        return self.matbycol[0]
    def east(self):
        return self.matbycol[-1]

    def update_matbylines(self):
        mat2= []
        for i in range(len(self.matbycol[0])):
            line = ""
            for j in range(len(self.matbycol)):
                line += self.matbycol[j][i]
            mat2.append(line)
        self.matbylines = mat2


    def flip_horizontal(self):
        self.matbycol.reverse()
        self.update_matbylines()
        return self

    def flip_vertical(self):
        self.matbylines.reverse()
        self.update_matbycol()
        return self

    def rotate(self):
        self.matbycol = self.matbylines[::-1]
        self.update_matbylines()
        return self

    def __init__(self, num, mat):
        self.num = num
        self.matbylines = mat
        self.update_matbycol()

    def __str__(self):
        return "\n".join(self.matbylines) + "\n"



def accept(tile, i, j):
    orientation = ["nord", "west", "east", "south"]
    neigh = [[-1,0], [0,-1], [0,1], [1,0]]
    for k in range(4):
        ni = i +neigh[k][0]
        nj = j +neigh[k][1]
        if (ni>= 0 and ni < size and nj>=0 and nj<size and sol[ni][nj] != None):
            if orientation[k] == "nord":
                if sol[ni][nj].south() != tile.nord():
                    return False
            elif orientation[k] == "south":
                if sol[ni][nj].nord() != tile.south():
                    return False
            elif orientation[k] == "east":
                if sol[ni][nj].west() != tile.east():
                    return False
            elif orientation[k] == "west":
                if sol[ni][nj].east() != tile.west():
                    return False
                pass
            else:
                print("error")
                exit(0)
    return True


def print_array_tiles(l):
    for i in l:
        print(i.num,end=",")
    print("\n")

finished = False
def solve(i, j):
    global finished, sol
    if not finished:
        if i == size and j == 0:
            print("here")
            print(sol[0][0].num*sol[0][size-1].num*sol[size-1][0].num*sol[size-1][size-1].num)
            finished = True
            for row in range(size):
                for col in range(size):
                    print(sol[row][col].num, end=" ")
                print("\n")
            return
        for tile in all_tiles:
            if mark[tile.num] == False:
                if accept(tile, i, j):
                    sol[i][j] = tile
                    mark[tile.num] = True
                    if j==size-1:
                        solve(i+1, 0)
                        if finished:
                            return;
                    else:
                        solve(i, j+1)
                        if finished:
                            return;
                    sol[i][j] = None
                    mark[tile.num] = False





if __name__ == "__main__":
    with open("20input.txt") as f:
        data = f.read()
        data = data[:-1]
        data = data.split("\n\n")
    all_tiles = []
    for tile in data:
        tile = tile.split('\n')
        num =  int(tile[0][5:-1])
        x = Tile(num, tile[1:])
        all_tiles.append(x)
    size =int(len(all_tiles)**0.5)
    print(size)
    tiles_rotation = []
    print_array_tiles(all_tiles)
    x = len(all_tiles)
    print(x)
    for tile in all_tiles:
        tile_copy = copy.deepcopy(tile)
        tile_copy_1 = copy.deepcopy(tile_copy)
        tile_copy_1.flip_vertical()
        tiles_rotation.append(tile_copy_1)
        for _ in range(3):
            tile_copy = copy.deepcopy(tile_copy)
            tile_copy.rotate()
            tiles_rotation.append(tile_copy)
            tile_copy_1 = copy.deepcopy(tile_copy)
            tile_copy_1.flip_vertical()
            tiles_rotation.append(tile_copy_1)
    all_tiles.extend(tiles_rotation)
    print_array_tiles(all_tiles)
    print(len(all_tiles) )

    sol = [[None for x in range(size)] for x in range(size)]
    mark = {}
    for tile in all_tiles:
        mark[tile.num] = False
    solve(0,0)
    print(sol[2][1])
    #part 2
    for row in range(size):
        for col in range(size):
            sol[row][col].matbylines.pop(0)
            sol[row][col].matbylines.pop(-1)
            sol[row][col].update_matbycol()
            sol[row][col].matbycol.pop(0)
            sol[row][col].matbycol.pop(-1)
            sol[row][col].update_matbylines()
    photo = ["" for _ in range(len(sol[0][0].matbylines)*size)]
    i = 0
    for line in range(size):
        for linex in range(len(sol[0][0].matbylines)):
            for col in range(size):
                photo[i] += sol[line][col].matbylines[linex]
            i += 1

    print(sol[2][1])
    for line in photo :
        print(line)

    sea_monster = ["__________________#_",
                   "#____##____##____###",
                   "_#__#__#__#__#__#___"]
    # all_sea_monsters = []
    # sea_mm = Tile(9999, sea_monster)
    # tile_copy = copy.deepcopy(sea_mm)
    # tile_copy_1 = copy.deepcopy(sea_mm)
    # tile_copy_1.flip_vertical()
    # all_sea_monsters.append(sea_mm)
    # all_sea_monsters.append(tile_copy_1)
    # for _ in range(3):
    #     tile_copy = copy.deepcopy(tile_copy)
    #     tile_copy.rotate()
    #     all_sea_monsters.append(tile_copy)
    #     tile_copy_1 = copy.deepcopy(tile_copy)
    #     tile_copy_1.flip_vertical()
    #     all_sea_monsters.append(tile_copy_1)
    # for monster in all_sea_monsters:
    #     print(monster)

    def coincide(target, comp):
        assert(len(target)==len(comp))
        for i in range(len(comp)):
            if comp[i] == "#" and target[i]!="#":
                return False
        return True

    def color(target,i, j, comp):
        assert(len(target[i:j])==len(comp))
        for k in range(i, j):
            if comp[k-i] == "#" and target[k]=="#":
                target[k] = "0"
        print(target)


    all_photos = []
    photo_tile = Tile(9999,photo)
    tile_copy = copy.deepcopy(photo_tile)
    tile_copy_1 = copy.deepcopy(photo_tile)
    tile_copy_1.flip_vertical()
    all_photos.append(photo_tile)
    all_photos.append(tile_copy_1)
    for _ in range(3):
        tile_copy = copy.deepcopy(tile_copy)
        tile_copy.rotate()
        all_photos.append(tile_copy)
        tile_copy_1 = copy.deepcopy(tile_copy)
        tile_copy_1.flip_vertical()
        all_photos.append(tile_copy_1)
    print("here")
    for photo in all_photos:
        photo = photo.matbylines
        trouve = False
        for line in range(len(photo)):
            for i in range(len(photo[0])):
                h = len(sea_monster[0])
                j = 0
                l = line
                n = 3
                while j < n and l< len(photo) and i+h <= len(photo[l]) and coincide(photo[l][i:i+h],sea_monster[j]):
                    print(i, j, n)
                    l += 1
                    j += 1
                if j == n:
                    print("xddd")
                    trouve = True
                    j = 0
                    l = line
                    while j < n and l< len(photo) and coincide(photo[l][i:i+h],sea_monster[j]):
                        print(photo[l], sea_monster[j])
                        photo[l] = list(photo[l])
                        color(photo[l], i, i+h, sea_monster[j])
                        photo[l] = "".join(photo[l])
                        print(photo[l])
                        l += 1
                        j += 1
        if trouve:
            break;
    cpt = 0
    for line in photo:
        for char in line:
            if char == "#":
                cpt+=1
    print(cpt)
