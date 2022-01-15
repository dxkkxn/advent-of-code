def to_dec(str):
    i = 0 
    res = 0
    while (i < 36): 
        if (str[-i-1] == '1'):
            res += 2**i 
        i += 1 
    return res



# with open("14input.txt", "r") as file: 
#     data = file.read() 
#     data = data.split('\n')

# memory = {}
# for line in data: 
#     l = line.split(" = ")
#     if l[0] == "mask": 
#         mask = l[1] 
#     else:
#         num = int(l[1])
#         index = int(l[0][l[0].index('[') + 1: l[0].index(']')])
#         i = 0
#         res = ""
#         while i<36 :
#             if mask[-i-1] == 'X':
#                 if (num & 1) : 
#                     res = '1' + res 
#                 else:
#                     res = '0' + res
#             else :
#                 res =  mask[-i-1] + res 
#             num = num>>1 
#             i += 1
#         memory[index] = to_dec(res)
# print(memory, sum(memory.values()))
# too low 917757379638

def all_index(index, mask):
    res = ""
    i = 0 
    cpt = 0
    pos = []
    while (i < 36): 
        if (mask[-i-1] == '1'): 
            res = '1'+ res 
        elif (mask[-i-1] == 'X'):
            res = 'X' + res 
            cpt += 1
            pos.append(36 - i - 1)
        else:
            res =  str(index & 1) + res 
        index = index>>1
        i += 1
    
    all_index = []
    
    for i in range(2**cpt) : 
        p_index = res # posible_index
        j = 0 
        while j < len(pos) : 
            if (i & 1): 
                p_index  = p_index[:pos[j]] + '1' + p_index[pos[j]+1 :]
            else :
                p_index  = p_index[:pos[j]] + '0' + p_index[pos[j]+1 :]
            i = i>>1
            j += 1
        p_index = to_dec(p_index)
        all_index.append(p_index) 
    return all_index 
                


with open("14input.txt", "r") as file: 
    data = file.read() 
    data = data.split('\n')

memory = {}
for line in data: 
    l = line.split(" = ")
    if l[0] == "mask": 
        mask = l[1] 
    else:
        num = int(l[1])
        index = int(l[0][l[0].index('[') + 1: l[0].index(']')])
        # i = 0
        # res = ""
        # while i<36 :
        #     if mask[-i-1] == 'X':
        #         if (num & 1) : 
        #             res = '1' + res 
        #         else:
        #             res = '0' + res
        #     else :
        #         res =  mask[-i-1] + res 
        #     num = num>>1 
        #     i += 1
        possible_index = all_index(index,mask) 
        for index in possible_index : 
            memory[index] = num
            print(num, index)
print(memory, sum(memory.values()))