#ifndef MAP_H
#define MAP_H

#include "..\Enums\TransportNode.h"

#include <stdint.h>

typedef struct Map {
    int i = 0;
} Map;

/*
// [from][to] === next node to go to
Nodes short_path[][] = {
    {1, 2, 2, 2, 2},
    {1, 2, 3, 4, 5},
    {2, 2, 3, 2, 2},
    {2, 2, 2, 4, 5},
    {2, 2, 2, 4, 5}
};
Nodes total_dist[][] = {
    {0, 1, 2, 2, 2},
    {1, 0, 1, 1, 1},
    {1, 1, 0, 2, 2},
    {1, 1, 1, 0, 1},
    {1, 1, 1, 1, 0}
};
Nodes next_dist[][] = {
    {0, 1, 2, 2, 2},
    {1, 0, 1, 1, 1},
    {1, 1, 0, 2, 2},
    {1, 1, 1, 0, 1},
    {1, 1, 1, 1, 0}
};
Nodes types[][] = {
    {0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {0, 0, 0, 3, 3},
    {0, 0, 3, 0, 0},
    {0, 0, 3, 0, 0}
}
*/

#endif