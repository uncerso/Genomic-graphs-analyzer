#pragma once

#include <unordered_map>
#include <utility>

struct Edge {
    size_t from;
    size_t to;
    size_t len;

    Edge() = default;

    Edge(size_t from, size_t to, size_t len)
        : from(from)
        , to(to)
        , len(len)
    {}
};

template<class T1, class T2>
struct fastPair {
    T1 x;
    T2 y;

    fastPair() = default;
    
    template<class F1, class F2>
    fastPair(F1 && x, F2 && y)
        : x(std::forward<F1>(x))
        , y(std::forward<F2>(y))
    {}
};

template<class F1, class F2>
fastPair(F1 && x, F2 && y) -> fastPair<std::decay_t<F1>, std::decay_t<F2>>;

using EdgeId = size_t;
using EdgesDatabase = std::unordered_map<EdgeId, Edge>;
using CanonicalData = fastPair<EdgesDatabase, size_t /*total amount of edges*/>;
