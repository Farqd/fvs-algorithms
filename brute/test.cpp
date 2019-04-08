#include "util.h"
#include "brute_1.h"

#include <set>
#include <optional>

namespace {

  void AllGrapshWithSizeRec(Graph const& graph, vector<Graph> & result, int n, int k)
  {
    if(n == k)
    {
      result.push_back(graph);
      return;
    }

    for(int mask=0; mask < (1 << k); mask++)
    {
      Graph new_graph = graph;

      for(int j=0; j < k; j++)
        if( (mask >> j) & 1)
        {
          new_graph[k].push_back(j);
          new_graph[j].push_back(k);
        }

      AllGrapshWithSizeRec(new_graph, result, n, k+1);
    }
  }
}

vector<Graph> AllGrapshWithSize(int n)
{
  vector<Graph> result;
  Graph graph(n);
  AllGrapshWithSizeRec(graph, result, n, 0);
  return result;
}


int main()
{
  auto const& graphs = AllGrapshWithSize(4);
  cerr << "Graphs generated: " << graphs.size() << endl;

  for(auto const& graph : graphs)
    assert(BruteEverySubset(graph) == BruteCycleSearch(graph));
}