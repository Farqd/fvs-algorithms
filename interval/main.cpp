#include "../util/util.h"
#include "../brute/brute_1.h"
#include "interval.h"

#include <set>
#include <optional>
#include <cassert>


int main()
{
  auto graphs = interval::GenerateAllGraphs(5);
  
  cerr << "Generating finihsed: " << graphs.size() << endl;
  
  for(auto const& ivGraph : graphs)
  {    
    int iv_res = interval::Fvs(ivGraph);
    auto const& graph = interval::IntervalGraphToGraph(ivGraph);
    int fvs_brute = BruteCycleSearch(graph);
    
    // cerr << iv_res << " " << fvs_brute << endl;
    assert(iv_res == fvs_brute);
  }
}
