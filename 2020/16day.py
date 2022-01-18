with open("16input.txt") as file :
    data = file.read()
    data = data.split("\n") 

i = 0 
print(data)
dico = {}
valid_values = []
while (data[i] != ''):
    valid_range = []
    x = data[i].split(' ')
    index = x[1].index('-')
    low = int(x[1][0:index])
    high = int(x[1][index + 1:])
    for j in range(low,high+1):
        valid_range.append(j)
        if j not in valid_values:
            valid_values.append(j)
    index = x[3].index('-')
    low = int(x[3][0:index])
    high = int(x[3][index + 1:])
    for j in range(low,high+1):
        
        valid_range.append(j)
        if j not in valid_values:
            valid_values.append(j)
    dico[x[0][:-1]] = valid_range


    print(valid_values)
    i += 1

print(dico)
valid_tickets = []
while (i < len(data)):
    if data[i] != '' and data[i] != "your ticket:" and data[i] != "nearby tickets:" :
        ticket = []
        nums = data[i].split(',')
        j = 0 
        valid = True
        while (j < len(nums) and valid):
            num = int(nums[j])
            if num not in valid_values:
                valid = False
            else:
                ticket.append(num)
            j += 1
        if valid:
            valid_tickets.append(ticket)
    i += 1

print(valid_tickets, 'eeeee')

values_for_ins = []
j = 0 
while (j < len(valid_tickets[0])) :
    l = []
    i = 0
    while (i < len(valid_tickets)):
        l.append(valid_tickets[i][j])
        i += 1
    j += 1
    values_for_ins.append(l)
print(values_for_ins)

def constraint(dico_):
    for key,value in dico_.items():
        if len(value) != 1:
            return False 
    return True

order = {}
for i in range(0,len(values_for_ins)):
    for key,value in dico.items():
        j = 0
        flag = True
        while j < len(values_for_ins[i]) and flag:
            value_i = values_for_ins[i][j]
            if value_i not in value:
                flag = False
            j += 1
        if flag:
            if order.get(key) != None :
                order[key].append(i)
            else:
                order[key] = [i] 


while constraint(order) == False : 
    for key,value in order.items():
        if len(value) == 1 : 
            x = value[0] 
            print(x)
            for key_,value_ in order.items():
                if x in value_ and key_ != key:
                    value_.remove(x) 

res = 1 
for key,value in order.items():
    if "departure" in key:
        res *= valid_tickets[0][value[0]] 
print(res)