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
        for(int x : permutation)
        cerr << x <<" ";
        cerr<<endl;
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
        int result = edges_map[i][j];
        assert(result >= 0);
        return result;
        // return edges_map[i][j];
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
                }
        }
        
        limit.resize(m);
        pred.resize(m);
        pred_inv.resize(m);

        A.resize(m);
        B.resize(m);

        C.resize(m+1, vector<int>(n+1, 0));
        D.resize(m+1, vector<int>(n+1, 0));
        E.resize(m+1, vector<int>(n+1, 0));
        F.resize(m+1, vector<int>(n+1, 0));
        
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
            
        for(auto const& edge : edges)
        {
            if(edge.i == 0) { pred[0] = 0; continue; }

            int i = edge.j - 1;
            while(permutation_inv[i] > permutation_inv[edge.i])
                i--;
            pred[edge.ix] = i;
        }

        // pred_inv
        for(auto const& edge : edges)
        {
            if(edge.i == 0) { pred_inv[0] = 0; continue; }

            int i_pos = permutation_inv[edge.i] - 1;
            while(permutation[i_pos] > edge.j)
                i_pos--;
            pred_inv[edge.ix] = permutation[i_pos];
        }

        for(int i=1; i<n; i++)
            C[0][i] = D[0][i] = E[0][i] = F[0][i] = 1;
        
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
                if(k > j && permutation_inv[k] < permutation_inv[i])
                {
                    if(permutation_inv[k] < permutation_inv[j])
                        F[ij][k] = 0;
                    else
                    {
                        int ik = GetCrossPairIx(i,k);
                        F[ij][k] = max({ D[limit[ik]][j] + 2,
                                    C[limit[jj]][i] + 2,
                                    A[limit[ij]] + 3});
                    }
                }

                //C[ij][k]
                if(k > j)
                    C[ij][k] = A[ij] + 1;
                else if(k < j && i == j)
                    C[ij][k] = C[limit[jj]][k] + 1;
                else if(k < j && i != j)
                {
                    int j2 = pred[ij];
                    int ij2 = GetCrossPairIx(i, j2);

                    int i2 = pred_inv[ij];
                    int i2j = GetCrossPairIx(i2, j);
                    C[ij][k] = max({ C[ij2][k],
                                    C[i2j][k],
                                    E[ij][k]});
                }

                // D[ij][k]
                if(k > j)
                {
                    if(permutation_inv[k] > permutation_inv[i])
                        D[ij][k] = A[ij] + 1;
                    else if(permutation_inv[k] < permutation_inv[i] && i == j)
                        D[ij][k] = D[limit[ij]][k] + 1;
                    else if(permutation_inv[k] < permutation_inv[i] && i != j)
                    {
                        int j2 = pred[ij];
                        int ij2 = GetCrossPairIx(i, j2);

                        int i2 = pred_inv[ij];
                        int i2j = GetCrossPairIx(i2, j);
                        D[ij][k] = max({ D[ij2][k],
                                        D[i2j][k],
                                        F[ij][k]});
                    }
                }
            }

        }
        
        int last_edge = edges.back().ix;
        return n - A[last_edge] - 1;
    }

    unordered_set<int> PermutationGraph::Fvs()
    {
        return {};
    }

}