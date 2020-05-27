#pragma once

#include "GraphUtilities.h"

#include <vector>
#include <type_traits>

enum class DSUHeuristicType {None, Rank, Size};

template<DSUHeuristicType heuristicType = DSUHeuristicType::Rank>
class DSU{
    using Rank_type = 
        std::conditional_t<
            heuristicType==DSUHeuristicType::Rank,
            std::vector<int>,
            bool
        >;
    
    using Size_type = 
        std::conditional_t<
            heuristicType==DSUHeuristicType::Size,
            std::vector<size_t>,
            bool
        >;
 
    std::vector<size_t> _parent;
     
    Rank_type _rank;
    Size_type _size;
    Size_type _edges;
    Size_type _edgesLen;

public:

    DSU(size_t sz = 0) 
        : _parent(sz, -1ull)
    {
        if constexpr (heuristicType == DSUHeuristicType::Rank) {
            _rank.resize(sz, 0);
        }

        if constexpr (heuristicType == DSUHeuristicType::Size) {
            _size.resize(sz, 1);
            _edges.resize(sz, 0);
            _edgesLen.resize(sz, 0);
        }
    }

    void makeNewVert() {
        _parent.resize(_parent.size() + 1);
        _parent.back() = -1ull;

        if constexpr (heuristicType == DSUHeuristicType::Rank) {
            _rank.resize(_rank.size() + 1);
            _rank.back() = 0;
        }

        if constexpr (heuristicType == DSUHeuristicType::Size) {
            _size.resize(_size.size() + 1);
            _size.back() = 1;
            _edges.resize(_edges.size() + 1);
            _edges.back() = 0;
            _edgesLen.resize(_edges.size() + 1);
            _edgesLen.back() = 0;
        }
    }

    size_t find(size_t v) noexcept {
        if (_parent[v] == -1ull) return v;
        return _parent[v] = find(_parent[v]);
    }

    std::vector<size_t> const & getRawData() const noexcept {
        return _parent;
    }

    void merge(size_t a, size_t b, size_t len = 0) noexcept {
        a = find(a);
        b = find(b);
    
        if constexpr (heuristicType == DSUHeuristicType::Size) {
            ++_edges[a];
            _edgesLen[a] += len;
        }
        
        if (a == b) return;

        if constexpr (heuristicType == DSUHeuristicType::Rank) {
            if (_rank[a] < _rank[b])
                std::swap(a, b);
            _rank[a] += _rank[a] == _rank[b];
        }

        if constexpr (heuristicType == DSUHeuristicType::Size) {
            if (_size[a] < _size[b])
                std::swap(a, b);
            _size[a] += _size[b];
            _edges[a]+=_edges[b];
            _edgesLen[a]+=_edgesLen[b];
        }

        _parent[b] = a;
    }

    Size_type getSizeInfo() const {
        Size_type ans(_size.size(), 0);
        for (size_t i = 0; i < _size.size(); ++i)
            if (_parent[i] == -1ull)
                ans[i] = _size[i];
        return ans;
    }

    auto getEdgesInfo() const {
        Size_type ansE(_edges.size(), -1ull);
        Size_type ansL(_edges.size(), -1ull);
        for (size_t i = 0; i < _edges.size(); ++i)
            if (_parent[i] == -1ull){
                ansE[i] = _edges[i];
                ansL[i] = _edgesLen[i];
            }
        return fastPair(move(ansE), move(ansL));
    }
};