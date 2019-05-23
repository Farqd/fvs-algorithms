#include "permutation/permutation.h"
#include "permutation/util.h"
#include "util/util.h"
#include "util/brute.h"

#include <chrono>
#include <vector>

using namespace permutation_graphs;

vector<int> GenRand(int n)
{
    vector<int> result;
    for(int i=0; i<n; i++)
    result.push_back(i);
    random_shuffle(result.begin(), result.end());

    return result;
}


vector<int> GenRandSparse(int n)
{
    vector<int> result;
    for(int i=0; i<n; i++)
    result.push_back(i);
    for(int i=0; i*i < n; i++)
    {
        int x = rand() % n;
        int y = rand() % n;
        swap(result[x], result[y]);
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
    const int N = 1000;

    auto perm = GenRandSparse(N);
        cerr << "N= " << N << endl;
    auto graph_ = PermutationToGraph(perm);
    cerr << "edges= " << edges(graph_) << endl;

    auto start = std::chrono::system_clock::now();

    PermutationGraph gr{perm};
    auto fvs = gr.Fvs();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    cerr <<"FVS= " << fvs.size() << endl;
    assert(util::IsFvs(graph_, fvs));
}
  