#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include <set>
#include "DSU.h"
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
    // All About Kruskal's
    double kruskalMST()
    {
        init();
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
                mstEdge.insert(make_pair(min(u, v), max(u, v)));
            }
        }
        return ans;
    }
    // All About reverse delete algorithm
    bool isConnected()
    {
        bool isVisited[vertex_count];
        for (int i = 0; i < vertex_count; i++)
        {
            isVisited[i] = false;
        }
        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            isVisited[u] = true;
            for (auto k: adj[u])
            {
                int v = k.first;
                if (!isVisited[v])
                {
                    q.push(v);
                }
            }
        }
        for (int i = 0; i < vertex_count; i++)
        {
            if (!isVisited[i])
            {
                return false;
            }
        }
        return true;
    }
    double reverseDeleteMST()
    {
        init();
        sort(wList.begin(), wList.end());
        double ans = 0.0;
        for (int i = wList.size() - 1; i >= 0; i--)
        {
            int u = wList[i].second.first;
            int v = wList[i].second.second;
            auto it = adj[u].begin();
            double w;
            for (auto it = adj[u].begin(); it != adj[u].end(); it++)
            {
                if ((*it).first == v)
                {
                    w = (*it).second;
                    adj[u].erase(it);
                }
            }
            for (auto it = adj[v].begin(); it != adj[v].end(); it++)
            {
                if ((*it).first == u)
                {
                    adj[v].erase(it);
                }
            }
            if (!isConnected())
            {
                adj[u].push_back(make_pair(v, w));
                adj[v].push_back(make_pair(u, w));
                mstEdge.insert(make_pair(min(u, v), max(u, v)));
                ans += w;
            }
        }
        return ans;
    }
    void printMST()
    {
        for(auto e: mstEdge)
        {
            cout << e.first << " " << e.second << "\n";
        }
    }
};