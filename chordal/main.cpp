#include "chordal/chordal.h"
#include "util/util.h"
#include "brute/brute.h"

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
            continue;
            // // cerr << fvs.size()<<endl;

            // if(!util::IsFvs(g, fvs))
            // {
            //     cerr << "FVS"<<endl;
            //     for(int x : fvs)
            //     cerr << x << " ";
            //     cerr<<endl;
            //     throw "";
            // }   
            // int corr = brute::EverySubset(g);
            // if(corr != fvs.size())
            // {
            //     util::PrintGraph(g);
            //     cerr << endl;
            //     util::PrintVector(cg.perfect_elimination);
            //     cerr << endl;
            //     cerr << corr << " " << fvs.size() << endl;
                
            //     cerr << "FVS"<<endl;
            //     for(int x : fvs)
            //     cerr << x << " ";
            //     cerr<<endl;

            // }
            // assert(corr == fvs.size());
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
    cerr << cg.FvsCount() << endl;
    cerr << brute::EverySubset(graph) << endl;
    return 0;
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