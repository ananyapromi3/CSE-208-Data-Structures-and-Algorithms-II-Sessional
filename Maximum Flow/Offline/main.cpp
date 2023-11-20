#include <iostream>
#include "BaseballElimination.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, w, l, r, k;
    string team;
    cin >> n;
    BaseballElimination *b;
    b = new BaseballElimination(n);
    for (int i = 0; i < n; i++)
    {
        cin >> team >> w >> l >> r;
        b->addTeam(i, team);
        b->updateTeamInfo(i, w, l, r);
        for (int j = 0; j < n; j++)
        {
            cin >> k;
            b->addMatch(i, j, k);
        }
    }
    b->constructGraph();
    b->elimination();
    for (auto str : b->eliminated)
    {
        cout << str << " is eliminated.\n";
        b->details(str);
    }
    return 0;
}