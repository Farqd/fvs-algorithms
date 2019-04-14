#include "interval/interval.h"
#include "util/brute.h"

#include "gtest/gtest.h"

#include <set>
#include <optional>

using namespace util;


namespace {

TEST(BruteTest, TestSize5) {
    auto graphs = AllGraphs(5);
    for(auto const& graph : graphs)
        EXPECT_EQ(brute::EverySubset(graph), brute::CycleSearch(graph));
}


}  // namespace
