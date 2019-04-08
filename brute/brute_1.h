#pragma once

#include "../util/util.h"

#include <set>
#include <optional>

namespace{

  int BruteFvsRec(Graph const& graph, set<int>& banned)
  {
    vector<int> cycle = util::FindCycle(graph, banned);
    if(cycle.size() == 0)
      return 0;
    
    int best_result = numeric_limits<int>::max();
    for(int x : cycle)
    {
      assert(banned.count(x) == 0);
      banned.insert(x);
      best_result = min(best_result, BruteFvsRec(graph, banned) + 1);
      banned.erase(x);
    }

    return best_result;
  }
}

// Search a cycle, remove one vertex => recursive call
int BruteCycleSearch(Graph const& graph)
{
  set<int> banned;
  return BruteFvsRec(graph, banned);
}

// For each subset of vertices check if it is a proper FVS
int BruteEverySubset(Graph const& graph)
{
  assert(graph.size() <= 20);
  int best_result = graph.size();
  
  for(int i=0; i < (1 << graph.size()); i++)
  {
    set<int> fvs;
    for(int j=0; j < graph.size(); j++)
      if( (i>>j) & 1 )
        fvs.insert(j);
    if(fvs.size() >= best_result)
      continue;
    if(util::IsFvs(graph, fvs))
      best_result = fvs.size();
  }

  return best_result;
}

