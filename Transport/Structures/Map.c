#include "Map.h"

const static TransportNode* __transport_node_next_node_arr[] =
{
	(TransportNode[]) {North_America, North_America, North_America, Western_Europe, North_America, Western_Europe, South_America, Western_Europe, East_Asia, North_America, East_Asia, East_Asia, South_America, North_America, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {South_America, South_America, North_America, North_America, South_America, South_Africa, South_America, South_Africa, North_America, North_America, South_Africa, Oceania, South_America, South_America, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {Western_Europe, North_America, Western_Europe, Western_Europe, North_America, Western_Europe, North_Africa, Eastern_Europe, Eastern_Europe, North_America, North_America, North_America, North_America, North_America, North_America, North_America, North_America, North_America, North_America}, 
	(TransportNode[]) {Western_Europe, Western_Europe, Eastern_Europe, Eastern_Europe, North_Africa, Eastern_Europe, North_Africa, Eastern_Europe, Eastern_Europe, Central_Asia, Middle_East, Middle_East, North_Africa, Middle_East, Middle_East, Middle_East, Middle_East, Middle_East, Middle_East}, 
	(TransportNode[]) {West_Africa, West_Africa, North_America, North_Africa, West_Africa, West_Africa, West_Africa, North_Africa, North_America, North_America, South_Africa, North_America, South_America, West_Africa, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {West_Africa, West_Africa, North_Africa, North_Africa, North_Africa, North_Africa, North_Africa, North_Africa, Eastern_Europe, West_Africa, South_Africa, South_Africa, South_Africa, North_Africa, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {West_Africa, South_Africa, North_Africa, North_Africa, South_Africa, South_Africa, South_Africa, North_Africa, South_Asia, South_Asia, South_Africa, South_Asia, South_Africa, West_Africa, West_Africa, West_Africa, West_Africa, West_Africa, West_Africa}, 
	(TransportNode[]) {Eastern_Europe, North_Africa, Eastern_Europe, Middle_East, North_Africa, Middle_East, North_Africa, Middle_East, Middle_East, Central_Asia, Middle_East, South_Asia, North_Africa, Middle_East, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {East_Asia, East_Asia, Eastern_Europe, Central_Asia, Middle_East, Middle_East, South_Asia, Central_Asia, Central_Asia, Central_Asia, Central_Asia, East_Asia, East_Asia, Central_Asia, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {East_Asia, North_America, North_America, Central_Asia, North_America, Central_Asia, South_Asia, Central_Asia, East_Asia, East_Asia, East_Asia, East_Asia, South_East_Asia, East_Asia, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {East_Asia, South_Africa, Central_Asia, Central_Asia, South_Africa, Middle_East, South_Asia, South_Asia, South_Asia, South_Asia, South_Asia, South_Asia, South_East_Asia, South_Asia, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {East_Asia, Oceania, East_Asia, East_Asia, East_Asia, South_Asia, South_Asia, South_Asia, East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit}, 
	(TransportNode[]) {South_America, Oceania, South_Africa, South_Africa, South_Africa, South_Africa, Oceania, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, Oceania, Oceania, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia, South_East_Asia}, 
	(TransportNode[]) {Earth_Orbit, Earth_Orbit, North_America, North_Africa, Earth_Orbit, Earth_Orbit, South_America, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, South_America, Earth_Orbit, Earth_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit}, 
	(TransportNode[]) {Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Earth_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Tharsis_Rise, Mars_Orbit, Tharsis_Rise}, 
	(TransportNode[]) {Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise}, 
	(TransportNode[]) {Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Hellas_Basin, Hellas_Basin, Hellas_Basin, Hellas_Basin}, 
	(TransportNode[]) {Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Mars_Orbit, Utopia_Basin, Utopia_Basin, Utopia_Basin, Utopia_Basin, Utopia_Basin}, 
	(TransportNode[]) {Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Tharsis_Rise, Vastitas_Borealis, Vastitas_Borealis, Vastitas_Borealis, Vastitas_Borealis}
};
inline TransportNode getNext(const TransportNode from, const TransportNode to) {
    return __transport_node_next_node_arr[from][to];
}

