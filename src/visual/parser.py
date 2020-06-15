# python parser.py < data.input
import sys
import json
import re



f = open(sys.argv[1], 'r')
#ant_qty = int(sys.stdin.readline())
ant_qty = int(f.readline())
#data = sys.stdin.readlines()
data = f.readlines()

start = False
end = False
end_of_map = False
nodes = []
edges = []
moves = []
rounds = []
queue = []
i = 0

for l in data:
    l = l.rstrip('\n')
    if l == "":
        end_of_map = True
    elif l == "##start":
        start = True
    elif l == "##end":
        end = True
    elif l.startswith('#'):
        pass
    elif end_of_map == False:
        if "-" in l:
            source, target = l.strip().split("-")
            edges.append({'data': {"id": source + target, "source": source, "target":  target}})
        else:
            if start == True:
                flag = 0
                start = False
            elif end == True:
                flag = 1
                end = False
            else:
                flag = -1
            name, x, y = l.split()
            if flag == 0:
                start_name = name
            nodes.append({'data': {'id': name, "flag": flag, "ant_id": 0, 'color': 'white'}})
    else:
        i += 1
        ant_moves = l.strip().split()
        for move in ant_moves: 
            ant_id, dest = move.split('-')
            moves.append({
                "ant_id": ant_id[1:],
                "dest": dest
            })
        rounds.append(moves.copy())
        moves.clear()


f = open(sys.argv[2], 'r')
data = f.readlines()
init = False
n = 0
paths = []
path = []
parents = []


for l in data:
    if 'solution' in l:
        if '{red}' not in l:
            paths.clear()
    if '#' in l:
        path = []
        color, path_id, new_path = l.split()
        rooms = new_path.split('-')
        path.append(start_name)
        for room in rooms:
            path.append(room)
        n += 1
        paths.append({'id': n, 'path': path})

print(json.dumps(
        {
            "nodes": nodes,
            "edges": edges,
            "ant_qty": ant_qty,
            "moves": rounds,
            "rounds": i,
            "paths": paths
        }, indent=4, sort_keys=True))
