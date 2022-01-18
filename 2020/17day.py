# with open("17input.txt") as file :
#     data = file.read().split()

# def get_neighbours(node):
#     all_nodes = []    
#     for x_dif in [-1,0,1]:
#         for y_dif in [-1,0,1]:
#             for z_dif in [-1,0,1]:
#                 x = node[0]
#                 y = node[1]
#                 z = node[2]
#                 node_ = (x + x_dif, y + y_dif, + z + z_dif)                
#                 all_nodes.append(node_) 
#     all_nodes.remove(tuple(node))
#     return all_nodes



# active_nodes = []
# for x, line_cube in enumerate(data): 
#     for y, cube in enumerate(line_cube):
#         if cube == '#' :
#             active_nodes.append((x,y,0))
# print(active_nodes) 
# print(data)

# flag = True 
# i = 0
# while i<6:
#     new_active_nodes = []
#     inactive_nodes = {}
#     for node in active_nodes:
#         neighbours = get_neighbours(node)
#         cpt = 0
#         for neighbour in neighbours:
#             print(neighbour)
#             if neighbour in active_nodes :
#                 cpt += 1
#             else:
#                 if inactive_nodes.get(neighbour):
#                     inactive_nodes[neighbour] += 1
#                 else:
#                     inactive_nodes[neighbour] = 1
#         if cpt == 2 or cpt == 3:
#             new_active_nodes.append(node)
#     for key,value in inactive_nodes.items():
#         if value == 3:
#             new_active_nodes.append(key)
    
#     active_nodes = new_active_nodes
#     i += 1
# print(len(active_nodes))

with open("17input.txt") as file :
    data = file.read().split()

def get_neighbours(node):
    all_nodes = []    
    for x_dif in [-1,0,1]:
        for y_dif in [-1,0,1]:
            for z_dif in [-1,0,1]:
                for w_dif in [-1,0,1]:
                    x = node[0]
                    y = node[1]
                    z = node[2]
                    w = node[3]
                    node_ = (x + x_dif, y + y_dif, + z + z_dif, w + w_dif)                
                    all_nodes.append(node_) 
    all_nodes.remove(tuple(node))
    return all_nodes



active_nodes = []
for x, line_cube in enumerate(data): 
    for y, cube in enumerate(line_cube):
        if cube == '#' :
            active_nodes.append((x,y,0,0))

flag = True 
i = 0
while i<6:
    new_active_nodes = []
    inactive_nodes = {}
    for node in active_nodes:
        neighbours = get_neighbours(node)
        cpt = 0
        for neighbour in neighbours:
            if neighbour in active_nodes :
                cpt += 1
            else:
                if inactive_nodes.get(neighbour):
                    inactive_nodes[neighbour] += 1
                else:
                    inactive_nodes[neighbour] = 1
        if cpt == 2 or cpt == 3:
            new_active_nodes.append(node)
    for key,value in inactive_nodes.items():
        if value == 3:
            new_active_nodes.append(key)
    
    active_nodes = new_active_nodes
    i += 1
print(len(active_nodes))


