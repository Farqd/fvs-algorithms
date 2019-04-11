#include "permutation/permutation.h"
#include "brute/brute.h"

#include "gtest/gtest.h"

using namespace permutation_graphs;

namespace {

TEST(Permutation, Cycle4)
{
  vector<int> permutation {2, 3, 0, 1};
  PermutationGraph gr{permutation};
  EXPECT_EQ(1, gr.FvsCount());
}

TEST(Permutation, TestSize5) 
{
  auto perms = AllPermutations(5);
  for(auto const& x : perms)
  {
    PermutationGraph gr{x};

    // unordered_set<int> fvs = gr.Fvs();
    int r = gr.FvsCount();
    if(brute::EverySubset(gr.graph) != r)
    {
      util::PrintVector(x);
    }

    EXPECT_EQ(brute::EverySubset(gr.graph), r);
    // EXPECT_TRUE(util::IsFvs(gr.graph, fvs));
  }
}

TEST(Permutation, BiggerTest1)
{
  vector<int> v{8, 0, 1, 2, 9, 3, 10, 12, 4, 5, 6, 14, 15, 7, 11, 13};
  PermutationGraph bg {v};
  EXPECT_EQ(4, bg.FvsCount());
  // EXPECT_TRUE(util::IsFvs(bg.graph, bg.Fvs()));
}

TEST(Permutation, BiggerTest2)
{
  vector<int> v{2, 3, 5, 0, 1, 7, 8, 9, 4, 10, 12, 6, 14, 11, 15, 13};
  PermutationGraph bg {v};
  EXPECT_EQ(2, bg.FvsCount());
  // EXPECT_TRUE(util::IsFvs(bg.graph, bg.Fvs()));
}

TEST(Permutation, VeryBigRandomTest)
{
  vector<int> x;
  for(int i=0; i<12; i++)
    x.push_back(i);
  int ix = 0;

  for(int i=0; i<10; i++)
  {
    random_shuffle(x.begin(), x.end());
    PermutationGraph gr{x};
    EXPECT_EQ(brute::EverySubset(gr.graph), gr.FvsCount());
    // EXPECT_TRUE(util::IsFvs(gr.graph, gr.Fvs()));
  }
}

}  // namespace