#include "DSU.h"
#include "staticsics.h"
#include "GraphUtilities.h"
#include "parserFastG.h"
#include "parserGRP.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, [[maybe_unused]] char *argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    auto [edgesOfGraph, totalAmountOfEdges] = (argc == 2 ? getCanonicalDataFastG(cin) : getCanonicalDataGRP(cin));

    { // info about weakly connected components
        auto [sizes, edges] = weakConnectedComponents(edgesOfGraph, totalAmountOfEdges);

        map<size_t, size_t> sizeInfo;
        map<size_t, size_t> edgesInfo;
        map<size_t, size_t> edgesLenInfo;

        for (size_t i = 0; i < sizes.size(); ++i)
            if (sizes[i]){
                ++sizeInfo[sizes[i]];
                ++edgesInfo[edges.x[i]];
                ++edgesLenInfo[edges.y[i]];
            }

        cout << "Info about weakly connected components:\n\n";
        cout << "Amount of vertices in a component : amount of components\n";
        for (auto const & x : sizeInfo)
            cout << x.first << " : " << x.second << '\n';
        
        cout << "\nAmount of edges in a component : amount of components\n";
        for (auto const & x : edgesInfo)
            cout << x.first << " : " << x.second << '\n';

        cout << "\nTotal length of edges in a component : amount of components\n";
        for (auto const & x : edgesLenInfo)
            cout << x.first << " : " << x.second << '\n';
    }

    return 0;
}