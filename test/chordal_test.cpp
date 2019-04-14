#include "chordal/chordal.h"
#include "util/brute.h"

#include "gtest/gtest.h"

using namespace chordal;

namespace {

TEST(ChordalGraph, TestSize5) {

    auto graphs = util::AllGraphs(5);
    for(auto const& g : graphs)
    {
        try 
        {
            ChordalGraph cg {g};
            auto fvs = cg.Fvs();
        
            int correct_size = brute::EverySubset(g);
            EXPECT_TRUE(util::IsFvs(g, fvs));
            EXPECT_EQ(correct_size, fvs.size());
        }
        catch(ChordalGraph::GraphIsNotChordal ignored)
        { }
    }
}

}  // namespace