#include <iostream>
#include "functions.h"
#include <vector>
#include <list>
using namespace std;

class DoubleHashing
{
    int tableSize;
    pair<string, int> *hashing;

    int doubleHash(string str, int i)
    {
        return abs(hashFunc(str) + i * auxHash(str)) % tableSize;
    }

public:
    DoubleHashing(int minSize)
    {
        tableSize = getNextPrime(minSize);
        hashing = new pair<string, int>[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            hashing[i] = make_pair("", -1); // -1 means empty
        }
    }

    int getTableSize() { return this->tableSize; }

    void insertData(string str, int x)
    {
        if (findData(str))
        {
            return;
        }
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(str, i);
            if (hashing[hashVal].second < 0)
            {
                hashing[hashVal] = make_pair(str, x);
                break;
            }
        }
    }

    int findData(string str)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(str, i);
            if (hashing[hashVal].second == -1)
            {
                return 0;
            }
            else if (hashing[hashVal].first == str)
            {
                return hashing[hashVal].second;
            }
        }
        return 0;
    }

    void displayData()
    {
        cout << "[";
        for (int i = 0; i < tableSize; i++)
        {
            if (hashing[i].second >= 0)
            {
                cout << "(" << hashing[i].first << ", " << hashing[i].second << ")";
            }
        }
        cout << "]";
    }
};

class DoubleHashing2
{
    int tableSize;
    pair<string, DoubleHashing *> *hashing;

    int doubleHash(string str, int i)
    {
        return abs(hashFunc(str) + i * auxHash(str)) % tableSize;
    }

public:
    DoubleHashing2(int minSize)
    {
        tableSize = getNextPrime(minSize);
        hashing = new pair<string, DoubleHashing *>[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            DoubleHashing *dhtemp;
            dhtemp = new DoubleHashing(tableSize);
            hashing[i] = make_pair("", dhtemp);
        }
    }

    int getTableSize() { return this->tableSize; }

    void insertData(string str1, string str2, int x)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(str1, i);
            if (hashing[hashVal].first == "")
            {
                hashing[hashVal].first = str1;
            }
            if (hashing[hashVal].first == str1)
            {
                hashing[hashVal].second->insertData(str2, x);
                break;
            }
        }
    }

    DoubleHashing *findData(string str)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(str, i);
            if (hashing[hashVal].first == str)
            {
                return hashing[hashVal].second;
            }
        }
        return NULL;
    }

    int findData(string str1, string str2)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(str1, i);
            if (hashing[hashVal].first == str1)
            {
                return hashing[hashVal].second->findData(str2);
            }
        }
        return 0;
    }
};
