#include "bipartite_permutation/bipartite_permutation.h"
#include "brute/brute.h"

#include "gtest/gtest.h"

using namespace bipartite_permutation;

namespace {

TEST(BipartitePermutation, TestSize5) {

  auto perms = AllPermutations(5);
  for(auto const& x : perms)
  {
    try {
      BipartiteGraph gr {x};
      cerr << gr.CalculateFVS() << endl;
    } catch(GraphIsNotBipartiteExpcetion const& exception)
    {
      cerr << "Not BP" << endl;
    }
  }
}

}  // namespace