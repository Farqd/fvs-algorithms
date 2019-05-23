#include "chordal/chordal.h"
#include "util/util.h"
#include "util/brute.h"
#include <chrono>

using namespace chordal;

Graph generateChordal(int n)
{
    Graph result;
    result.resize(n);

    int k = 0;
    while(true)
    {
        if(k == n) break;
        int next_clique =  (rand() % min(100, n-k)) + 1;
        
        for(int i=k; i <k+next_clique; i++)
        for(int j=i+1; j <k+next_clique; j++)
        {
            result[i].push_back(j);
            result[j].push_back(i);
        }

        if(k!=0)
        {
            int tmp = rand() % k;
            result[k].push_back(tmp);
            result[tmp].push_back(k);
        }

        k += next_clique;
    }

    return result;
}

int edges(Graph const& g)
{
    int result = 0;
    for(auto const& x : g)
        result += x.size();
    return result;
}

int main()
{
    srand(time(0));
    const int N = 10000;
    auto graph = generateChordal(N);

    cerr << "N= " << N << endl;
    cerr << "edges= " << edges(graph) << endl;

    auto start = std::chrono::system_clock::now();
    ChordalGraph cg {graph};
            
    auto fvs = cg.Fvs();
    auto end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    cerr <<"FVS= " << fvs.size() << endl;
    assert(util::IsFvs(graph, fvs));


}