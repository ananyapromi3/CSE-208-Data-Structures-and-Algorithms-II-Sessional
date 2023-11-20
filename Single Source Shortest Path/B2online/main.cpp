#include <iostream>
#include "Graph.h"
#include <map>
#include <string>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, w, f, ans;
    map<string, int> node_no;
    map<int, string> node_name;
    cin >> n >> f;
    g = new Graph(n);
    int weight[n];
    string str1, str2;
    for (int i = 0; i < n; i++)
    {
        cin >> str1 >> w;
        node_no[str1] = i;
        weight[i] = w;
        node_name[i] = str1;
    }
    for (int i = 0; i < f; i++)
    {
        cin >> str1 >> str2 >> w;
        g->addEdge(node_no[str1], node_no[str2], w);
        g->addEdge(node_no[str2], node_no[str1], w);
    }
    cin >> str1 >> str2;
    ans = g->dijkstra(node_no[str1], node_no[str2]);
    stack<int> path;
    int i = node_no[str2];
    while (g->parent[i] != -1)
    {
        path.push(i);
        i = g->parent[i];
    }
    if (i != node_no[str1])
    {
        cout << "No path found\n";
    }
    else
    {
        cout << str1;
        while (!path.empty())
        {
            int v = path.top();
            path.pop();
            cout << " -> " << node_name[v];
            ans += weight[v];
        }
        cout << "\n";
    }
    cout << ans << "\n";
    return 0;
}