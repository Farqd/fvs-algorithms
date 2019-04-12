#include "chordal/chordal.h"

#include "permutation/util.h"
#include "util/util.h"

#include <list>
#include <unordered_set>

namespace chordal
{


    ChordalGraph::ChordalGraph(Graph const& graph)
        : graph(graph)
    {
        n = graph.size();
        perfect_elimination = FindPerfectElimination(graph);
        perfect_elimination_inv = permutation_graphs::InversePermutation(perfect_elimination);

        graph_reordered.resize(n);
        for(int i=0; i<n; i++)
        {
            int ix = perfect_elimination_inv[i];
            for(int x : graph[i])
                graph_reordered[ix].push_back(perfect_elimination_inv[x]);
        }

        if(!IsChordal())
            throw GraphIsNotChordal{};
    }

    int ChordalGraph::FvsCount()
    {
        return Fvs().size();
    }

    bool ChordalGraph::IsChordal()
    {
        vector<int> mark(n);
        vector<int> p(n, n);

        for(int i=0; i<n; i++)
        for(int x : graph_reordered[i])
            if(x > i)
                p[i] = min(p[i], x);

        for(int w=0; w<n; w++)
        {
            for(int x : graph_reordered[w])
                if(x > w)
                    mark[x] = 1;
            
            for(int x : graph_reordered[w])
            if(p[x] == w)
            {
                for(int y : graph_reordered[x])
                if(y > w && mark[y] == 0)
                    return false;
            }

            for(int x : graph_reordered[w])
                mark[x] = 0;
        }
        return true;
    }

    int ChordalGraph::GetFirst(list<set_timestamp_pair> & sequence)
    {
        while(sequence.begin()->first.size() == 0)
            sequence.pop_front();
        int x = *sequence.begin()->first.begin();
        sequence.begin()->first.erase(x);
        return x;
    }

    unordered_set<int> ChordalGraph::Fvs()
    {
        unordered_set<int> result;
        
        for(int i=0; i<n; i++)
        {
            int nc = 0;
            for(int x : graph_reordered[i])
                if(x >= i) ++nc;
            if(nc <= 1) continue;

            int rem = numeric_limits<int>::max();
            
            if(result.count(i) == 0)
                rem = i;
            
            for(int x : graph_reordered[i])
                if(x >= i && result.count(x) == 0)
                    rem = min(rem, x);
            for(int x : graph_reordered[i])
                if(x >= i && x != rem)
                    result.insert(x);
            if(i != rem)
                result.insert(i);
        }

        unordered_set<int> reorder;
        for(int x : result)
            reorder.insert(perfect_elimination[x]);
        return reorder;
    }

    vector<int> ChordalGraph::FindPerfectElimination(Graph const& graph)
    {
        vector<int> result;
        n = graph.size();

        list< set_timestamp_pair > sequence;
        vector<list< set_timestamp_pair>::iterator> vertex_to_set(n);
        vector<bool> processed(n, false);

        sequence.push_front({{}, -1});
        for(int i=0; i<n; i++)
        {
            sequence.begin()->first.insert(i);
            vertex_to_set[i] = sequence.begin();
        }
        
        auto add_elem_fun = [&](int x, int timestamp) {
            auto it = vertex_to_set[x];
            if(timestamp != it->second)
            {
                sequence.insert(it, {{}, timestamp});
                it->second = timestamp;
            }

            it->first.erase(x);
            it--;
            it->first.insert(x);
            vertex_to_set[x] = it;
        };
        
        for(int i=0; i<n; i++)
        {
            int el = GetFirst(sequence);
            processed[el] = true;

            for(int x : graph[el])
            {
                if(processed[x])
                    continue;
                add_elem_fun(x, i);
            }
            result.push_back(el);
        }

        reverse(result.begin(), result.end());
        return result;
    }


}