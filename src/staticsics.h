#pragma once
#include "DSU.h"
#include <vector>
#include <unordered_map>
#include "GraphUtilities.h"

auto weakConnectedComponents(EdgesDatabase const & edges, size_t amountOfVertexes){
    DSU<DSUHeuristicType::Size> dsu(amountOfVertexes);
    for (auto const & [_, edge] : edges) 
        dsu.merge(dsu.find(edge.from), dsu.find(edge.to), edge.len);

    return fastPair(dsu.getSizeInfo(), dsu.getEdgesInfo());
}
