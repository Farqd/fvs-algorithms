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
        
        vector<int> limit;
        vector<int> pred;
        vector<int> pred_inv;
        
        vector<int> A;
        vector<int> B;
        
        vector<vector<int>> C;
        vector<vector<int>> D;
        vector<vector<int>> E;
        vector<vector<int>> F;
        
        void RecoverResultA(int ix, unordered_set<int> & result);
        void RecoverResultB(int ix, unordered_set<int> & result);

        void RecoverResultC(int ix, int k, unordered_set<int> & result);
        void RecoverResultD(int ix, int k, unordered_set<int> & result);
        void RecoverResultE(int ix, int k, unordered_set<int> & result);
        void RecoverResultF(int ix, int k, unordered_set<int> & result);

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
