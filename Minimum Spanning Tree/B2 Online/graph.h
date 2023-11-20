#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;
class Graph // undirected;
{
    int vertex_count, edge_count;
    vector<pair<int, double> > *adj;
    vector<pair<double, pair<int, int> > > wList;
    int *parent;
    double *key;
    bool *inMST;

public:
    set<pair<int, int> > mstEdge;
    Graph(int n, int m)
    {
        vertex_count = n;
        edge_count = m;
        adj = new vector<pair<int, double> >[n];
        parent = new int[n];
        key = new double[n];
        inMST = new bool[n];
    }
    ~Graph()
    {
        init();
        for (int i = 0; i < vertex_count; i++)
        {
            adj[i].clear();
        }
        delete[] adj;
        mstEdge.clear();
        delete[] parent;
        delete[] key;
        delete[] inMST;
    }
    void init()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            parent[i] = i;
            key[i] = (double)INT_MAX;
            inMST[i] = false;
        }
        for (int i = 0; i < vertex_count; i++)
        {
            for (auto l : adj[i])
            {
                wList.push_back(make_pair(l.second, make_pair(i, l.first)));
            }
        }
        mstEdge.clear();
    }
    void addEdge(int u, int v, double w)
    {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    // All About Prim's
    double totalWeightPrim()
    {
        double sum = 0.0;
        for (int i = 0; i < vertex_count; i++)
        {
            sum += key[i];
        }
        return sum;
    }
    int primMST()
    {
        init();
        priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > q;
        int root = 0;
        key[root] = 0.0;
        q.push(make_pair(key[root], root));
        while (!q.empty())
        {
            int u = q.top().second;
            q.pop();
            if (!inMST[u])
            {
                inMST[u] = true;
                for (auto p : adj[u])
                {
                    int v = p.first;
                    double w = p.second;
                    if (!inMST[v] && w < key[v])
                    {
                        key[v] = w;
                        q.push(make_pair(key[v], v));
                        parent[v] = u;
                    }
                }
            }
        }
        for (int i = 0; i < vertex_count; i++)
        {
            if (parent[i] != i)
            {
                mstEdge.insert(make_pair(min(parent[i], i), max(parent[i], i)));
            }
        }
        return root;
    }
    void printMST()
    {
        for(auto e: mstEdge)
        {
            cout << e.first << " " << e.second << "\n";
        }
    }
};