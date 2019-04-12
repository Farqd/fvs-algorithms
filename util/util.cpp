#include "util.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <cassert>

using namespace std;

namespace 
{
  bool FindCycleDfs(int k, int parent, Graph const& graph,
      unordered_set<int> const& banned, vector<bool>& visited, vector<int>& cycle)
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

vector<int> util::FindCycle(Graph const& graph, unordered_set<int> const& banned)
{
  vector<bool> visited(graph.size(), false);
  vector<int> cycle;

  for(int i = 0; i < (int)graph.size(); i++)
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

bool util::IsFvs(Graph const& graph, unordered_set<int> const& fvs)
{
  vector<int> const& cycle = FindCycle(graph, fvs);
  if(cycle.size() == 0)
    return true;
  return false;
}

void util::PrintGraph(Graph const& graph)
{
  cerr << graph.size() << endl;
  for(int i=0; i< (int)graph.size(); i++)
  {
    cerr << i << ": ";
    for(int x : graph[i])
      cerr << x << " ";
    cerr << endl;
  }
}

void util::PrintVector(vector<int> const& v)
{
  cerr << v.size() << endl;
  for(int x : v)
    cerr << x << " ";
  cerr << endl << endl;
}

vector<Graph> util::AllGraphs(int size)
{

  vector<Graph> result;

  if(size == 1)
  {
    Graph tmp;
    tmp.push_back({});
    result.push_back(tmp);
    return result;    
  }
  
  vector<Graph> smaller_graphs = AllGraphs(size-1);

  for(Graph const& g : smaller_graphs)
  {
    for(int mask = 1; mask < (1 << (size-1)); mask++)
    {
      result.push_back(g);
      auto & last_graph = result.back();
      last_graph.push_back({});
      
      for(int i=0; i<size-1; i++)
      {
        if((mask>>i)&1)
        {
          last_graph[size-1].push_back(i);
          last_graph[i].push_back(size-1);
        }
      }
    }
  }

  return result;
}