#include "util/util.h"
#include "permutation/util.h"

#include "bipartite_permutation/bipartite_permutation.h"


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
          cerr << vertex << " " << x << endl;
          cerr << side[x] << " " << side[vertex] << endl;
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

      for(int i=0; i< (int)graph.size(); i++)
        if(side[i] == 1)
          result.first.push_back(i);
        else
          result.second.push_back(i);

      return result;
    }
  }

    // Generate Bipartite Permutaiton graph, left & right are ordered using Strong Ordering
  BipartiteGraph::BipartiteGraph(vector<int> const& permutation) : graph(PermutationToGraph(permutation))
  {      
    // util::PrintGraph(graph);

    pair<vector<int>, vector<int>> sides = BipartiteDivide(graph);

    left.push_back(-1);
    right.push_back(-1);

    left.insert(left.end(), sides.first.begin(), sides.first.end());
    right.insert(right.end(), sides.second.begin(), sides.second.end());

    n = graph.size();

    edges_map.resize(n);
    for(int i=0; i<n; i++)
      for(int x : graph[i])
        edges_map[i].insert(x);


    // FIX it works in n^2 now
    for(int sum = 0; sum < (int)left.size() + (int)right.size(); sum++)
    {
      int up = min<int>(sum + 1, left.size());
      for(int i=0; i < up; i++)
      {
        int x = left[i];

        if(sum - i >= (int)right.size())
          continue;

        int y = right[sum - i];

        if(E(x,y))
          edges.push_back( { i, sum-i } );
      }
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
    
    for(int i=1; i<(int)left.size(); i++)
    for(int j=1; j<(int)right.size(); j++)
    {
      if(E(left[i], right[j]))
      {
        l[left[i]] = min(l[left[i]], j);
        l[right[j]] = min(l[right[j]], i);

        r[left[i]] = max(r[left[i]], j);
        r[right[j]] = max(r[right[j]], i);
      }
    }

      // cerr << endl;
      // util::PrintVector(l);
      // util::PrintVector(r);
      // cerr << endl;

  }

  int BipartiteGraph::A2(int i, int j)
  {
    if(i==0 && j==0)
      return 0;
    if(E(left[i], right[j]))
      return A[i][j];
    if(r[left[i]] < j)
      return A[i][r[right[j]]] + j - (r[left[i]] + 1) + 1;
    if(r[right[j]] < i)
      return A[r[right[j]]][j] + i - (r[right[j]]+1) + 1;
    assert(false);
  }

  int BipartiteGraph::CalculateFVS()
  {
    int l_size = left.size(); int r_size = right.size();

    auto resize_matrix_fun = [=](vector<vector<int> > & matrix){
        matrix.resize(l_size);
        for(auto & row : matrix)
          row.resize(r_size);
    };

    resize_matrix_fun(A);
    resize_matrix_fun(B);
    resize_matrix_fun(C);
    resize_matrix_fun(D);

    CalculateLAndR();

    // ALGO
    // we want to calculate dp in order where (x, y) is calculated before (x2, y2) if x + y < x2 + y2
    for(auto const& edge : edges)
    {
      int i = edge.first;
      int j = edge.second;

      // cerr << i << " " << j << endl;

      // int xi = left[i];
      // int yj = right[j];

      // cerr << "xi yj " << xi << " " << yj << endl;
      
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
        int tmp = max( { A2(i2,j1) + 2, C[i1][j] + 1, D[i1][j2] + 2 } );
        if(E(left[i2], right[j2]) && l[right[j1]] == i2)
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
        if(E(left[i1], right[j2]) && l[right[j1]] == i2)
          D[i][j] = max(tmp, B[i1][j2] + 3);
        else
          D[i][j] = tmp;
      }

      B[i][j] = max(C[i][j], D[i][j]);
      A[i][j] = max({ A2(i1, j), A2(i, j1), B[i][j]  });

    }

    // cerr << endl;
    // for(int i=0; i<3; i++)
    // for(int j=0; j<3; j++)
    //   cerr << i << " " << j << " " << A[i][j] << endl;

    // cerr << endl;
    // for(int i=0; i<3; i++)
    // for(int j=0; j<3; j++)
    //   cerr << "C " << i << " " << j << " " << C[i][j] << endl;

    

      
    // cerr << endl;
    return n - A[left.size()-1][right.size()-1];
  }

}