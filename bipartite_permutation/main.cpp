#include "bipartite_permutation/bipartite_permutation.h"
#include "util/util.h"

using namespace bipartite_permutation;

vector<int> GenerateBipartitePermutation(int n)
{
    vector<int> result;
    
    for(int i=n; i<2*n; i++)
        result.push_back(i);
    for(int i=0; i<n; i++)
    {
        // result.push_back(2*i+1);
        result.push_back(i);
    }
    return result;


}

int main()
{
    vector<int> perm = 
        GenerateBipartitePermutation(2000);
    BipartiteGraph gr {perm};
    cerr << gr.edges.size() << endl;
    cout << gr.FvsCount() << endl;
    assert(util::IsFvs(gr.graph, gr.Fvs()));
}
  