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
            int k = parent[i];
            if(k == -1)
                continue;
            v_not_in_parent[i] = v[i];
            for(int x : v[k])
                v_not_in_parent[i].erase(x);
            v_not_in_parent[i].insert(-1);
        }

        auto unpack  = [&](int k){
            pair<int, int> result;
            int a = k / (n+1);
            int b = k % (n+1);

            return pair<int, int> { a-1, b-1 };
        };

        auto pack = [&](int a, int b)
        {
            if(a > b)
                swap(a,b);
            return (a+1) * (n+1) + b + 1;
        };

        auto get_result_lam = [&](int k, int a, int b) {
            if(v[k].count(a) && v[k].count(b))
                return results[k][pack(a, b)];
            if( (!v[k].count(a)) && (!v[k].count(b)))
            {
                // dwóch dowolnych ziomków nie z parent, może być -1
                int tmp = 0;
                for(int x : v_not_in_parent[k])
                for(int y : v_not_in_parent[k])
                    tmp = max(tmp, results[k][pack(x, y)]);
                return tmp;
            }
            assert(v[k].count(a) ||v[k].count(b));

            if(v[k].count(b))
                a = b;

            // jeden ziom nie z parent, moze byc -1
            int tmp = 0;
            for(int x : v_not_in_parent[k])
                tmp = max(tmp, results[k][pack(a, x)]);
            return tmp;
        };

        for(int i=0; i<n; i++)
        {
            vector<int> candidates;
            candidates.push_back(-1);
            for(int x : v[i])
                candidates.push_back(x);
            
            vector<int> children;
            for(int x : graph_reordered[i])
                if(parent[x] == i)
                    children.push_back(x);
            
            auto ptx = [&](int k){
                int res = 0;
                for(int x: children)
                    if(v[x].count(k))
                        ++res;
                return res;
            };

            for(int x : candidates)
            for(int y : candidates)
            {
                int tmp = 0;
                if(x != -1)
                    tmp++;
                if(y != -1 && x!=y)
                    tmp++;
                
                tmp -= ptx(x);
                tmp -= ptx(y);
                for(int child : children)
                    tmp += get_result_lam(child, x, y);

                results[i][pack(x, y)] = tmp;
            }

        }
        int result = 0;
        for(auto const& p : results[n-1])
            result = max(p.second, result);

        return n - result;
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