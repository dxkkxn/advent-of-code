def get_rules(list_rules):
    sub_list = []
    for char in list_rules.split(' '):
        if char.isnumeric():
            sub_list.append(int(char))
    return tuple(sub_list)

def clean_list(l):
    if l:
        if  isinstance(l[0], list) and len(l) == 1:
            l = l[0]
        else:
            for i in range(len(l)):
                if isinstance(l[i], list) and len(l[i]) == 1:
                    l[i] = l[i][0]


dp = {}
def solve(number, rules):
    rules_number = rules[number]
    if number in dp:
        return dp[number]
    elif type(rules_number) == str:
        dp[number] = rules[number]
        return rules_number
    elif type(rules_number) == list:
        all_ops = []
        for tup in rules_number:
            str_ops = [""]
            str_conj = ""
            for rule in tup:
                solved = solve(rule, rules)
                clean_list(solved)
                new_list = None
                if type(solved) == list:
                    new_list = []
                    for i in range(len(str_ops)):
                        for j in solved:
                            new_list.append(str_ops[i] + j)
                    str_ops =  new_list
                else :
                    for i in range(len(str_ops)):
                        str_ops[i] += solved
            all_ops.extend(str_ops)
            dp[number] = all_ops
        return all_ops
    else :
        str_ops = [""]
        for rule in rules_number:
            solved = solve(rule, rules)
            clean_list(solved)
            new_list = None
            if type(solved) == list:
                new_list = []
                for i in range(len(str_ops)):
                    for j in solved:
                        new_list.append(str_ops[i] + j)
                str_ops =  new_list
            else :
                for i in range(len(str_ops)):
                    str_ops[i] += solved
        dp[number] = str_ops
        return str_ops

def first(num, rules):
    all_valid_str = [""]
    for rule in rules[num]:
        solved = solve(rule, rules)
        clean_list(solved)
        if type(solved) == list:
            new_list =  []
            for i in range(len(all_valid_str)):

                for j in solved:
                    new_list.append(all_valid_str[i] + j)
            all_valid_str = new_list
        else:
            for i in range(len(all_valid_str)):
                all_valid_str[i] += solved

    return all_valid_str




with open("19input.txt") as file:
    data = file.read().split("\n")
    if '' in data:
        data.remove('')
    data.pop(-1)

rules = {}
messages = []
for line in data:
    if line[0].isnumeric():
        i = line.index(":")
        num = int(line[0:i])
        all_values = []
        if '|' in line:
            for sub_list in line[i+1:].split('|'):
                all_values.append(get_rules(sub_list))
        elif line[i+2].isnumeric():
            all_values = get_rules(line[i+2:])
        else:
            all_values = line[i+3]
        rules[num] = all_values

    else:
        messages.append(line)

print(messages)
print(rules)
good_options = (first(0, rules))

cpt = 0
# for mes in messages:
#     if mes in good_options:
#         print(mes)
#         cpt += 1
# print(cpt)


for mes in messages:
    splited_msg =  [mes[i:i+8] for i in range(0, len(mes), 8)]
    r42 = [False for _ in range(len(splited_msg))]
    r31 = [False for _ in range(len(splited_msg))]
    for i in range(len(splited_msg)):
        if splited_msg[i] in dp[42]:
            r42[i] = True
        if splited_msg[i] in dp[31]:
            r31[i] = True
        assert(r42[i]!=r31[i])
    i = 0
    c42, c31 = 0, 0
    if r42[i]:
        c42+=1
        i+=1
        while(i < len(r42) and r42[i]):
            c42+=1
            i+= 1
        while(i<len(r31) and r31[i]):
            c31+=1
            i+= 1
        if i == len(r31) and c42>c31>0:
            cpt+=1


print(cpt)

