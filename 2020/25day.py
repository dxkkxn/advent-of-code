public_key_card = 14205034
public_key_door = 18047856

subject_number = 7
value = 1
i = 0
while value != public_key_card:
    value *= subject_number
    value %= 20201227
    i += 1
card_loop_size = i
i = 0
value = 1
while value != public_key_door:
    value *= subject_number
    value %= 20201227
    i += 1
door_loop_size = i
print(card_loop_size, door_loop_size)

i = 0
value =  1
subject_number = public_key_door
while i< card_loop_size:
    value *= subject_number
    value %= 20201227
    i += 1
print(value)
