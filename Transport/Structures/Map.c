#include "Map.h"

const static TransportNode __transport_node_next_node_arr[][] =
{
['{<generator object <listcomp>.<genexpr> at 0x0000020941DC6190>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6260>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6330>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6400>, <generator object <listcomp>.<genexpr> at 0x0000020941DC64D0>, <generator object <listcomp>.<genexpr> at 0x0000020941DC65A0>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6670>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6740>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6810>, <generator object <listcomp>.<genexpr> at 0x0000020941DC68E0>, <generator object <listcomp>.<genexpr> at 0x0000020941DC69B0>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6A80>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6B50>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6C20>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6CF0>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6DC0>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6E90>, <generator object <listcomp>.<genexpr> at 0x0000020941DC6F60>, <generator object <listcomp>.<genexpr> at 0x0000020941DC7030>}']
};
inline TransportNode getNext(const TransportNode from, const TransportNode to) {
    return __transport_node_next_node_arr[from][to];
}

