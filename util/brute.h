#pragma once

#include "util/util.h"

#include <set>
#include <optional>

namespace brute {
  // Returns minimum FVS
  // Search a cycle, remove one vertex => recursive call
  int CycleSearch(Graph const& graph);

  // Returns minumum FVS
  // For each subset of vertices check if it is a proper FVS
  int EverySubset(Graph const& graph);
}