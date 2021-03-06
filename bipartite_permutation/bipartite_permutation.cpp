#include "util/util.h"
#include "permutation/util.h"

#include "bipartite_permutation/bipartite_permutation.h"

#include <unordered_map>

using namespace std;
using namespace permutation_graphs;

namespace bipartite_permutation {

  namespace 
  {
    void Dfs(Graph const& graph, vector<int> &side, int vertex)
    {
      for(int x : graph[vertex])
      {
        if(side[x] == 0)
        {
          side[x] = side[vertex] ^ 3;
          Dfs(graph, side, vertex);
        }
        
        if(side[x] != (side[vertex] ^ 3))
        {
          throw GraphIsNotBipartiteExpcetion(); 
        }
      }
    }


   pair<vector<int>, vector<int>> BipartiteDivide(Graph const& graph)
    {
      pair<vector<int>, vector<int>> result;

      // 0 -> none, 1 -> left, 2 -> right
      vector<int> side (graph.size());

      for(unsigned i=0; i <graph.size(); i++)
      {
        if(side[i] == 0)
        {
          side[i] = 1;
          Dfs(graph, side, i);
        }
      }

      for(unsigned i = 0; i < graph.size(); i++)
        for(int x : graph[i])
          if( (side[i] ^ 3) != side[x])
            throw GraphIsNotBipartiteExpcetion(); 

      for(int i=0; i< (int)graph.size(); i++)
        if(side[i] == 1)
          result.first.push_back(i);
        else
          result.second.push_back(i);

      return result;
    }
  }

    // Generate Bipartite Permutaiton graph, left & right are ordered using Strong Ordering
  BipartiteGraph::BipartiteGraph(vector<int> const& permutation) 
  : graph(PermutationToGraph(permutation))
  {      
    // Save for debug
    permutation_ = permutation;

    pair<vector<int>, vector<int>> sides = BipartiteDivide(graph);
    
    left.push_back(-1);
    right.push_back(-1);

    n = graph.size();

    edges_map.resize(n);
    for(int i=0; i<n; i++)
      for(int x : graph[i])
        edges_map[i].insert(x);

    for(int x : sides.first)
      if(edges_map[x].size() > 0)
        left.push_back(x);
      else
        isolated.push_back(x);
      
    for(int x : sides.second)
      if(edges_map[x].size() > 0)
        right.push_back(x);
      else
        isolated.push_back(x);

    vector<vector<pair<int, int> > > count_sort_tab;
    count_sort_tab.resize(n+2);

    unordered_map<int, pair<int, bool> > vertex_position;

    for(int i=1; i < left.size(); i++)
      vertex_position[left[i]] = {i, true};
    for(int i=1; i < right.size(); i++)
      vertex_position[right[i]] = {i, false};
    

    for(int i=0; i<n; i++)
    {
      auto p = vertex_position[i];
      if(!p.second)
        continue;

      for(int x : graph[i])
      {
        auto p2 = vertex_position[x];
        if(p2.second)
          continue;
        
        count_sort_tab[p.first + p2.first].push_back({p.first, p2.first});
      }
    }

    for(int i=0; i<n+2; i++)
    {
      for(auto const& p : count_sort_tab[i])
        edges.push_back(p);
    }

  }

  bool BipartiteGraph::E(int x, int y)
  {
    if(x < 0 || x > n)
      return false;
    return edges_map[x].count(y);
  }


  void BipartiteGraph::CalculateLAndR()
  {
    // l -> minimum index of adjacent vertex
    // r -> maximum index of adjacent vertex

    l.resize(n, numeric_limits<int>::max());
    r.resize(n, 0);
    
    for(auto const& edge : edges)
    {
      int i = edge.first;
      int j = edge.second;

      {
        l[left[i]] = min(l[left[i]], j);
        l[right[j]] = min(l[right[j]], i);

        r[left[i]] = max(r[left[i]], j);
        r[right[j]] = max(r[right[j]], i);
      }
    }

  }

  int BipartiteGraph::A2(int i, int j)
  {
    if(i==0 && j==0)
      return 0;
    if(i == 0)
      return j;
    if(j == 0)
      return i;
    if(E(left[i], right[j]))
      return A[i][j];

    if(r[left[i]] < j)
      return A[i][r[left[i]]] + j - (r[left[i]] + 1) + 1;
    if(r[right[j]] < i)
      return A[r[right[j]]][j] + i - (r[right[j]]+1) + 1;
    

    assert(false);
  }

