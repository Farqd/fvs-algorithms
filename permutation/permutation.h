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

        // Permutation staring from 0, e.g. [2,3,0,1]
        PermutationGraph(vector<int> const& permutation);

        // Returns minum FVS
        unordered_set<int> Fvs();
        
        // Returns size of minumum FVS
        int FvsCount();

        // Underlying graph for debugging
        Graph const graph;

    private:

        vector<int> permutation;
        
        // Inverse permutation
        vector<int> permutation_inv;

        // All data structures as defined in paper
        vector<vector<int>> brcl;
        int n;
        
        vector<int> limit;
        vector<int> pred;
        vector<int> pred_inv;
        
        vector<int> A;
        vector<int> B;
        
        vector<vector<int>> C;
        vector<vector<int>> D;
        vector<vector<int>> E;
        vector<vector<int>> F;
        
        void RecoverResultA(int ij, unordered_set<int> & result);
        void RecoverResultB(int ij, unordered_set<int> & result);

        void RecoverResultC(int ij, int k, unordered_set<int> & result);
        void RecoverResultD(int ij, int k, unordered_set<int> & result);
        void RecoverResultE(int ij, int k, unordered_set<int> & result);
        void RecoverResultF(int ij, int k, unordered_set<int> & result);

        struct CrossPair
        {
            int i;
            int j;
            int ix;
        };

        vector<CrossPair> edges;

        vector<unordered_map<int, int> > edges_map;
        int GetCrossPairIx(int i, int j);
    };
}
