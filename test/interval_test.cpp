#include "interval/interval.h"
#include "brute/brute.h"

#include "gtest/gtest.h"

namespace {

TEST(IntervalTest, TestSize5) {

  auto graphs = interval::GenerateAllGraphs(5);
    
  for(auto const& ivGraph : graphs)
  {    
    int iv_res = interval::Fvs(ivGraph);
    auto const& graph = interval::IntervalGraphToGraph(ivGraph);
    int fvs_brute = brute::CycleSearch(graph);
    
    // cerr << iv_res << " " << fvs_brute << endl;
    EXPECT_EQ(fvs_brute, iv_res);
  }
}

}  // namespace

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?