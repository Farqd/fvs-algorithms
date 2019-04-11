#pragma once

#include "util/util.h"
#include "permutation/util.h"

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iostream>


using namespace std;

namespace permutation_graphs
{

    class PermutationGraph
    {
    public:
            
        PermutationGraph(vector<int> const& permutation);

        unordered_set<int> Fvs();
        
        int FvsCount();

        Graph const graph;

    private:

        vector<int> permutation;
        vector<int> permutation_inv;

        vector<vector<int>> brcl;
        int n;
        int limit[100];
        int pred[100];
        int pred_inv[100];

        int A[100];
        int B[100];
        int C[100][100];
        int D[100][100];
        int E[100][100];
        int F[100][100];


        struct CrossPair
        {
            int i;
            int j;
            int ix;
        };

        vector<CrossPair> edges;

        void PrintCP(int x)
        {
            cerr << edges[x].ix << ": " << edges[x].i << " " << edges[x].j << endl;

        }
        
        unordered_map<int, int>  edges_map[100];
        int GetCrossPairIx(int i, int j);
    };
}
