#include "Map.h"

const static TransportNode* __transport_node_next_node_arr[] =
{
	(TransportNode[]) {North_America, South_America, Western_Europe, Western_Europe, West_Africa, Western_Europe, South_America, Western_Europe, East_Asia, East_Asia, East_Asia, East_Asia, South_America, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {North_America, South_America, North_America, North_America, West_Africa, South_Africa, South_Africa, South_Africa, North_America, North_America, South_Africa, Oceania, Oceania, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {North_America, North_America, Western_Europe, Eastern_Europe, North_America, North_Africa, North_Africa, Eastern_Europe, Eastern_Europe, North_America, North_America, North_America, North_America, North_America, North_America, North_America, North_America, North_America, North_America}, 
	(TransportNode[]) {Western_Europe, Western_Europe, Western_Europe, Eastern_Europe, North_Africa, North_Africa, North_Africa, Middle_East, Central_Asia, Central_Asia, Middle_East, Middle_East, North_Africa, Middle_East, Middle_East, Middle_East, Middle_East, Middle_East, Middle_East}, 
	(TransportNode[]) {North_America, South_America, North_America, North_Africa, West_Africa, North_Africa, South_Africa, North_Africa, North_America, North_America, South_Africa, North_America, South_America, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {West_Africa, West_Africa, Western_Europe, Eastern_Europe, West_Africa, North_Africa, South_Africa, Middle_East, Eastern_Europe, West_Africa, South_Africa, South_Africa, South_Africa, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {West_Africa, South_America, North_Africa, North_Africa, West_Africa, North_Africa, South_Africa, North_Africa, South_Asia, South_Asia, South_Asia, South_Asia, Oceania, West_Africa, West_Africa, West_Africa, West_Africa, West_Africa, West_Africa}, 
	(TransportNode[]) {Eastern_Europe, North_Africa, Eastern_Europe, Eastern_Europe, North_Africa, North_Africa, North_Africa, Middle_East, Central_Asia, Central_Asia, South_Asia, South_Asia, North_Africa, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {East_Asia, East_Asia, Eastern_Europe, Eastern_Europe, Middle_East, Middle_East, South_Asia, Middle_East, Central_Asia, East_Asia, South_Asia, East_Asia, East_Asia, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {North_America, North_America, North_America, Central_Asia, North_America, Central_Asia, South_Asia, Central_Asia, Central_Asia, East_Asia, South_Asia, South_East_Asia, South_East_Asia, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {East_Asia, South_Africa, Central_Asia, Central_Asia, South_Africa, Middle_East, South_Africa, Middle_East, Central_Asia, East_Asia, South_Asia, South_East_Asia, South_East_Asia, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {East_Asia, Oceania, East_Asia, East_Asia, East_Asia, South_Asia, South_Asia, South_Asia, East_Asia, East_Asia, South_Asia, South_East_Asia, Oceania, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {South_America, South_America, South_Africa, South_Africa, South_Africa, South_Africa, South_Africa, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, Oceania, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia}, 
	(TransportNode[]) {North_America, South_America, North_America, North_Africa, West_Africa, North_Africa, South_America, Middle_East, Central_Asia, East_Asia, South_Asia, South_East_Asia, South_America, Earth_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit}, 
	(TransportNode[]) {Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Mars_Orbit, Tharsis_Rise, Tharsis_Rise, Utopia_Basin, Tharsis_Rise}, 
	(TransportNode[]) {Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Tharsis_Rise, Hellas_Basin, Utopia_Basin, Vastitas_Borealis}, 
	(TransportNode[]) {Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Hellas_Basin, Utopia_Basin, Vastitas_Borealis}, 
	(TransportNode[]) {Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Tharsis_Rise, Hellas_Basin, Utopia_Basin, Vastitas_Borealis}, 
	(TransportNode[]) {Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Hellas_Basin, Utopia_Basin, Vastitas_Borealis}
};
TransportNode getNext(const TransportNode from, const TransportNode to) {
    return __transport_node_next_node_arr[from][to];
}

const static uint_fast16_t* __transport_node_total_dist_arr[] =
{
	(uint_fast16_t[]) {0, 5, 5, 10, 5, 10, 10, 15, 10, 5, 10, 10, 10, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {5, 0, 10, 15, 5, 10, 5, 15, 15, 10, 10, 10, 5, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {5, 10, 0, 5, 10, 5, 10, 10, 10, 10, 15, 15, 15, 15, 16, 19, 24, 19, 24}, 
	(uint_fast16_t[]) {10, 15, 5, 0, 10, 5, 10, 5, 5, 10, 10, 15, 15, 15, 16, 19, 24, 19, 24}, 
	(uint_fast16_t[]) {5, 5, 10, 10, 0, 5, 5, 10, 15, 10, 10, 15, 10, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {10, 10, 5, 5, 5, 0, 5, 5, 10, 15, 10, 15, 10, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {10, 5, 10, 10, 5, 5, 0, 10, 10, 10, 5, 10, 5, 15, 16, 19, 24, 19, 24}, 
	(uint_fast16_t[]) {15, 15, 10, 5, 10, 5, 10, 0, 5, 10, 5, 10, 15, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {10, 15, 10, 5, 15, 10, 10, 5, 0, 5, 5, 10, 15, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {5, 10, 10, 10, 10, 15, 10, 10, 5, 0, 5, 5, 10, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {10, 10, 15, 10, 10, 10, 5, 5, 5, 5, 0, 5, 10, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {10, 10, 15, 15, 15, 15, 10, 10, 10, 5, 5, 0, 5, 10, 11, 14, 19, 14, 19}, 
	(uint_fast16_t[]) {10, 5, 15, 15, 10, 10, 5, 15, 15, 10, 10, 5, 0, 15, 16, 19, 24, 19, 24}, 
	(uint_fast16_t[]) {10, 10, 15, 15, 10, 10, 15, 10, 10, 10, 10, 10, 15, 0, 1, 4, 9, 4, 9}, 
	(uint_fast16_t[]) {11, 11, 16, 16, 11, 11, 16, 11, 11, 11, 11, 11, 16, 1, 0, 3, 8, 3, 8}, 
	(uint_fast16_t[]) {14, 14, 19, 19, 14, 14, 19, 14, 14, 14, 14, 14, 19, 4, 3, 0, 5, 5, 5}, 
	(uint_fast16_t[]) {19, 19, 24, 24, 19, 19, 24, 19, 19, 19, 19, 19, 24, 9, 8, 5, 0, 5, 5}, 
	(uint_fast16_t[]) {14, 14, 19, 19, 14, 14, 19, 14, 14, 14, 14, 14, 19, 4, 3, 5, 5, 0, 5}, 
	(uint_fast16_t[]) {19, 19, 24, 24, 19, 19, 24, 19, 19, 19, 19, 19, 24, 9, 8, 5, 5, 5, 0}
};
uint_fast16_t getTotalDistance(const TransportNode from, const TransportNode to) {
    return __transport_node_total_dist_arr[from][to];
}

const static uint_fast16_t* __transport_node_next_dist_arr[] =
{
	(uint_fast16_t[]) {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 
	(uint_fast16_t[]) {5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 10, 10, 10, 10, 10, 10}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5}, 
	(uint_fast16_t[]) {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 1, 1, 1, 1, 1}, 
	(uint_fast16_t[]) {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 3, 3, 3}, 
	(uint_fast16_t[]) {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 5, 5, 5}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5}, 
	(uint_fast16_t[]) {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 0, 5}, 
	(uint_fast16_t[]) {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0}
};
uint_fast16_t getNextDistance(const TransportNode from, const TransportNode to) {
    return __transport_node_next_dist_arr[from][to];
}

const static TransportConnectionType* __transport_node_conn_type_arr[] =
{
	(TransportConnectionType[]) {NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {TERRESTRIAL, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {TERRESTRIAL, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, TERRESTRIAL, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {TERRESTRIAL, TERRESTRIAL, NOTHING, NOTHING, NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, TERRESTRIAL, TERRESTRIAL, TERRESTRIAL, NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, TERRESTRIAL, NOTHING, NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, NOTHING, NOTHING, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, NOTHING, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, TERRESTRIAL, TERRESTRIAL, TERRESTRIAL, NOTHING, TERRESTRIAL, NOTHING, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, TERRESTRIAL, NOTHING, TERRESTRIAL, TRANSIT, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {TRANSIT, TRANSIT, NOTHING, NOTHING, TRANSIT, TRANSIT, NOTHING, TRANSIT, TRANSIT, TRANSIT, TRANSIT, TRANSIT, NOTHING, NOTHING, SPACE, NOTHING, NOTHING, NOTHING, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, SPACE, NOTHING, TRANSIT, NOTHING, TRANSIT, NOTHING}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TRANSIT, NOTHING, TERRESTRIAL, TERRESTRIAL, TERRESTRIAL}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, NOTHING, TERRESTRIAL, TERRESTRIAL}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TRANSIT, TERRESTRIAL, TERRESTRIAL, NOTHING, TERRESTRIAL}, 
	(TransportConnectionType[]) {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, TERRESTRIAL, TERRESTRIAL, TERRESTRIAL, NOTHING}
};
TransportConnectionType getConnectionType(const TransportNode from, const TransportNode to) {
    return __transport_node_conn_type_arr[from][to];
}

