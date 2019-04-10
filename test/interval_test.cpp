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
    
    EXPECT_EQ(fvs_brute, iv_res);
  }
}

}  // namespace