#include "bipartite_permutation/bipartite_permutation.h"
#include "brute/brute.h"

using namespace bipartite_permutation;

bool cycle3(Graph const& graph)
{
    
    for(int i=0;i<graph.size(); i++)
    for(int x : graph[i])
    for(int y : graph[x])
    for(int z : graph[y])
        if(i == z) return true;
    return false;
}

int main()
{

{
    // vector<int> p {2, 0, 1};
    // vector<int> p {1, 0, 3, 4, 2};
    // vector<int> p {2,4,5,0,6,1,3}; // 2
    vector<int> p {3,4,0,6,1,2,5}; // 2
      BipartiteGraph gr {p};
      int fvs = gr.CalculateFVS();
      int actual_fvs = brute::EverySubset(gr.graph);
    //   cerr << fvs << " " << actual_fvs << endl;
      assert(fvs == actual_fvs);
    //   return 0;
}
    // return 0;
//   auto perms = AllPermutations(11);
//   cerr << perms.size() << endl;

int ix = 0;
vector<int> x;
for(int i=0; i<14; i++)
x.push_back(i);
int ix0 = 0;
//   for(auto const& x : perms)
while(true)
  {
      random_shuffle(x.begin(), x.end());
    try {
      BipartiteGraph gr{x};
        ++ix0;
        if(ix0 == 1000) break;
      int fvs = gr.CalculateFVS();
    //   cerr << fvs << endl;

      int actual_fvs = brute::EverySubset(gr.graph);
    // assert(fvs == actual_fvs);
    cerr << "RESULTS " << actual_fvs << " " << fvs << endl;

      if(actual_fvs != fvs)
      {
            cerr << "PERMUTAION" << endl;
            util::PrintVector(x);

            cerr << "LEFT" << endl;
            util::PrintVector(gr.left);

            cerr << "RIGHT" << endl;
            util::PrintVector(gr.right);

            cerr << "graph" << endl;
            util::PrintGraph(gr.graph);

            throw "AA";
            
      }

    } catch(GraphIsNotBipartiteExpcetion const& exception)
    {
        ++ix;
    //   cerr << "Not BP" << endl;
    }
  }
  cerr << ix0 << " " << ix << endl;
}