#pragma once

#include "util/util.h"
#include "permutation/util.h"

#include <unordered_set>
#include <unordered_map>

#include <vector>

using namespace std;
using namespace permutation_graphs;

namespace bipartite_permutation {

  class GraphIsNotBipartiteExpcetion : exception { };

  struct BipartiteGraph
  {

    // Generate Bipartite Permutaiton graph, left & right are ordered using Strong Ordering
    // ThrowsGraphIsNotBipartiteExpcetion if graph is not bipartite
    BipartiteGraph(vector<int> const& permutation);

    // Size of minumum FVS
    int FvsCount();

    // Returns minumum FVS
    unordered_set<int> Fvs();

    // Underlying graph for debugging
    Graph const graph;

    // All the data structures as defined in paper
    // indexes of left/right sides
    vector<int> left;
    vector<int> right;

    int n;
    vector<int> isolated;
    vector<unordered_set<int>> edges_map;
    vector<pair<int, int> > edges;
    vector<int> permutation_;

    bool E(int x, int y);

    // As defined in paper
    vector<unordered_map<int, int> > A, B, C, D;
    vector<int> l,r;


    void CalculateLAndR();

    int A2(int i, int j);

    // RecoverResultX(i, j), I am in table X in dynamic programming at position i,j
    // and want to 'go back'
    void RecoverResultA(int i, int j, unordered_set<int> & result);
    void RecoverResultB(int i, int j, unordered_set<int> & result);
    void RecoverResultC(int i, int j, unordered_set<int> & result);
    void RecoverResultD(int i, int j, unordered_set<int> & result);

  };





}