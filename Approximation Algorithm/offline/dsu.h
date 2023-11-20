#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
class DSU
{
    int *parent;
    int *rank;

public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
    ~DSU()
    {
        delete[] parent;
        delete[] rank;
    }
    int findNode(int v)
    {
        if (parent[v] == -1)
        {
            return v;
        }
        return parent[v] = findNode(parent[v]);
    }
    void unionNode(int u, int v)
    {
        int u_p = findNode(u);
        int v_p = findNode(v);
        if (u_p != v_p)
        {
            if (rank[u_p] < rank[v_p])
            {
                parent[u_p] = v_p;
            }
            else if (rank[u_p] > rank[v_p])
            {
                parent[v_p] = u_p;
            }
            else
            {
                parent[v_p] = u_p;
                rank[u_p]++;
            }
        }
    }
};