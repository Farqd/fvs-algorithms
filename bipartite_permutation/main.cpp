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
    for(int N = 1000; N<=20000; N+=1000)
    {

        vector<pair<double,int>> v;
        for(int i=0; i<10; i++)
        {
            auto perm = GenRand(N);

            auto graph_ = PermutationToGraph(perm);
            // egde += edges(graph_);

            auto start = std::chrono::system_clock::now();

            BipartiteGraph gr {perm};
            auto fvs = gr.Fvs();

            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            // std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        
            // std::cout << "finished computation at " << std::ctime(&end_time)
            //           << "elapsed time: " << elapsed_seconds.count() << "s\n";
            // cerr <<"FVS= " << fvs.size() << endl;
            // time_ += elapsed_seconds.count();
            v.push_back({elapsed_seconds.count(), edges(graph_)});
            // cerr << edge << " " << N  << " " << elapsed_seconds.count() << endl;
            assert(util::IsFvs(graph_, fvs));
        }
        int egde = 0;
        double time_ = 0;
        sort(v.begin(), v.end());
        for(int i=3; i<7; i++)
        {
            egde += v[i].second;
            time_ += v[i].first;
        }
        cout << egde/4 << " " << N << " " << time_/4 << endl;
    }
}
  