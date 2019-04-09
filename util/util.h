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
  vector<int> FindCycle(Graph const& graph, set<int> const& banned);

  bool IsFvs(Graph const& graph, set<int> const& fvs);

  void PrintGraph(Graph const& graph);

  void PrintVector(vector<int> const& v);
}