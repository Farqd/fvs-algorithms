#include "permutation/permutation.h"

#include "util/util.h"
#include "permutation/util.h"

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace permutation_graphs
{

    PermutationGraph::PermutationGraph(vector<int> const& permutation)
        : graph(PermutationToGraph(permutation))
    {
        // Adding 0->0 to the permutation, later existance of this line
        // makes code simpler
        this->permutation.push_back(0);
        for(int x : permutation)
            this->permutation.push_back(x+1);
        n = this->permutation.size();
        permutation_inv = InversePermutation(this->permutation);
        


    }

    int PermutationGraph::GetCrossPairIx(int i, int j)
    {
        assert(edges_map[i].count(j));
        return edges_map[i][j];
    }

    // Caclulate A,B,C,D,E,F as described in paper in order of 'ordered cross pairs'
    // 
    
    int PermutationGraph::FvsCount()
    {
        // (edges (brcl)
        int m = 0;
        for(int i=0; i<n; i++)
        {
            int pos = permutation_inv[i];
            for(int j = pos; j < n; j++)
                if(permutation[j] <= i)
                {
                    edges_map[permutation[j]][i] = m;
                    edges.push_back({permutation[j], i, m++});
                    cerr << permutation[j] << " " << i << endl;
                }
        }

        // limit
        limit[0] = 0;
        for(auto const& edge : edges)
        {
            if(edge.i == 0) continue;

            int j = edge.i - 1;
            while(permutation_inv[j] >= permutation_inv[edge.j])
                j--;
            
            int i_pos = permutation_inv[edge.j] - 1;
            while(permutation[i_pos] >= edge.i)
                i_pos--;
            int i = permutation[i_pos];
            limit[edge.ix] = GetCrossPairIx(i, j);
        }
            
        // cerr << "LIMIT: " << endl;
        // PrintCP(limit[GetCrossPairIx(1, 1)]);
        // PrintCP(limit[GetCrossPairIx(4, 6)]);
        // PrintCP(limit[GetCrossPairIx(5, 7)]);
        
        for(int x : permutation_inv)
        cerr << x << " ";
        cerr << endl;
        // pred
        for(auto const& edge : edges)
        {
            if(edge.i == 0) { pred[0] = 0; continue; }

            int i = edge.j - 1;
            while(permutation_inv[i] > permutation_inv[edge.i])
                i--;
            pred[edge.ix] = i;
        }

        // cerr << pred[GetCrossPairIx(4, 7)] << endl;
        // cerr << pred[GetCrossPairIx(3, 6)] << endl;
        

        // pred_inv
        for(auto const& edge : edges)
        {
            if(edge.i == 0) { pred_inv[0] = 0; continue; }

            int i_pos = permutation_inv[edge.i] - 1;
            while(permutation[i_pos] > edge.j)
                i_pos--;
            pred_inv[edge.ix] = permutation[i_pos];
        }

        // cerr << pred_inv[GetCrossPairIx(3, 8)] << endl;
        // cerr << pred_inv[GetCrossPairIx(4, 7)] << endl;

        for(auto const& edge : edges)
        {
            if(edge.i == 0) continue;

            int i = edge.i;
            int j = edge.j;
            int ij = edge.ix;
            int ii = GetCrossPairIx(i,i);
            int jj = GetCrossPairIx(j, j);

            // B
            B[ij] = max({ C[limit[jj]][i] + 1,  
                            D[limit[ii]][j] + 1,
                            A[limit[ij]] + 2});

            // A
            if(i == j)
            {
                A[ij] = A[limit[ij]] + 1;
            }
            else
            {
                // bug in pseudocode :(
                int k1 = pred[ij];
                int k2 = pred_inv[ij];
                A[ij] = max({ A[GetCrossPairIx(i, k1)],
                              A[GetCrossPairIx(k2, j)],
                              B[ij]});
            }
            
            for(int k = 1; k < n; k++)
            {
                // E[ij][k]
                if(permutation_inv[k] > permutation_inv[i] && k < j)
                {
                    if(k < i)
                        E[ij][k] = 0;
                    else
                    {
                        int kj = GetCrossPairIx(k, j);
                        E[ij][k] = max({ C[limit[kj]][i] + 2,
                                    D[limit[ii]][j] + 2,
                                    A[limit[ij]] + 3});
                    }
                }

                // F[ij][k]
                // if(k > j && permutation_inv[k] )
            }

        }
        


        return 0;
    }

    unordered_set<int> PermutationGraph::Fvs()
    {
        return {};
    }

}