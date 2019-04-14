#include "chordal/chordal.h"
#include "util/util.h"
#include "util/brute.h"

using namespace chordal;


int main()
{
    auto graphs = util::AllGraphs(7);
    cerr << graphs.size() << endl;
int ix = 0;
    for(auto const& g : graphs)
    {
        try{
        ChordalGraph cg {g};
        ++ix;
        if(ix % 100 ==0) cerr << "ct: " << ix << endl;
            auto fvs = cg.Fvs();
        
            int correct = brute::EverySubset(g);
            assert(util::IsFvs(g, fvs));
            if(fvs.size() != correct)
            {
                cerr << "ME: " << fvs.size() << " expected: " << correct << endl << endl;
                cerr << "FVS ";
                for(int x : fvs)
                cerr << x << " ";
                cerr << endl;
                util::PrintGraph(g);
                cerr << endl;
                util::PrintVector(cg.perfect_elimination);
                throw "";
            }
        } catch(ChordalGraph::GraphIsNotChordal e)
        {
            // util::PrintGraph(g);

        }
    }

}