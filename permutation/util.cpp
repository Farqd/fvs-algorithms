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

  result.resize(permutation.size());
  auto const& edges = permutation_graphs::CalculateEdges(permutation);

  for(auto const& p : edges)
    result[p.first].push_back(p.second);

  return result;
}

namespace
{
  void MergeSort(vector<int> & tab, int beg, int end, vector<pair<int, int> > & edges)
  {
    if(beg + 1 == end)
      return;
    int mid = (beg + end) / 2;
    MergeSort(tab, beg, mid, edges);
    MergeSort(tab, mid, end, edges);

    vector<int> tmp;
    int l = beg;
    int r = mid;

    while(l < mid && r < end)
    {
      if(tab[l] < tab[r])
      {
        tmp.push_back(tab[l++]);
      } else
      {
        for(int k = l; k < mid; k++)
        {
          edges.push_back({tab[r], tab[k]});
          edges.push_back({tab[k], tab[r]});
        }

        tmp.push_back(tab[r++]);
      }
      
    }

    while(l < mid)
      tmp.push_back(tab[l++]);
    while(r < end)
      tmp.push_back(tab[r++]);

    for(int i=0; i<(int)tmp.size(); i++)
      tab[beg+i] = tmp[i];
  }
}

vector<pair<int, int> > permutation_graphs::CalculateEdges(vector<int> permutation)
{
  vector<pair<int, int> > result;

  MergeSort(permutation, 0, permutation.size(), result);

  return result;
}

vector<int> permutation_graphs::InversePermutation(vector<int> const& permutation)
{
    vector<int> result;
    result.resize(permutation.size());

    for(unsigned i=0; i<permutation.size(); i++)
      result[permutation[i]] = i;

    return result;
}