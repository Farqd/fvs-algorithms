#pragma once

#include "../util/util.h"

#include <vector>
#include <algorithm>


using namespace std;

// Assuming permutations are from 0 to n-1

namespace permutation_graphs {

  vector<vector<int>> AllPermutations(int size);

  Graph PermutationToGraph(vector<int> const& permutation);

}