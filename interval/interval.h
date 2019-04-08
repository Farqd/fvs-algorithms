#pragma once

#include "../util/util.h"

#include <set>
#include <optional>

/*

  I assume ends of the intervals are unique numbers

*/


namespace interval {

using Interval = pair<int, int>;
using IntervalGraph = vector<Interval>;
struct Endpoint{
  int position;
  int interval;
  bool left;
};

void PrintIG(IntervalGraph const& graph)
{
  cerr << endl;
  for(auto const& x : graph)
    cerr << x.first << " " << x.second << endl;
  cerr << endl;
}

int Fvs(vector<Interval> graph)
{
  auto interval_cmp = [](Interval const& a, Interval const& b){return a.second < b.second; };
  sort(graph.begin(), graph.end(), interval_cmp);

  // PrintIG(graph);

  vector<Endpoint> endpoints;
  for(int i = 0; i < graph.size(); i++)
  {
    Interval const& iv = graph[i];
    endpoints.push_back({iv.first, i, true});
    endpoints.push_back({iv.second, i, false});
  }

  auto endpoint_cmp = [](Endpoint const& a, Endpoint const& b){ return a.position < b.position; };
  sort(endpoints.begin(), endpoints.end(), endpoint_cmp);
  
  int size = 0;
  vector<int> fvs;
  // current intervals
  
  // After each right end at most two intervals can remain, x < y, remember, they interval indexes are sorted by right end
  int x = -1; int y = -1;
  
  for(auto const& e : endpoints)
  {
    if(e.left)
    {
      if(y == -1)
        { y = e.interval; continue; }
      if(x == -1)
        { x = e.interval; if(x > y) swap(x,y); continue; }

      if(e.interval < x)
      {
        fvs.push_back(y);
        y = x;
        x = e.interval;
      } else if(e.interval < y)
      {
        fvs.push_back(y);
        y = e.interval;
      } else
      {
        fvs.push_back(e.interval);
      }
    }
    else // e is right end
    {
      // assert(e.interval == x || (e.interval == y && x == -1) || (x == -1 && y == -1));
      if(x == e.interval)
        x = -1;
      if(y == e.interval)
        y = -1;
      if(x > y)
        swap(x,y);
    }
  }

  return fvs.size();
}

Graph IntervalGraphToGraph(IntervalGraph const& intervals)
{
  Graph graph(intervals.size());

  for(int i = 0; i < intervals.size(); i++)
  for(int j = i + 1; j < intervals.size(); j++)
  {
    auto const& x = intervals[i];
    auto const& y = intervals[j];

    if(x.first > y.second || x.second < y.first) 
      continue;

    graph[i].push_back(j);
    graph[j].push_back(i);
  }

  return graph;
} 


vector<IntervalGraph> GenerateAllGraphs(int size = 6)
{
  vector<IntervalGraph> result;
  vector<int> perm;

  for(int i=0; i<size; i++)
  {
    perm.push_back(i);
    perm.push_back(i);
  }
  
  do {
    IntervalGraph ig(size);
    for(int i = 0; i < size; i++)
      { ig[i].first = -1; ig[i].second = -1; }
    
    for(int i = 0; i < perm.size(); i++)
    {
      if(ig[perm[i]].first == -1)
        ig[perm[i]].first = i;
      else
        ig[perm[i]].second = i;
    }

    result.push_back(ig);

  } while(next_permutation(perm.begin(), perm.end()));

  return result;
}

}