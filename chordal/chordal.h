#pragma once

#include "util/util.h"

#include <unordered_set>
#include <set>

#include <list>
#include <unordered_map>

using namespace std;

const int MAXN = 10000;

namespace chordal
{

class ChordalGraph
{
public:

    // Constructor throws GraphIsNotChordal if given graph is not Chordal
    ChordalGraph(Graph const& graph);

    // Returns size of minimum FVS
    int FvsCount();

    // Returns FVS
    unordered_set<int> Fvs();

    // Underlying graph for debug purposses
    Graph const graph;

    // Graph with vertices in perfect elimination order
    Graph graph_reordered;


    class GraphIsNotChordal : exception { };

    // Perfect elimination order of graph
    vector<int> perfect_elimination;
    
private:

    vector<int> FindPerfectElimination(Graph const& graph);
    int n;

    using set_timestamp_pair = pair<unordered_set<int>, int>;
    vector<int> perfect_elimination_inv;

    int GetFirst(list< set_timestamp_pair> & sequence);
    bool IsChordal();

    unordered_map<long long,int> results[MAXN];
    unordered_set<int> v[MAXN];
    vector<int> children_tab[MAXN];

    void RecoverResult(int k, int x, int y, unordered_set<int> & result);
    
    int parent[MAXN];
    long long Pack(int a, int b);
    pair<int, int> Unpack(long long val);
};

}