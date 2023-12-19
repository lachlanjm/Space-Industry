#ifndef MAP_H
#define MAP_H

#include "..\Enums\TransportNode.h"
#include "..\Enums\TransportConnectionType.h"

#include <stdint.h>

inline TransportNode getNext(const TransportNode from, const TransportNode to);
inline uint_fast16_t getTotalDistance(const TransportNode from, const TransportNode to);
inline uint_fast16_t getNextDistance(const TransportNode from, const TransportNode to);
inline TransportConnectionType getConnectionType(const TransportNode from, const TransportNode to);

#endif