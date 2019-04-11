#include "util/util.h"
#include "interval/interval.h"

#include <set>
#include <optional>

/*

  I assume ends of the intervals are unique numbers

*/


namespace interval {

void PrintIG(IntervalGraph const& graph)
{
  cerr << endl;
  for(auto const& x : graph)
    cerr << x.begin << " " << x.end << endl;
  cerr << endl;
}

unordered_set<int> Fvs(vector<Interval> graph)
{
  auto interval_cmp = [](Interval const& a, Interval const& b){return a.end < b.end; };
  sort(graph.begin(), graph.end(), interval_cmp);

  // PrintIG(graph);

  vector<Endpoint> endpoints;
  for(int i = 0; i < (int)graph.size(); i++)
  {
    Interval const& iv = graph[i];
    endpoints.push_back({iv.begin, i, true});
    endpoints.push_back({iv.end, i, false});
  }

  auto endpoint_cmp = [](Endpoint const& a, Endpoint const& b){ return a.position < b.position; };
  sort(endpoints.begin(), endpoints.end(), endpoint_cmp);
  
  unordered_set<int> fvs;
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
        fvs.insert(graph[y].ix);
        y = x;
        x = e.interval;
      } else if(e.interval < y)
      {
        fvs.insert(graph[y].ix);
        y = e.interval;
      } else
      {
        fvs.insert(graph[e.interval].ix);
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

  return fvs;
}

Graph IntervalGraphToGraph(IntervalGraph const& intervals)
{
  Graph graph(intervals.size());

  for(int i = 0; i < (int)intervals.size(); i++)
  for(int j = i + 1; j < (int)intervals.size(); j++)
  {
    auto const& x = intervals[i];
    auto const& y = intervals[j];

    if(x.begin > y.end || x.end < y.begin) 
      continue;

    graph[i].push_back(j);
    graph[j].push_back(i);
  }

  return graph;
} 

vector<IntervalGraph> GenerateAllGraphs(int size)
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
      { ig[i].begin = -1; ig[i].end = -1; ig[i].ix = i; }
    
    for(int i = 0; i < (int)perm.size(); i++)
    {
      if(ig[perm[i]].begin == -1)
        ig[perm[i]].begin = i;
      else
        ig[perm[i]].end = i;
    }

    result.push_back(ig);

  } while(next_permutation(perm.begin(), perm.end()));

  return result;
}

}