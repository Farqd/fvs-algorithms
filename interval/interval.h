#pragma once

#include "util/util.h"

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

void PrintIG(IntervalGraph const& graph);

int Fvs(vector<Interval> graph);

Graph IntervalGraphToGraph(IntervalGraph const& intervals);

vector<IntervalGraph> GenerateAllGraphs(int size = 6);

}