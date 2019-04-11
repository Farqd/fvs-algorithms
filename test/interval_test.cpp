#include "interval/interval.h"
#include "brute/brute.h"

#include "gtest/gtest.h"

using namespace interval;

namespace {

TEST(IntervalTest, TestSize5) {

  auto graphs = interval::GenerateAllGraphs(5);
    
  for(auto const& ivGraph : graphs)
  {    
    unordered_set<int> fvs = Fvs(ivGraph);
    auto const& graph = IntervalGraphToGraph(ivGraph);
    int fvs_brute = brute::EverySubset(graph);
    
    EXPECT_TRUE(util::IsFvs(IntervalGraphToGraph(ivGraph), fvs));
    EXPECT_EQ(fvs_brute, fvs.size());
  }
}

IntervalGraph GenerateIG(int n)
{
  vector<int> v;
  for(int i=0; i<2*n; i++)
    v.push_back(i);
  random_shuffle(v.begin(), v.end());

  IntervalGraph result;
  for(int i=0; i<n; i++)
  {
    int x = v[2*i]; int y = v[2*i+1];
    if(x > y) swap(x, y);
    result.push_back({x, y, i});
  }
  return result;
}

TEST(IntervalTest, RandomBigTest) {

  for(int i=0; i<5; i++)
  {
    auto graph = GenerateIG(50);
    unordered_set <int> fvs = Fvs(graph);
    EXPECT_TRUE(util::IsFvs(IntervalGraphToGraph(graph), fvs));
    auto g = IntervalGraphToGraph(graph);
    
    if(fvs.size() > 0)
    {
      fvs.erase(fvs.begin());
      EXPECT_FALSE(util::IsFvs(IntervalGraphToGraph(graph), fvs));
    }
  }
}

}  // namespace