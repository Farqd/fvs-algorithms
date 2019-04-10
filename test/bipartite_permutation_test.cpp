#include "bipartite_permutation/bipartite_permutation.h"
#include "brute/brute.h"

#include "gtest/gtest.h"

using namespace bipartite_permutation;

namespace {


TEST(BipartitePermutation, Cycle4)
{
  vector<int> permutation {2, 3, 0, 1};
  BipartiteGraph graph {permutation};
  EXPECT_EQ(1, graph.CalculateFVS());
}

TEST(BipartitePermutation, TestSize5) 
{
  auto perms = AllPermutations(5);
  for(auto const& x : perms)
  {
    try {
      BipartiteGraph gr {x};
      int fvs = gr.CalculateFVS();
      cerr << fvs << endl;

            cerr << "PERMUTAION" << endl;
            util::PrintVector(x);

      int actual_fvs = brute::EverySubset(gr.graph);
      EXPECT_EQ(actual_fvs, fvs);

      if(actual_fvs != fvs)
      {
            cerr << "PERMUTAION" << endl;
            util::PrintVector(x);

            cerr << "LEFT" << endl;
            util::PrintVector(gr.left);

            cerr << "RIGHT" << endl;
            util::PrintVector(gr.right);

            cerr << "graph" << endl;
            util::PrintGraph(gr.graph);

            throw "AAA";
            
      }

    } catch(GraphIsNotBipartiteExpcetion const& exception)
    {
      cerr << "Not BP" << endl;
    }
  }
}

}  // namespace