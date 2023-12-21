#ifndef TRASPORT_NODE_H
#define TRASPORT_NODE_H

typedef enum TransportNode {
    North_America = 0,
	South_America = 1,
	Western_Europe = 2,
	Eastern_Europe = 3,
	West_Africa = 4,
	North_Africa = 5,
	South_Africa = 6,
	Middle_East = 7,
	Central_Asia = 8,
	East_Asia = 9,
	South_Asia = 10,
	South_East_Asia = 11,
	Oceania = 12,
	Earth_Orbit = 13,
	Mars_Orbit = 14,
	Tharsis_Rise = 15,
	Hellas_Basin = 16,
	Utopia_Basin = 17,
	Vastitas_Borealis = 18,
    TRANSPORT_NODE_COUNT
} TransportNode;

const char* getNameTransportNode(TransportNode node);

#endif