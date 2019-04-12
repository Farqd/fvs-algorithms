#include "chordal/chordal.h"
#include "util/util.h"
#include "brute/brute.h"

using namespace chordal;


int main()
{
    auto graphs = util::AllGraphs(4);
    cerr << graphs.size() << endl;

    for(auto const& g : graphs)
    {
        try{
        ChordalGraph cg {g};
            auto fvs = cg.Fvs();
            // cerr << fvs.size()<<endl;
            if(!util::IsFvs(g, fvs))
            {
                util::PrintGraph(g);
                cerr << endl;
                util::PrintVector(cg.perfect_elimination);
                cerr << "FVS"<<endl;
                for(int x : fvs)
                cerr << x << " ";
                cerr<<endl;
                throw "";
            }   
            int corr = brute::EverySubset(g);
            if(corr != fvs.size())
            {
                util::PrintGraph(g);
                cerr << endl;
                util::PrintVector(cg.perfect_elimination);
                cerr << endl;
                cerr << corr << " " << fvs.size() << endl;
                
                cerr << "FVS"<<endl;
                for(int x : fvs)
                cerr << x << " ";
                cerr<<endl;

            }
            assert(corr == fvs.size());
        } catch(ChordalGraph::GraphIsNotChordal e)
        {
            // util::PrintGraph(g);

        }
    }
    return 0;
    Graph graph;
    graph.resize(8);
    graph[0] = {1,2};
    graph[1] = {0,2};
    graph[2] = {0,1,6,7};
    graph[3] = {5,6};
    graph[4] = {5,7};
    graph[5] = {3,4,6,7};
    graph[6] = {2,3,5,7};
    graph[7] = {2,4,5,6};
    
    
    ChordalGraph cg {graph};
    auto elim = cg.FindPerfectElimination(graph);

    for(int x : elim)
    cerr << x << " ";
    cerr<<endl;

    auto fvs = cg.Fvs();
    for(int x : fvs)
    cerr << x << " ";
    cerr<<endl;

    assert(util::IsFvs(cg.graph, fvs));



}