#!/usr/bin/env python3

import sys
import json

start = False
end = False
end_of_map = False
rooms = {}
tunnels = {}
rounds = {}
i = 1

import os.path
from os import path
if path.exists("parsing.json"):
    os.remove("parsing.json")
for line in sys.stdin:
    line = line.rstrip('\n')
    if (line == "ERROR"):
        print("ERROR")
        quit()
    if (line == ""):
        end_of_map = True
    elif (line[0] == '#' and line != "##start" and line != "##end"):
        pass
    elif (line.isnumeric()):
        ant_qty = int(line)
    elif (line == "##start"):
        start = True
    elif (line == "##end"):
        end = True
    elif (end_of_map == False):
        if (line.find("-") == -1):
            tab = line.split()
            if (start == True):
                flag = 0
                start = False
            elif (end == True):
                flag = 1
                end = False
            else:
                flag = -1
            rooms[tab[0]] = [int(tab[1]), int(tab[2]), flag]
        else:
            tab = line.split('-') 
            if (tab[0] in tunnels.keys()):
                tunnels[tab[0]] += tab[1]
            else:
                tunnels[tab[0]] = [tab[1]]
    else:
        tab = line.split()
        for move in tab:
            tab_move = move.split('-')
            if (i in rounds.keys()):
                rounds[i] += [tab_move[1]]
            else:
                rounds[i] = [tab_move[1]]
        i += 1
data = {
        "ant_qty": ant_qty, 
        "rooms": rooms,
        "tunnels": tunnels, 
        "rounds": rounds
        }
jstring = json.dumps(data)
f = open("parsing.json", "w")
f.write("let MAP = JSON.parse(`%s`)" % jstring)
f.close()
