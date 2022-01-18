# with open("13input.txt") as f :
#     data = f.read()
# data = data.split()
# st_time = int(data[0]) 
# buses_ = data[1].split(",") 
# buses = []
# for bus in buses_:
#     if bus != "x":
#         buses.append(int(bus))

# time = st_time 
# flag = True
# while flag:
#     for bus in buses:
#         if time % bus == 0 :
#             print((time - st_time) * bus)
#             flag = False
#             break
#     time += 1

with open("13input.txt") as f :
    data = f.read()
data = data.split()
buses_ = data[1].split(",") 
pos_buses = {}
buses = []
cpt_num = 0
i = 0
while i < len(buses_) :
    if buses_[i] != "x":
        buses.append(int(buses_[i]))

        pos_buses[int(buses_[i])] = i
        cpt_num += 1
    i +=  1

print(buses, pos_buses, cpt_num)
time = buses[0]
i = 1
step = buses[0]
while i < len(buses):
    while (time + pos_buses[buses[i]]) % buses[i] != 0 :
        time += step
    step *= buses[i]
    i += 1
    print(time)
    
