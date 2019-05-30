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

    pair<int, int> ChordalGraph::Unpack(long long k){
        pair<int, int> result;
        int a = k / (n+1);
        int b = k % (n+1);

        return pair<int, int> { a-1, b-1 };
    };

    long long ChordalGraph::Pack(int a, int b)
    {
        if(a > b)
            swap(a,b);
        return (long long)(a+1) * (n+1) + b + 1;
    };

    int ChordalGraph::FvsCount()
    {
        for(int i=0; i < n; i++)
        {
            parent[i] = numeric_limits<int>::max();
            v[i].insert(i);
            for(int x : graph_reordered[i])
                if(x > i)
                {
                    v[i].insert(x);
                    parent[i] = min(parent[i], x);
                }
            if(parent[i] == numeric_limits<int>::max())
                parent[i] = -1;
        }
        for(int i=0; i<n; i++)
        {
            for(int x : graph_reordered[i])
            if(parent[x] == i)
                children_tab[i].push_back(x);
        }

        for(int i=0; i<n; i++)
        {
            vector<int> candidates;
            candidates.push_back(-1);
            for(int x : v[i])
                candidates.push_back(x);

            //calculate part
            for(int x : candidates)
            for(int y : candidates)
            {
                if(x == y && x != -1) continue;
                int result = 0;
                if(x != -1) ++result;
                if(y != -1) ++result;

                for(int c : children_tab[i])
                {
                    int x2 = x; int y2 = y;
                    if(!v[c].count(x)) x2 = -1;
                    if(!v[c].count(y)) y2 = -1;

                    result += results[c][Pack(x2, y2)];
                    if(x2 != -1) --result;
                    if(y2 != -1) --result; 
                }

                results[i][Pack(x, y)] = result;
            }

            //update part
            if(i == n-1)
                continue;

            int p = parent[i];
            
            for(int x : candidates)
            for(int y : candidates)
            {
                int x2 = x;
                int y2 = y;
                if(!v[p].count(x))
                    x2 = -1;
                if(!v[p].count(y))
                    y2 = -1;
                
                long long p1 = Pack(x, y);
                long long p2 = Pack(x2, y2);
                results[i][p2] = max(results[i][p2], results[i][p1]);
            }
        }

        int result = 0;
        for(auto const& p : results[n-1])
            result = max(p.second, result);
        
        return n - result;
    }

    void ChordalGraph::RecoverResult(int k, int x, int y, unordered_set<int> & result)
    {
        result.insert(x);
        result.insert(y);
        
        auto recover_pair_fun = [&](int k, int a, int b) {
            int best_result = results[k][Pack(a,b)];
            if(a > b) swap(a,b);
            // for all pairs if one reduces to {a,b}

            pair<int, int> result {-1, -1};
            for(auto pai : results[k])
            {
                if(pai.second != best_result) 
                    continue;

                auto candidate = Unpack(pai.first);
                int x = candidate.first;
                int y = candidate.second;

                if(!v[parent[k]].count(x))
                    x = -1;
                if(!v[parent[k]].count(y))
                    y = -1;
                if(x > y) swap(x,y);
                    
                if(a == x && b == y)
                {
                    int n0r = 0;
                    if(result.first != -1)
                        n0r++;
                    if(result.second != -1)
                        n0r++;
                    
                    int n0c = 0;
                    if(candidate.first != -1)
                        n0c++;
                    if(candidate.second != -1)
                        n0c++;
                    if(n0c > n0r)
                        result = candidate;
                }
            }
            return result;
        };
        
        for(int child : children_tab[k])
        {
            int x2 = x;
            int y2 = y;
            if(!v[child].count(x))
                x2 = -1;
            if(!v[child].count(y))
                y2 = -1;
            
            auto p = recover_pair_fun(child, x2, y2);
            RecoverResult(child, p.first, p.second, result);
        }
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
        int score = FvsCount();
        
        pair<int, int> best;
        int tmp = 0;
        
        for(auto const& p : results[n-1])
        {
            if(p.second >= tmp)
            {
                tmp = p.second;
                best = Unpack(p.first);
            }
        }

        RecoverResult(n-1, best.first, best.second, result);
        
        unordered_set<int> reorder;
        for(int i=0; i<n; i++)
            reorder.insert(i);
        result.erase(-1);
        for(int x : result)
            reorder.erase(perfect_elimination[x]);

        // assert(reorder.size() == score);
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
