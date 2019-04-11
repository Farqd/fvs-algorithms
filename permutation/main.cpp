#include "permutation/permutation.h"
#include "permutation/util.h"
#include "util/util.h"
#include "brute/brute.h"

#include <vector>

using namespace permutation_graphs;


int main()
{
    // vector<int> perm {1, 7, 5, 2, 0, 6, 3, 4};
    // vector<int> perm{5,4,3,2,1,0};
    vector<int> perm{8, 0, 1, 2, 9, 3, 10, 12, 4, 5, 6, 14, 15, 7, 11, 13};
    // vector<int> perm{2,3,0,1};
    // vector<int> perm{0,1,2,3,4, 5, 6, 7, 8, 9, 10, 11, 12};
    // auto perms = AllPermutations(6);
    // int ix = 0;
    // while(true)
    // for(auto const& perm : perms)
    {
        
        PermutationGraph gr{perm};

        auto r = gr.Fvs();
        
        int e = brute::EverySubset(gr.graph);
        cerr << r.size() << " " << e << endl;
        assert(r.size() == e);
        assert(util::IsFvs(gr.graph, r));
    }

    // // vector<int> v;
    // PermutationGraph gr{perm};

    // int r = gr.FvsCount();
    // int e = brute::EverySubset(gr.graph);
    // cerr << "RESULT: " << r << " EXPECTED: " << e << endl;
    // assert(util::IsFvs(gr.graph, gr.Fvs()));
}
  