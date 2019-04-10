#include "../util/util.h"
#include "../brute/brute_1.h"
#include "../permutation/util.h"
#include "bipartite_permutation.h"

#include <set>
#include <optional>

using namespace bipartite_permutation;

int main()
{

  vector<int> v{2,3,0,1};
  // vector<int> v{2,3,0,1, 6,7,4,5};
  // vector<int> v{2,3,4,5,6,7,0,1};

  // auto perms = AllPermutations(5);
  for(auto const& x : perms)
  {
    try {
      BipartiteGraph gr {x};
      cerr << gr.CalculateFVS() << endl;
    } catch(GraphIsNotBipartiteExpcetion const& exception)
    {
      cerr << "Not BP" << endl;
    }
  }
}
