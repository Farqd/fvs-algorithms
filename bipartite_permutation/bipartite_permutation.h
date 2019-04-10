#pragma once

#include "util/util.h"
#include "permutation/util.h"

#include <unordered_set>
#include <vector>

using namespace std;
using namespace permutation_graphs;

namespace bipartite_permutation {

  class GraphIsNotBipartiteExpcetion : exception { };

  struct BipartiteGraph
  {
    // indexes of left/right sides
    vector<int> left;
    vector<int> right;

    int n;
    vector<int> isolated;
    Graph const graph;
    vector<unordered_set<int>> edges_map;
    vector<pair<int, int> > edges;
    vector<int> permutation_;

    bool E(int x, int y);

    // Generate Bipartite Permutaiton graph, left & right are ordered using Strong Ordering
    // ThrowsGraphIsNotBipartiteExpcetion if graph is not bipartite
    BipartiteGraph(vector<int> const& permutation);

    // As defined in paper
    vector<vector<int>> A, B, C, D;
    vector<int> l,r;


    void CalculateLAndR();

    int A2(int i, int j);

    int FvsCount();

    unordered_set<int> Fvs();
    void RecoverResultA(int i, int j, unordered_set<int> & result);
    void RecoverResultB(int i, int j, unordered_set<int> & result);
    void RecoverResultC(int i, int j, unordered_set<int> & result);
    void RecoverResultD(int i, int j, unordered_set<int> & result);

  };





}