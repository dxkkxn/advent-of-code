import copy
import pdb
def play(p1_deck, p2_deck):
    previous_games = []
    while(len(p1_deck)>0 and len(p2_deck)>0):
        p1_copy = p1_deck.copy()
        p2_copy = p2_deck.copy()
        if (p1_copy, p2_copy) in previous_games :
            return 1
        previous_games.append((p1_copy, p2_copy))
        p1 = p1_deck.pop(0)
        p2 = p2_deck.pop(0)
        if p1 <= len(p1_deck) and p2<=len(p2_deck):
            if play(p1_deck[:p1], p2_deck[:p2]) == 1:
                p1_deck.append(p1)
                p1_deck.append(p2)
            else:
                p2_deck.append(p2)
                p2_deck.append(p1)
        else:
            if p1 > p2:
                p1_deck.append(p1)
                p1_deck.append(p2)
            else:
                p2_deck.append(p2)
                p2_deck.append(p1)
    if len(p1_deck) == 0:
        return 2
    else:
        return 1

with open("22input.txt") as f:
    data = f.read().split("\n\n")
    player1 = data[0].split("\n")
    player2 = data[1].split("\n")
    player2.pop(-1)
    player1.pop(0)
    player2.pop(0)
    player1 = [int(x) for x in player1]
    player2 = [int(x) for x in player2]
# previous_games = []
# while(len(player1)>0 and len(player2)>0):
#     previous_games.append((player1, player2))
#     if (player1, player2) in previous_games :
#         break;
#     p1 = player1.pop(0)
#     p2 = player2.pop(0)
#     if p1 > p2:
#         player1.append(p1)
#         player1.append(p2)
#     else:
#         player2.append(p2)
#         player2.append(p1)

# print(player1, player2)

pdb.set_trace()
play(player1, player2)
if len(player1) == 0:
    win = player2
else:
    win = player1
res = 0
win.reverse()
print(win)
for i in range(len(win)):
    res += win[i]*(i+1)
print(res)
