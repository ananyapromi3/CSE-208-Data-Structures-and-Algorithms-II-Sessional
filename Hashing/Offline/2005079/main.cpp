#include <iostream>
#include <iomanip>
#include "Hashing.h"
#include <vector>
#include <string>
#include <time.h>
#include <set>
using namespace std;
#define COUNT 10000
// #define N 5000
// #define N 10000
// #define N 20000
#define n 1000
int main()
{
    // srand(time(0));
    srand(0);
    set<string> words;
    while (words.size() <= COUNT)
    {
        string str = getRandomWords();
        words.insert(str);
    }
    vector<string> wordlist;
    for (auto s : words)
    {
        wordlist.push_back(s);
    }
    freopen("output.txt", "w", stdout);
    int arr[3] = {5000, 10000, 20000};
    for (int p = 0; p < 3; p++)
    {
        int N = arr[p];
        cout << "For N' = " << N << "\n";
        SeperateChaining *sc1;
        int sc1_col = 0;
        int sc1_prob = 0;
        SeperateChaining *sc2;
        int sc2_col = 0;
        int sc2_prob = 0;
        DoubleHashing *dh1;
        int dh1_col = 0;
        int dh1_prob = 0;
        DoubleHashing *dh2;
        int dh2_col = 0;
        int dh2_prob = 0;
        CustomProbing *cp1;
        int cp1_col = 0;
        int cp1_prob = 0;
        CustomProbing *cp2;
        int cp2_col = 0;
        int cp2_prob = 0;
        sc1 = new SeperateChaining(N, 1);
        sc2 = new SeperateChaining(N, 2);
        dh1 = new DoubleHashing(N, 1);
        dh2 = new DoubleHashing(N, 2);
        cp1 = new CustomProbing(N, 1, 913, 719);
        cp2 = new CustomProbing(N, 2, 913, 719);
        // int count = COUNT;
        int count = min(sc1->getTableSize(), COUNT);
        set<string> search;
        while (search.size() <= n)
        {
            int i = rand() % count;
            search.insert(wordlist[i]);
        }
        for (int i = 1; i <= count; i++)
        {
            sc1_col += sc1->insertData(make_pair(wordlist[i], i));
            sc2_col += sc2->insertData(make_pair(wordlist[i], i));
            dh1_col += dh1->insertData(make_pair(wordlist[i], i));
            dh2_col += dh2->insertData(make_pair(wordlist[i], i));
            cp1_col += cp1->insertData(make_pair(wordlist[i], i));
            cp2_col += cp2->insertData(make_pair(wordlist[i], i));
        }
        for (auto word : search)
        {
            sc1_prob += sc1->countProbing(word);
            sc2_prob += sc2->countProbing(word);
            dh1_prob += dh1->countProbing(word);
            dh2_prob += dh2->countProbing(word);
            cp1_prob += cp1->countProbing(word);
            cp2_prob += cp2->countProbing(word);
        }
        // sc1->displayData();
        // sc2->displayData();
        // dh1->displayData();
        // dh2->displayData();
        // cp1->displayData();
        // cp2->displayData();
        cout << left << setfill('_') << setw(140) << "" << setfill(' ');
        cout << "\n";
        cout << left << setw(20) << "Hash Table Size";
        cout << left << setw(32) << "Collision Resolution Method";
        cout << left << setw(20) << "";
        cout << left << setw(24) << "Hash1";
        cout << left << setw(20) << "";
        cout << left << setw(24) << "Hash2";
        cout << "\n";
        cout << right << setfill(' ') << setw(52) << "" << setfill('_') << setw(88) << "" << setfill(' ');
        cout << "\n";
        cout << left << setw(52) << "";
        cout << left << setw(24) << "# of Collisions";
        cout << left << setw(20) << "Average Probes";
        cout << left << setw(24) << "# of Collisions";
        cout << left << setw(20) << "Average Probes";
        cout << "\n";
        cout << left << setfill('_') << setw(140) << "" << setfill(' ');
        cout << "\n";
        cout << left << setw(20) << sc1->getTableSize();
        cout << left << setw(32) << "Chaining";
        cout << left << setw(24) << sc1_col;
        cout << left << setw(20) << (sc1_prob * 1.0) / n;
        cout << left << setw(24) << sc2_col;
        cout << left << setw(20) << (sc2_prob * 1.0) / n;
        cout << "\n";
        cout << left << setw(20) << dh1->getTableSize();
        cout << left << setw(32) << "Double Hashing";
        cout << left << setw(24) << dh1_col;
        cout << left << setw(20) << (dh1_prob * 1.0) / n;
        cout << left << setw(24) << dh2_col;
        cout << left << setw(20) << (dh2_prob * 1.0) / n;
        cout << "\n";
        cout << left << setw(20) << cp1->getTableSize();
        cout << left << setw(32) << "Custom Probing";
        cout << left << setw(24) << cp1_col;
        cout << left << setw(20) << (cp1_prob * 1.0) / n;
        cout << left << setw(24) << cp2_col;
        cout << left << setw(20) << (cp2_prob * 1.0) / n;
        cout << "\n";
        cout << left << setfill('_') << setw(140) << "" << setfill(' ');
        cout << "\n\n\n\n";
    }
    
    // vector<int> v;
    // set<int> s;
    // for (auto x : wordlist)
    // {
    //     int val = auxHash(x);
    //     s.insert(val);
    //     v.push_back(val);
    // }
    // cout << s.size() << " " << v.size() << "\n";
    // cout << (1.0 * s.size()) / (1.0 * v.size());

    return 0;
}
