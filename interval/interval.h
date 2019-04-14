#pragma once

#include "util/util.h"

#include <set>
#include <optional>

/*

  I assume ends of the intervals are unique numbers

*/


namespace interval {

struct Interval
{
  int begin;
  int end;
  int ix;
};


// I represent Interval Graph as a list of intervals
using IntervalGraph = vector<Interval>;


// Returns minimum FVS
unordered_set<int> Fvs(vector<Interval> graph);


// Creates list of edges for IntervalGraph used for testing and debugging 
Graph IntervalGraphToGraph(IntervalGraph const& intervals);

vector<IntervalGraph> GenerateAllGraphs(int size = 6);

void PrintIG(IntervalGraph const& graph);

}