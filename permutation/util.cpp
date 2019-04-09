#include "util/util.h"
#include "permutation/util.h"

#include <vector>
#include <algorithm>

using namespace std;

// Assuming permutations are from 0 to n-1

vector<vector<int>> permutation_graphs::AllPermutations(int size)
{
  vector<vector<int>> result;
  vector<int> permutation;

  for(int i=0; i<size; i++)
    permutation.push_back(i);

  do {
    result.push_back(permutation);
  } while(next_permutation(permutation.begin(), permutation.end()));

  return result;
}

Graph permutation_graphs::PermutationToGraph(vector<int> const& permutation)
{
  Graph result;

  int const n = permutation.size();
  result.resize(n);

  for(int i = 0; i < n; i++)
  for(int j = i+1; j < n; j++)
  {
    if(permutation[i] > permutation[j])
    {
      result[permutation[i]].push_back(permutation[j]);
      result[permutation[j]].push_back(permutation[i]);
    }
  }

  return result;
}
