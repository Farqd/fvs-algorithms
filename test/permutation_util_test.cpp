#include "permutation/util.h"

#include "gtest/gtest.h"

using namespace permutation_graphs;

namespace {

vector<pair<int, int> > GenerateEdgesSlow(vector<int> const& permutation)
{
  vector<pair<int, int> > result;

  int n = permutation.size();

  for(int i = 0; i < n; i++)
  for(int j = i+1; j < n; j++)
  {
    if(permutation[i] > permutation[j])
    {
      result.push_back({permutation[i], permutation[j]});
      result.push_back({permutation[j], permutation[i]});
    }
  }
  return result;
}


TEST(PermutationUtil, GenerateEdges)
{
  vector<int> v{2,3,0,1};
  auto const& edges = CalculateEdges(v);
  EXPECT_EQ(8, edges.size());
}

TEST(PermutationUtil, RandomPerms)
{
  vector<int> perm;
  for(int i=0; i<50; i++)
    perm.push_back(i);
  for(int i=0; i<100; i++)
  {
    random_shuffle(perm.begin(), perm.end());

    auto expected = GenerateEdgesSlow(perm);
    auto result = CalculateEdges(perm);

    sort(expected.begin(), expected.end());
    sort(result.begin(), result.end());
    EXPECT_EQ(expected, result);
  }
}

}  // namespace