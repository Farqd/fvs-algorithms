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

    ChordalGraph(Graph const& graph);

    int FvsCount();

    unordered_set<int> Fvs();

    vector<int> FindPerfectElimination(Graph const& graph);

    Graph const graph;
    Graph graph_reordered;

    int n;

    class GraphIsNotChordal : exception { };

    vector<int> perfect_elimination;
private:

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