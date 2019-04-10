#include "bipartite_permutation/bipartite_permutation.h"
#include "brute/brute.h"

#include "gtest/gtest.h"

using namespace bipartite_permutation;

namespace {

TEST(BipartitePermutation, Cycle4)
{
  vector<int> permutation {2, 3, 0, 1};
  BipartiteGraph graph {permutation};
  unordered_set<int> fvs = graph.Fvs();
  EXPECT_TRUE(util::IsFvs(graph.graph, fvs));
}

TEST(BipartitePermutation, TestSize5) 
{
  auto perms = AllPermutations(5);
  for(auto const& x : perms)
  {
    try 
    {
      BipartiteGraph gr {x};
      unordered_set<int> fvs = gr.Fvs();
      EXPECT_TRUE(util::IsFvs(gr.graph, fvs));

    } catch(GraphIsNotBipartiteExpcetion const&)
    {  }
  }
}

TEST(BipartitePermutation, BiggerTest1)
{
  vector<int> v{8, 0, 1, 2, 9, 3, 10, 12, 4, 5, 6, 14, 15, 7, 11, 13};
  BipartiteGraph bg {v};
  EXPECT_EQ(4, bg.FvsCount());
  EXPECT_TRUE(util::IsFvs(bg.graph, bg.Fvs()));
}

TEST(BipartitePermutation, BiggerTest2)
{
  vector<int> v{2, 3, 5, 0, 1, 7, 8, 9, 4, 10, 12, 6, 14, 11, 15, 13};
  BipartiteGraph bg {v};
  EXPECT_EQ(2, bg.FvsCount());
  EXPECT_TRUE(util::IsFvs(bg.graph, bg.Fvs()));
}

// TEST(BipartitePermutation, VeryBigRandomTest)
// {
//   vector<int> x;
//   for(int i=0; i<12; i++)
//     x.push_back(i);
//   int ix = 0;

//   while(true)
//   {
//     random_shuffle(x.begin(), x.end());
//     try {
//       BipartiteGraph gr{x};
//       ++ix;
//       if(ix == 10)
//         break;
//       EXPECT_TRUE(util::IsFvs(gr.graph, gr.Fvs()));

//     } catch(GraphIsNotBipartiteExpcetion const& exception)
//     { }
//   }
// }

}  // namespace