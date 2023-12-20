#include "TransportNode.h"

const static char* __transport_node_names_char_arr__[] =
{
	"North America",
	"South America",
	"Western Europe",
	"Eastern Europe",
	"West Africa",
	"North Africa",
	"South Africa",
	"Middle East",
	"Central Asia",
	"East Asia",
	"South Asia",
	"South East Asia",
	"Oceania",
	"Earth Orbit",
	"Mars Orbit",
	"Tharsis Rise",
	"Hellas Basin",
	"Utopia Basin",
	"Vastitas Borealis"
};
inline char* getNameTransportNode(TransportNode node) {
    return __transport_node_names_char_arr__[node];
}

