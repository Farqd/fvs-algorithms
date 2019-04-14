#include "bipartite_permutation/bipartite_permutation.h"
#include "util/brute.h"

using namespace bipartite_permutation;

bool cycle3(Graph const& graph)
{
    
    for(int i=0;i< (int)graph.size(); i++)
    for(int x : graph[i])
    for(int y : graph[x])
    for(int z : graph[y])
        if(i == z) return true;
    return false;
}

int main()
{
{
    // // vector<int> p {2, 0, 1};
    // vector<int> p {2, 3, 0, 1};
    // // vector<int> p {1, 0, 3, 4, 2};
    // // vector<int> p {2,4,5,0,6,1,3}; // 2
    // // vector<int> p {3,4,0,6,1,2,5}; // 2
    // //   vector<int> p{8, 0, 1, 2, 9, 3, 10, 12, 4, 5, 6, 14, 15, 7, 11, 13};

    //   BipartiteGraph gr {p};
    //   int fvs = gr.FvsCount();
    //   unordered_set<int> F = gr.Fvs();
    //   for(int x : F) cerr << x << " ";
    //   cerr << endl;
    //   assert(util::IsFvs(gr.graph, F));
    //   int actual_fvs = brute::EverySubset(gr.graph);
    // //   cerr << fvs << " " << actual_fvs << endl;
    //   assert(fvs == actual_fvs);
    //   return 0;
}
    // return 0;
//   auto perms = AllPermutations(12);
//   cerr << perms.size() << endl;

// int ix = 0;
vector<int> x;
for(int i=0; i<16; i++)
x.push_back(i);
// int ix0 = 0;

//   for(auto const& x : perms)
while(true)
  {
      random_shuffle(x.begin(), x.end());
    try {
      BipartiteGraph gr{x};
       
    //    cerr << "permutation" << endl;
    //    for(int y : x)
    //    cerr << y <<" ";
    //    cerr << endl;

      auto F = gr.Fvs();
        cerr << "A " << gr.FvsCount();
      if(!util::IsFvs(gr.graph, F))
      {
          util::PrintGraph(gr.graph);
          cerr << endl;
          util::PrintVector(x);
          cerr << endl;

          for(int x : F)
          cerr << x << " ";
          cerr << endl;
          throw("AAAA");
      }

    } catch(GraphIsNotBipartiteExpcetion const& exception)
    { }
  }
}