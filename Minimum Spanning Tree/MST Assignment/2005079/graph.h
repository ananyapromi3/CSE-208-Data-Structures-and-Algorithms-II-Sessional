#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include "DSU.h"
using namespace std;
class Graph // undirected;
{
    int vertex_count, edge_count;
    vector<pair<int, double> > *adj;
    vector<pair<int, int> > kruskalEdge;
    int *primParent;
    double *key;
    bool *inMST;

public:
    Graph(int n, int m)
    {
        vertex_count = n;
        edge_count = m;
        adj = new vector<pair<int, double> >[n];
        primParent = new int[n];
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
        kruskalEdge.clear();
        delete[] primParent;
        delete[] key;
        delete[] inMST;
    }
    void init()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            primParent[i] = i;
            key[i] = (double)INT_MAX;
            inMST[i] = false;
        }
    }
    void addEdge(int u, int v, double w)
    {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    // All About Prim's
    void printPrim()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            if (primParent[i] != i)
            {
                cout << primParent[i] << " " << i << "\n";
            }
        }
    }
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
                        primParent[v] = u;
                    }
                }
            }
        }
        return root;
    }
    // All About Kruskal's
    void printKruskal()
    {
        for(auto e: kruskalEdge)
        {
            cout << e.first << " " << e.second << "\n";
        }
    }
    double kruskalMST()
    {
        vector<pair<double, pair<int, int> > > wList;
        for (int i = 0; i < vertex_count; i++)
        {
            for (auto l : adj[i])
            {
                wList.push_back(make_pair(l.second, make_pair(i, l.first)));
            }
        }
        sort(wList.begin(), wList.end());
        DSU *dsu;
        dsu = new DSU(vertex_count);
        double ans = 0.0;
        for (auto wl : wList)
        {
            double w = wl.first;
            int u = wl.second.first;
            int v = wl.second.second;
            if (dsu->findNode(u) != dsu->findNode(v))
            {
                dsu->unionNode(u, v);
                ans += w;
                kruskalEdge.push_back(make_pair(u, v));
            }
        }
        return ans;
    }
};