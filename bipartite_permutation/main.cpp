#include "bipartite_permutation/bipartite_permutation.h"
#include "util/util.h"
#include <chrono>

using namespace bipartite_permutation;

vector<int> GenRand(int n)
{
    vector<int> result;
    vector<int> l,r;

    for(int i=0; i<n; i++)
    {
        if(rand()%2) 
            l.push_back(i); 
        else 
            r.push_back(i);
    }

    int i=0; int j=0; 
    while(i < l.size() && j < r.size())
    {
        if(rand()%2)
            result.push_back(l[i++]);
        else
            result.push_back(r[j++]);
    }
    while(i < l.size()) result.push_back(l[i++]);
    while(j < r.size()) result.push_back(r[j++]);

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
    const int N = 300;

    auto perm = GenRand(N);

    cerr << "N= " << N << endl;
    auto graph_ = PermutationToGraph(perm);
    cerr << "edges= " << edges(graph_) << endl;

    auto start = std::chrono::system_clock::now();

    BipartiteGraph gr {perm};
    auto fvs = gr.Fvs();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    cerr <<"FVS= " << fvs.size() << endl;
    assert(util::IsFvs(graph_, fvs));
}
  