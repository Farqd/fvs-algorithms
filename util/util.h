#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <cassert>

using namespace std;

using Graph = vector<vector<int>>;

namespace util
{
  namespace 
  {
    bool FindCycleDfs(int k, int parent, Graph const& graph, set<int> const& banned, vector<bool>& visited, vector<int>& cycle)
    {
      if(visited[k])
      {
        cycle.push_back(k);
        return true;
      }

      visited[k] = true;

      for(int x : graph[k])
      {
        if(banned.count(x) || x == parent)
          continue;
        bool res = FindCycleDfs(x, k, graph, banned, visited, cycle);
        if(res)
        {
          if(k == cycle[0])
            return false;
          cycle.push_back(k);
          return true;
        }
      }
      return false;
    }
  }

  vector<int> FindCycle(Graph const& graph, set<int> const& banned)
  {
    vector<bool> visited(graph.size(), false);
    vector<int> cycle;

    for(int i = 0; i < graph.size(); i++)
    {
      if(!banned.count(i) && !visited[i])
      {
        FindCycleDfs(i, -1, graph, banned, visited, cycle);
        if(cycle.size() > 0)
          return cycle;
      }
    }

    return cycle;
  }

  bool IsFvs(Graph const& graph, set<int> const& fvs)
  {
    vector<int> const& cycle = FindCycle(graph, fvs);
    if(cycle.size() == 0)
      return true;
    return false;
  }

  void PrintGraph(Graph const& graph)
  {
    for(int i=0; i<graph.size(); i++)
    {
      cout << i << ": ";
      for(int x : graph[i])
        cout << x << " ";
      cout << endl;
    }
  }

  void PrintVector(vector<int> const& v)
  {
    for(int x : v)
    cerr << x << " ";
    cerr << endl;
  }
}