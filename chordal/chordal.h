#pragma once

#include "util/util.h"

#include <unordered_set>
#include <set>

#include <list>
#include <unordered_map>

using namespace std;

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

    unordered_map<int,int> results[10000];
    
    unordered_set<int> v[10000];
    unordered_set<int> v_not_in_parent[10000];
    vector<int> children_tab[10000];

    void RecoverResult(int k, int x, int y, unordered_set<int> & result);
    
    int parent[10000];
    

};

}