with open("15input.txt") as file :
    data = file.read()
    data = data.split(',')
    start_num = []
    for num in data: 
        start_num.append(int(num))

i = 0
dico = {}
n = len(start_num)
for i in range(n):
    dico[start_num[i]] = [i+1]

prec_num = start_num[n-1]
for i in range(n, 30000000):
    if (len(dico[prec_num]) < 2):
        num = 0
        if dico.get(num) is None:
            dico[num] = [i+1]
        else :
            dico[num].append(i+1)
        prec_num = num

    else:
        num = dico[prec_num][-1] - dico[prec_num][-2]
        if dico.get(num) is None:
            dico[num] = [i+1]
        elif (len(dico[num]) == 2) :
            dico[num].append(i+1)
            dico[num].pop(0)
        else :
            dico[num].append(i+1)
        prec_num = num

print(num)