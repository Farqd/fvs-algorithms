#include "permutation/permutation.h"
#include "permutation/util.h"
#include "util/util.h"

#include <vector>

using namespace permutation_graphs;


int main()
{
    vector<int> perm {1, 7, 5, 2, 0, 6, 3, 4};
    // vector<int> v;
    PermutationGraph gr{perm};

    cerr << gr.FvsCount() << endl;
    // assert(util::IsFvs(gr.graph, gr.Fvs()));
}
  