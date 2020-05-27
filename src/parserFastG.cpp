#include "parserFastG.h"
#include "FastNumberParser.h"
#include "DSU.h"

#include <string>
#include <fstream>

using namespace std;

namespace {

auto getEdgeInfo(string const & s, size_t & pos) {
    fastPair<size_t, size_t> ans(0ull, 0ull);

    pos += 6;
    if (pos >= s.size())
        return ans;

    ans.x = getNumFrom(s, pos);
    pos += 8;
    ans.y = getNumFrom(s, pos);

    for (;pos < s.size() && s[pos] != ',' && s[pos] != ':' && s[pos] != '\'' && s[pos] != ';'; ++pos);    

    if (pos < s.size() && s[pos] == '\'')
        ans.x |= static_cast<size_t>(1)<<63; // set the oldest bit
    return ans;
}

auto readGraphFastG(istream & inp) {
    size_t cnt = 0;
    EdgesDatabase ans;
    DSU dsu;
    string s;
    while(!inp.eof()) {
        getline(inp, s);
        if (!s.empty() && s[0] == '>') {
            size_t pos = 0;
            auto tmp = getEdgeInfo(s, pos);
            auto it = ans.find(tmp.x);
            if (it == ans.end()) {
                auto[it2, _] = ans.emplace(tmp.x, Edge(cnt, cnt + 1, tmp.y));
                it = it2;
                cnt += 2;
                dsu.makeNewVert();
                dsu.makeNewVert();
            }
            auto midVert = it->second.to;
            
            while (pos < s.size() && s[pos] != ';') {
                if (s[pos] == '\''){
                    ++pos;
                    continue;
                }
                tmp = getEdgeInfo(s, pos);
                it = ans.find(tmp.x);
                if (it == ans.end()) {
                    auto[it2, _] = ans.emplace(tmp.x, Edge(midVert, cnt++, tmp.y));
                    it = it2;
                    dsu.makeNewVert();
                }
                dsu.merge(dsu.find(midVert), dsu.find(it->second.from));
            }
        }
    }
    return fastPair(move(ans), move(dsu));
}

} // namespace

CanonicalData getCanonicalDataFastG(istream & inp) {
    auto [edgesOfGraph, dsu] = readGraphFastG(inp);

    auto const & rawData = dsu.getRawData();
    vector<size_t> compressedRange(rawData.size());
    size_t cnt = 0;
    for (size_t i = 0; i < rawData.size(); ++i)
        if (rawData[i] == -1ull)
            compressedRange[i] = cnt++;

    for (auto & x : edgesOfGraph){
        x.second.from = compressedRange[dsu.find(x.second.from)];
        x.second.to = compressedRange[dsu.find(x.second.to)];
    }
    return fastPair(move(edgesOfGraph), cnt);
}