  int BipartiteGraph::FvsCount()
  {
    int l_size = left.size();
    A.resize(l_size);
    B.resize(l_size);
    C.resize(l_size);
    D.resize(l_size);

    CalculateLAndR();

    // we want to calculate dp in order where (x, y) is calculated before (x2, y2) if x + y < x2 + y2
    for(auto const& edge : edges)
    {
      int i = edge.first;
      int j = edge.second;
      
      int i1 = i - 1;
      int j1 = j - 1;

      int i2 = l[right[j]] - 1;
      int j2 = l[left[i]] - 1;
      // C

      if(i1 <= l[right[j]])
        C[i][j] = A2(i1, j2) + 2;
      else if(! E(left[i1], right[j2] ))
        C[i][j] = C[i1][j] + 1;
      else 
      {
        int tmp = max( { A2(i2,j2) + 2, C[i1][j] + 1, D[i1][j2] + 2 } );
        if(E(left[i2], right[j2]) && l[left[i1]] == j2)
          C[i][j] = max(tmp, B[i2][j2] + 3);
        else
          C[i][j] = tmp;
      }

      // D

      if(j1 <= l[left[i]])
        D[i][j] = A2(i2,j1) + 2;
      else if(!E(left[i2], right[j1]))
        D[i][j] = D[i][j1] + 1;
      else 
      {
        int tmp = max({ A2(i2, j2) + 2, D[i][j1] + 1, C[i2][j1] + 2  });
        if(E(left[i2], right[j2]) && l[right[j1]] == i2)
          D[i][j] = max(tmp, B[i2][j2] + 3);
        else
          D[i][j] = tmp;
      }

      B[i][j] = max(C[i][j], D[i][j]);
      A[i][j] = max({ A2(i1, j), A2(i, j1), B[i][j]  });

    }

    return n - A[left.size()-1][right.size()-1] - isolated.size();
  }


  void BipartiteGraph::RecoverResultA(int i, int j, unordered_set<int> & result)
  {
    
    auto lamAddRight = [&](int beg) {
      for(int k = beg; k <= j; k++)
        result.insert(right[k]);
    };

    auto lamAddLeft = [&](int beg) {
      for(int k = beg; k <= i; k++)
        result.insert(left[k]);
    };

    if(i == 0)
    {
      lamAddRight(1);
      return;
    }

    if(j == 0)
    {
      lamAddLeft(1);
      return;
    }
    // A2
    if(!E(left[i], right[j]))
    {
      if(r[left[i]] < j)
      {
        lamAddRight(r[left[i]]+1);
        return RecoverResultA(i, r[left[i]], result);
      }

      assert(r[right[j]] < i);
      lamAddLeft(r[right[j]]+1);
      return RecoverResultA(r[right[j]], j, result);
    }

    // Case when {i, j} is an edge

    if(A[i][j] == B[i][j])
      return RecoverResultB(i, j, result);
    if(A[i][j] == A2(i-1, j))
      return RecoverResultA(i-1, j, result);
    if(A[i][j] == A2(i, j-1))
      return RecoverResultA(i, j-1, result);

    assert(false);
  }

  void BipartiteGraph::RecoverResultB(int i, int j, unordered_set<int> & result)
  {
    if(B[i][j] == C[i][j])
      return RecoverResultC(i, j, result);
    if(B[i][j] == D[i][j])
      return RecoverResultD(i, j, result);

    assert(false);
  }

  void BipartiteGraph::RecoverResultC(int i, int j, unordered_set<int> & result)
  {
    int i1 = i - 1;
    int i2 = l[right[j]] - 1;
    int j2 = l[left[i]] - 1;

    result.insert(left[i]);

    if(i1 <= l[right[j]])
    {
      result.insert(right[j]);
      return RecoverResultA(i1, j2, result);
    }
    else if(! E(left[i1], right[j2] ))
    {
      return RecoverResultC(i1, j, result);
    }
    else 
    {
      int res = C[i][j];
      if(res == A2(i2, j2) + 2)
      {
        result.insert(right[j]);
        return RecoverResultA(i2, j2, result);
      }

      if(res == C[i1][j] + 1)
      {
        return RecoverResultC(i1, j, result);
      }

      if(res == D[i1][j2] + 2)
      {
        result.insert(right[j]);
        return RecoverResultD(i1, j2, result);
      }

      assert(res == B[i2][j2] + 3);

      result.insert(right[j]);
      result.insert(left[i1]);
      return RecoverResultB(i2, j2, result);
    }
  }

  void BipartiteGraph::RecoverResultD(int i, int j, unordered_set<int> & result)
  {
    int j1 = j - 1;
    int i2 = l[right[j]] - 1;
    int j2 = l[left[i]] - 1;

    result.insert(right[j]);

    if(j1 <= l[left[i]])
    {
      result.insert(left[i]);
      return RecoverResultA(i2, j1, result);
    }
    else if(! E(left[i2], right[j1] ))
    {
      return RecoverResultD(i, j1, result);
    }
    else 
    {
      int res = D[i][j];
      if(res == A2(i2, j2) + 2)
      {
        result.insert(left[i]);
        return RecoverResultA(i2, j2, result);
      }

      if(res == C[i2][j1] + 2)
      {
        result.insert(left[i]);
        return RecoverResultC(i2, j1, result);
      }

      if(res == D[i][j1] + 1)
      {
        return RecoverResultD(i, j1, result);
      }

      assert(res == B[i2][j2] + 3);

      result.insert(left[i]);
      result.insert(right[j1]);
      return RecoverResultB(i2, j2, result);
    }
  }

  unordered_set<int> BipartiteGraph::Fvs()
  {
    unordered_set<int> result;
    for(int i=0; i<n; i++) 
      result.insert(i);
    unordered_set<int> mcfs;

        int size = FvsCount();
    for(int x : isolated)
      result.erase(x);

    RecoverResultA(left.size()-1, right.size()-1, mcfs);

    for(int x : mcfs)
      result.erase(x);

    assert((int)result.size() == size);
    return result;
  }
}
