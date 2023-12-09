import os

node_h_format = """#ifndef TRASPORT_NODE_H
#define TRASPORT_NODE_H

typedef enum TransportNode {{
    {0}
}} TransportNode;

#endif"""

node_c_start = """#include "TransportNode.h"

"""

map_h_format = """#ifndef MAP_H
#define MAP_H

#include "..\Enums\TransportNode.h"

#include <stdint.h>

typedef struct Map {{
    int i = 0;
}} Map;

{0}

#endif"""

map_c_start = """#include "Map.h"

"""

class Node:
    def __init__(self, name) -> None:
        self.name = name
        self.index = -1
        self.connections = []
        self.next_map = []
        self.tot_dist = []
        self.next_dist = []
        self.next_type = []
    
    def __str__(self) -> str:
        return self.name

    def addConn(self, connection):
        self.connections.append(connection)

class Connection:
    def __init__(self, name, conn_type, dist) -> None:
        self.dest_name = name
        self.type = conn_type
        self.distance = dist
        self.dest = None

function_format = """const static {1} {2}[] =
{{
{3}
}};
{0} {{
    return {2}[from][to];
}}

"""

### Start of program
nodes = []
node_funcs = [
    "inline char* getName(TransportNode node)"
]
norm_params = "(const TransportNode from, const TransportNode to)"
map_funcs = [
    f"inline TransportNode getNext{norm_params}",
    f"inline uint_fast32_t getTotalDistance{norm_params}",
    f"inline uint_fast32_t getNextDistance{norm_params}",
    f"inline TransportConnectionType getConnectionType{norm_params}"
]
arr_groups = [""]

with open(os.path.join(os.path.dirname(__file__), "Map.in"), "r") as f:
    line = f.readline()

    while line:
        if line == "\n":
            arr_groups[0] += '\t"' + nodes[-1].name.replace("_", " ") + '",\n'

        elif line[0] == "\t" or line[0] == " ":
            dst_name = line[:line.index("===>")].strip().replace(" ", "_")
            conn_type = line[line.index("===>")+4:line.index(":")].strip()
            dist = int(line[line.index(":")+1:].strip())
            nodes[-1].addConn(Connection(dst_name, conn_type, dist))
            
        else:
            nodes.append(Node(line.strip().replace(" ", "_")))
        
        line = f.readline()

arr_groups[0] = arr_groups[0][:-2]

for i in range(len(nodes)):
    nodes[i].index = i

##### Node definition
with open(os.path.join(os.path.dirname(__file__), "..\Enums\TransportNode.h"), "w") as f:
    nodes_names = [f"{n.name} = {n.index}" for n in nodes]
    f.write(node_h_format.format(
        ",\n\t".join(nodes_names),
        ";\n".join(node_funcs) + ";\n"
    ))

with open(os.path.join(os.path.dirname(__file__), "..\Enums\TransportNode.c"), "w") as f:
    f.write(node_c_start)

    f.write(function_format.format(node_funcs[0], "char*", "__transport_node_names_char_arr__", arr_groups[0]).replace("from][to", "node").replace("][", ""))

##### Map definition
node_dict = {}
for node in nodes:
    node_dict[node.name] = node

for node in nodes:
    for conn in node.connections:
        conn.dest = node_dict[conn.dest_name]

terr_weight = 1
launch_weight = 100
space_weight = 10000
for start in nodes:
    # Run BFS TODO NOT WORKING
    found_nodes = {node : [None, -1] for node in nodes}
    queue = [(start, 0, [])]

    while len(queue):
        curr = queue.pop(0)
        if found_nodes[curr[0]][0] is None:
            new_path = curr[2] + [curr[0]]
            found_nodes[curr[0]][0] = new_path
            found_nodes[curr[0]][1] = curr[1]

            ### LOGS DISCOVERED PATHS
            #for n in new_path:
            #    print(n, end=' => ')
            #print()

            for conn in curr[0].connections:
                if found_nodes[conn.dest][0] is None:
                    if conn.type == "Terrestrial":
                        new_dist = curr[1] + conn.distance
                    elif conn.type == "Transit":
                        new_dist = curr[1] + launch_weight * conn.distance
                    elif conn.type == "Space":
                        new_dist = curr[1] + space_weight * conn.distance
                    # Insert sort
                    i = 0
                    while i < len(queue) and queue[i][1] <= new_dist:
                        i += 1
                    queue.insert(i, (conn.dest, new_dist, new_path))
    
    for node in nodes:
        if len(found_nodes[node][0]) > 1:
            start.next_map.append(found_nodes[node][0][1])
        else:
            start.next_map.append(start)
        
        start.tot_dist.append(found_nodes[node][1])

        for conn in node.connections:
            if conn.dest is start.next_map[-1]:
                start.next_dist.append(conn.distance)
                start.next_type.append(conn.type)
                break

with open(os.path.join(os.path.dirname(__file__), "..\Structures\Map.h"), "w") as f:
    f.write(map_h_format.format("")) # Empty atm

with open(os.path.join(os.path.dirname(__file__), "..\Structures\Map.c"), "w") as f:
    f.write(map_c_start)

    f.write(function_format.format(map_funcs[0], "TransportNode*", "__transport_node_next_node_arr", 
        str(
            [f"\n\t(TransportNode<|>) {[n.name for n in node.next_map]}" for node in nodes]
        ).replace("[", "{").replace("]", "}").replace("\\t", "\t").replace("\\n", "\n").replace("'", "").replace('"', "").replace("<|>", "[]")[2:-1]
    ))