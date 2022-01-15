# operateurs = set(['+','*'])
# def solve(operation):
#     res = operation[0]
#     op = None
#     for i in range(1,len(operation)):
#         if operation[i] in operateurs:
#             op = operation[i]
#         else:
#             if op == '+':
#                 res += operation[i]
#             elif op == '*':
#                 res *= operation[i]
#     return res

        
# def check_blocks(block_op):
#     i = 0 
#     simplified_op = []
#     while i < len(block_op):
#         if block_op[i] == '(':
#             j = i+1
#             new_block = []
#             other_brackets =  0
#             while block_op[j] != ')' or other_brackets != 0 :
#                 if block_op[j] == '(':
#                     other_brackets += 1
#                 elif block_op[j] == ')':
#                     other_brackets -= 1
#                 new_block.append(block_op[j])
#                 j += 1
#             if '(' in new_block:
#                 s = check_blocks(new_block)
#             else:
#                 s = solve(new_block)
#             block_op = block_op[:i] + [s] + block_op[j+1:]
#         i += 1
#     return solve(block_op)  


# with open("18input.txt") as file:
#     data = file.read().split('\n')
#     sum_each_line = 0
#     for line in data:
#         operation = []
#         for c in line:
#             if c.isnumeric():
#                 operation.append(int(c))
#             elif c != ' ':
#                 operation.append(c)
#         sum_each_line += check_blocks(operation)
        

#     print(sum_each_line)
    
def sum_(l):
    res = 0
    for i in l:
        if type(i) == int:
            res += i
    return res
operateurs = set(['+','*'])
def solve(operation):
    res = 1
    prec = None
    i = 0
    prec = 0
    never = True
    while i < len(operation):
        if operation[i] == '*':
            res *= sum_(operation[prec:i])
            prec = i + 1
            never = False
        i += 1
    if never:
        res =sum_(operation)
    else:
        res *= sum_(operation[prec:])

    return res 
        


        
def check_blocks(block_op):
    i = 0 
    simplified_op = []
    while i < len(block_op):
        if block_op[i] == '(':
            j = i+1
            new_block = []
            other_brackets =  0
            while block_op[j] != ')' or other_brackets != 0 :
                if block_op[j] == '(':
                    other_brackets += 1
                elif block_op[j] == ')':
                    other_brackets -= 1
                new_block.append(block_op[j])
                j += 1
            if '(' in new_block:
                s = check_blocks(new_block)
            else:
                s = solve(new_block)
            block_op = block_op[:i] + [s] + block_op[j+1:]
        i += 1
    return solve(block_op)  

with open("18input.txt") as file:
    data = file.read().split('\n')
    sum_each_line = 0
    for line in data:
        operation = []
        for c in line:
            if c.isnumeric():
                operation.append(int(c))
            elif c != ' ':
                operation.append(c)
        sum_each_line += check_blocks(operation)
        

        print(operation, check_blocks(operation))
    print(sum_each_line)
    


