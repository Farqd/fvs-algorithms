#pragma once

#include "../util/util.h"

#include <vector>
#include <algorithm>


using namespace std;

// Assuming permutations are from 0 to n-1

namespace permutation_graphs {

  vector<vector<int>> AllPermutations(int size);

  Graph PermutationToGraph(vector<int> const& permutation);

  // Return all edges. Works in O(N*log(N) + E)
  vector<pair<int, int> > CalculateEdges(vector<int> permutation);

  // Return inverse permutation
  vector<int> InversePermutation(vector<int> const& permutation);
}