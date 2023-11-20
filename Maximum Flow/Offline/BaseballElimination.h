#include <iostream>
#include <map>
#include <vector>
#include "Graph.h"
using namespace std;
class BaseballElimination
{
    int teamCount;
    map<string, int> teamCode;
    vector<string> teamName;
    int *wins;
    int *loses;
    int *gamesLeft;
    int **matchAgainst;
    int nodeCount;
    Graph *g;
    map<string, int> nodeName;
    bool *isEliminated;

public:
    vector<string> eliminated;
    vector<string> *eliminationResp;
    BaseballElimination(int n)
    {
        teamCount = n;
        wins = new int[n];
        loses = new int[n];
        gamesLeft = new int[n];
        matchAgainst = new int *[n];
        eliminationResp = new vector<string>[n];
        isEliminated = new bool[n];
        for (int i = 0; i < n; i++)
        {
            matchAgainst[i] = new int[n];
            isEliminated[i] = false;
        }
        init();
    }
    ~BaseballElimination()
    {
        delete[] wins;
        delete[] loses;
        delete[] gamesLeft;
        for (int i = 0; i < teamCount; i++)
        {
            delete[] matchAgainst[i];
        }
        delete[] matchAgainst;
    }
    void init()
    {
        for (int i = 0; i < teamCount; i++)
        {
            for (int j = 0; j < teamCount; j++)
            {
                matchAgainst[i][j] = 0;
            }
        }
    }
    void addTeam(int i, string name)
    {
        teamName.push_back(name);
        teamCode[name] = i;
    }
    void updateTeamInfo(int i, int win, int lose, int left)
    {
        wins[i] = win;
        loses[i] = lose;
        gamesLeft[i] = left;
    }
    void addMatch(int i, int j, int count)
    {
        matchAgainst[i][j] = count;
        matchAgainst[j][i] = count;
    }
    void constructGraph()
    {
        nodeCount = 0;
        nodeName["s"] = nodeCount;
        for (int i = 0; i < teamCount; i++)
        {
            for (int j = i + 1; j < teamCount; j++)
            {
                if (matchAgainst[i][j])
                {
                    nodeName[to_string(i) + "-" + to_string(j)] = ++nodeCount;
                }
            }
        }
        for (int i = 0; i < teamCount; i++)
        {
            nodeName[to_string(i)] = ++nodeCount;
        }
        nodeName["t"] = ++nodeCount;
        g = new Graph(++nodeCount);
        for (int i = 0; i < teamCount; i++)
        {
            for (int j = i + 1; j < teamCount; j++)
            {
                if (matchAgainst[i][j])
                {
                    int u = nodeName[to_string(i) + "-" + to_string(j)];
                    int x = nodeName[to_string(i)];
                    int y = nodeName[to_string(j)];
                    g->addFlow(0, u, matchAgainst[i][j]);
                    g->addFlow(u, x, INF);
                    g->addFlow(u, y, INF);
                }
            }
        }
        for (int i = 0; i < teamCount; i++)
        {
            g->addFlow(nodeName[to_string(i)], nodeCount - 1, 0);
        }
    }
    bool updateGraph(int elim)
    {
        for (int i = 0; i < teamCount; i++)
        {
            if (matchAgainst[elim][i])
            {
                int u = nodeName[to_string(min(elim, i)) + "-" + to_string(max(elim, i))];
                g->updateFlow(0, u, 0);
            }
        }
        bool flag = false;
        for (int i = 0; i < teamCount; i++)
        {
            int u = nodeName[to_string(i)];
            if (i != elim)
            {
                if (wins[elim] + gamesLeft[elim] >= wins[i])
                {
                    g->updateFlow(u, nodeCount - 1, wins[elim] + gamesLeft[elim] - wins[i]);
                }
                else
                {
                    eliminationResp[elim].push_back(teamName[i]);
                    flag = true;
                }
            }
            else
            {
                g->updateFlow(u, nodeCount - 1, 0);
            }
        }
        return flag;
    }
    void resetGraph()
    {
        for (int i = 0; i < teamCount; i++)
        {
            for (int j = i + 1; j < teamCount; j++)
            {
                if (matchAgainst[i][j])
                {
                    int u = nodeName[to_string(i) + "-" + to_string(j)];
                    g->updateFlow(0, u, matchAgainst[i][j]);
                }
            }
        }
        for (int i = 0; i < teamCount; i++)
        {
            g->addFlow(nodeName[to_string(i)], nodeCount - 1, 0);
        }
    }
    void elimination()
    {
        for (int i = 0; i < teamCount; i++)
        {
            resetGraph();
            if (updateGraph(i))
            {
                eliminated.push_back(teamName[i]);
                isEliminated[i] = true;
            }
            else
            {
                g->Edmonds_Karp(0, nodeCount - 1);
                if (!g->isSaturated(0))
                {
                    eliminated.push_back(teamName[i]);
                    isEliminated[i] = true;
                    g->BFS(0, nodeCount - 1);
                    for (int j = 0; j < teamCount; j++)
                    {
                        if (g->parent[nodeName[to_string(j)]] != -1 && !isEliminated[j])
                        {
                            eliminationResp[i].push_back(teamName[j]);
                        }
                    }
                }
            }
        }
    }
    void details(string team)
    {
        int teamID = teamCode[team];
        cout << "They can win at most " << wins[teamID] << " + " << gamesLeft[teamID] << " = " << wins[teamID] + gamesLeft[teamID] << " games.\n";
        int totalWins = 0;
        double totalPlayed = 0.0;
        int count = 0;
        int size = eliminationResp[teamID].size();
        for (auto t : eliminationResp[teamID])
        {
            count++;
            if (count > 1 && count < size)
            {
                cout << ", ";
            }
            else if (count > 1 && count == size)
            {
                cout << " and ";
            }
            cout << t;
            totalWins += wins[teamCode[t]];
            for (auto r : eliminationResp[teamID])
            {
                totalPlayed += matchAgainst[teamCode[t]][teamCode[r]];
            }
        }
        totalPlayed /= 2;
        if (eliminationResp[teamID].size() > 1)
        {
            cout << " have";
        }
        else
        {
            cout << " has";
        }
        cout << " won a total of " << totalWins << " games.\n";
        cout << "They play each other " << totalPlayed << " times.\n";
        cout << "So on average, each of the teams wins " << totalWins + totalPlayed << "/" << size << " = " << (totalWins + totalPlayed) / size << " games.\n";
        cout << "\n";
    }
};