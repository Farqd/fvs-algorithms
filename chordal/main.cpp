#include "chordal/chordal.h"
#include "util/util.h"
#include "util/brute.h"
#include <chrono>
#include <functional>

using namespace chordal;

/* Chordal graph generation based on: https://link.springer.com/chapter/10.1007/978-3-319-57586-5_37*/

Graph generateTree(int const n)
{
    Graph result;

    result.resize(n);
    for(int i=1; i<n; i++)
    {
        int k = rand() % i;
        result[k].push_back(i);
        result[i].push_back(k);
    }

    return result;
}

unordered_set<int> generateSubtree(Graph const& graph, int const k)
{
    // k = size of three
    unordered_set<int> result;
    vector<int> vertices;

    int t_0 = rand() % graph.size();
    result.insert(t_0);
    vertices.push_back(t_0);

    for(int i=1; i<k; i++)
    {
        while(true)
        {
            int u = rand() % vertices.size(); u = vertices[u];
            vector<int> options;
            for(int x : graph[u])
                if(!result.count(x))
                    options.push_back(x);
            if(options.size() == 0) continue;
            int v = rand() % options.size(); v = options[v];
            assert(result.count(v) == 0);
            result.insert(v);
            vertices.push_back(v);
            break;
        }
    }

    return result;
}

vector<unordered_set<int> > generateSubtrees(Graph const& graph, int const k)
{
    vector<unordered_set<int> > result;

    for(int i=0; i<(int)graph.size(); i++)
    {
        int k1 = rand() % (std::min(2*k - 1, (int)graph.size()));
        result.push_back(generateSubtree(graph, k1 + 1));
    }

    return result;
}

Graph generateChordal(int const n, int const k)
{
    Graph result;
    result.resize(n);
    auto const& tree = generateTree(n);
    auto const& trees = generateSubtrees(tree, k);
    for(int i=0; i<(int)trees.size(); i++)
    for(int j=i+1; j<(int)trees.size(); j++)
    {
        for(auto const& x : trees[i])
        {
            if(trees[j].count(x))
            {
                result[i].push_back(j);
                result[j].push_back(i);
                break;
            }
        }
    }
    return result;
}

bool isConnected(Graph const& graph)
{
    vector<int> visited; visited.resize(graph.size());

    std::function<void(Graph const&,int, vector<int>&)> dfs;
    dfs = [&](Graph const& g, int k, vector<int> & v){
        if(v[k] == 1) return;
        v[k] = 1;
        for(int x : g[k])
            dfs(g, x, v);
    };

    dfs(graph, 0, visited);
    for(int i=0; i<(int)graph.size(); i++)
        if(!visited[i]) return false;
    return true;
}

int edges(Graph const& g)
{
    int result = 0;
    for(auto const& x : g)
        result += x.size();
    return result;
}

int main()
{
    srand(time(0));
    int N = 200; 
    int K = 50;

    cin >> N >> K;

    auto graph = generateChordal(N, K);
    while(!isConnected(graph))
    {
        cerr << "NOT CONNECTED" << endl;
        graph = generateChordal(N, K);
    }

    cerr << "N= " << N << endl;
    cerr << "edges= " << edges(graph) << endl;

    auto start = std::chrono::system_clock::now();
    ChordalGraph cg {graph};
            
    auto fvs = cg.Fvs();
    auto end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    cerr <<"FVS= " << fvs.size() << endl;
    assert(util::IsFvs(graph, fvs));


}