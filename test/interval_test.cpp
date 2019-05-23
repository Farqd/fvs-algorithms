#include "interval/interval.h"
#include "util/brute.h"

#include "gtest/gtest.h"

using namespace interval;

namespace {

TEST(IntervalTest, TestSize5) {

  auto graphs = interval::GenerateAllGraphs(5);
    
  for(auto const& ivGraph : graphs)
  {    
    vector<int> fvs = Fvs(ivGraph);
    auto const& graph = IntervalGraphToGraph(ivGraph);
    int fvs_brute = brute::EverySubset(graph);
    
    unordered_set<int> fvs_set;
    for(int x : fvs) fvs_set.insert(x);
    EXPECT_EQ(fvs_set.size(), fvs.size());
    EXPECT_TRUE(util::IsFvs(IntervalGraphToGraph(ivGraph), fvs_set));
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
    vector <int> fvs = Fvs(graph);
    unordered_set<int> fvs_set;
    for(int x : fvs) fvs_set.insert(x);
    EXPECT_EQ(fvs_set.size(), fvs.size());

    EXPECT_TRUE(util::IsFvs(IntervalGraphToGraph(graph), fvs_set));
    auto g = IntervalGraphToGraph(graph);
    
    if(fvs.size() > 0)
    {
      fvs_set.erase(*fvs.begin());
      EXPECT_FALSE(util::IsFvs(IntervalGraphToGraph(graph), fvs_set));
    }
  }
}

}  // namespace