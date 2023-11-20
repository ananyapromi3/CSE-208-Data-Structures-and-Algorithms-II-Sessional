#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include <set>
#include "dsu.h"
#define INF 100000
using namespace std;
class Graph // undirected;
{
    int vertex_count;
    int **grph;

public:
    Graph(int n)
    {
        vertex_count = n;
        grph = new int *[n];
        for (int i = 0; i < n; i++)
        {
            grph[i] = new int[n];
        }
        for (int i = 0; i < vertex_count; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                grph[i][j] = INF;
            }
        }
        for (int i = 0; i < vertex_count; i++)
        {
            grph[i][i] = 0;
        }
    }
    ~Graph()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            delete[] grph[i];
        }
        delete[] grph;
    }
    void addEdge(int u, int v, double w)
    {
        grph[u][v] = w;
        grph[v][u] = w;
    }

    set<pair<int, int> > kruskalMST()
    {
        set<pair<int, int> > edges;
        vector<pair<int, pair<int, int> > > wList;
        for (int i = 0; i < vertex_count; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                wList.push_back(make_pair(grph[i][j], make_pair(i, j)));
            }
        }
        sort(wList.begin(), wList.end());
        DSU *dsu;
        dsu = new DSU(vertex_count);
        int ans = 0;
        for (auto wl : wList)
        {
            double w = wl.first;
            int u = wl.second.first;
            int v = wl.second.second;
            if (dsu->findNode(u) != dsu->findNode(v))
            {
                dsu->unionNode(u, v);
                ans += w;
                edges.insert(make_pair(min(u, v), max(u, v)));
            }
        }
        return edges;
    }

    vector<int> eulerian_tour()
    {
        set<pair<int, int> > edges;
        edges = kruskalMST();
        vector<int> tour;
        vector<vector<int> > adj(vertex_count);
        for (auto e : edges)
        {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
        }
        bool *visited;
        visited = new bool[vertex_count];
        for (int i = 0; i < vertex_count; i++)
        {
            visited[i] = false;
        }
        dfs(&tour, 0, visited, adj);
        tour.push_back(0);
        return tour;
    }

    void dfs(vector<int> *tour, int v, bool *visited, vector<vector<int> > adj)
    {
        visited[v] = true;
        tour->push_back(v);
        for (auto e : adj[v])
        {
            {
                if (!visited[e])
                    dfs(tour, e, visited, adj);
            }
        }
    }

    vector<int> exact_tsp()
    {
        vector<int> tour;
        int **dp = new int *[1 << vertex_count];
        for (int i = 0; i < (1 << vertex_count); ++i)
        {
            dp[i] = new int[vertex_count];
        }
        for (int i = 0; i < (1 << vertex_count); i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                dp[i][j] = INF;
            }
        }
        dp[1][0] = 0;
        int **path = new int *[1 << vertex_count];
        for (int i = 0; i < (1 << vertex_count); ++i)
        {
            path[i] = new int[vertex_count];
        }
        for (int i = 0; i < (1 << vertex_count); ++i)
        {
            for (int j = 0; j < vertex_count; ++j)
            {
                path[i][j] = -1;
            }
        }
        for (int s = 1; s < (1 << vertex_count); s++)
        {
            for (int u = 1; u < vertex_count; u++)
            {
                if (s & (1 << u)) // s contains u
                {
                    for (int v = 0; v < vertex_count; v++)
                    {
                        if (v != u && (s & (1 << v))) // s contains v
                        {
                            if (dp[s][u] > dp[s ^ (1 << u)][v] + grph[v][u])
                            {
                                dp[s][u] = dp[s ^ (1 << u)][v] + grph[v][u];
                                path[s][u] = v;
                            }
                        }
                    }
                }
            }
        }
        int min_cost = INF;
        int last_vertex = -1;
        for (int u = 1; u < vertex_count; u++)
        {
            if (min_cost > dp[(1 << vertex_count) - 1][u] + grph[u][0])
            {
                min_cost = dp[(1 << vertex_count) - 1][u] + grph[u][0];
                last_vertex = u;
            }
        }
        int mask = (1 << vertex_count) - 1;
        tour.push_back(0);
        while (last_vertex != -1)
        {
            int prev_vertex = path[mask][last_vertex];
            tour.push_back(last_vertex);
            mask ^= (1 << last_vertex);
            last_vertex = prev_vertex;
        }
        reverse(tour.begin(), tour.end());
        for (int i = 0; i < (1 << vertex_count); i++)
        {
            delete[] dp[i];
        }
        delete[] dp;
        return tour;
    }

    int calculate_tour_length(vector<int> tour)
    {
        int len = 0;
        int n = tour.size();
        for (int i = 0; i < n; ++i)
        {
            int u = tour[i];
            int v = tour[(i + 1) % n];
            len += grph[u][v];
        }
        return len;
    }
};