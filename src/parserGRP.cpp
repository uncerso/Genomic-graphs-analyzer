#include "parserGRP.h"
#include "FastNumberParser.h"

#include <string>
#include <iostream>
using namespace std;

CanonicalData getCanonicalDataGRP(istream & inp) {
    unordered_map<size_t, size_t> verts;
    size_t n, m;
    inp >> n >> m;
    string s;
    getline(inp, s); //skip endl after last reading
    for (size_t i = 0, pos; i < n; ++i){
        pos = 7;
        // Input format:
        // Vertex 12345 ~ 54321 .
        getline(inp, s);
        verts.emplace(getNumFrom(s, pos), 0);
        pos+=3;
        verts.emplace(getNumFrom(s, pos), 0);
    }
    size_t cnt = 0;
    for (auto & x : verts)
        x.second = cnt++;

    EdgesDatabase edges;
    getline(inp, s); //read empty line
    for (size_t i = 0, pos, id, from, to, len; i < m; ++i) {
        getline(inp, s);
        pos = 5;
        // Input format:
        // Edge 98765 : 12345 -> 54321, I = 23 ~ 32 .
        id = getNumFrom(s, pos);
        pos += 3;
        from = getNumFrom(s, pos);
        pos += 4;
        to = getNumFrom(s, pos);
        pos += 6;
        len = getNumFrom(s, pos);
        auto it = verts.find(from);
        from = it->second;
        it = verts.find(to);
        to = it->second;
        edges.emplace(id, Edge(from, to, len));
    }

    return fastPair(move(edges), cnt);
}
