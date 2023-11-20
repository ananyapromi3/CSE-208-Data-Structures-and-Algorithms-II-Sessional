#include <iostream>
#include "functions.h"
#include <vector>
#include <list>
#define loadFactor 0.4
#define rehashing 0
using namespace std;

class SeperateChaining
{
    int tableSize;
    int minSize;
    int hashMethod;
    int count;
    list<pair<string, int> > *hashing;

    int myHash(string str)
    {
        if (hashMethod == 1)
        {
            return abs(hash1(str) + tableSize) % tableSize;
        }
        else
        {
            return abs(hash2(str) + tableSize) % tableSize;
        }
    }

public:
    SeperateChaining(int minSize, int hashMethod)
    {
        this->minSize = minSize;
        tableSize = getNextPrime(minSize);
        hashing = new list<pair<string, int> >[tableSize];
        this->hashMethod = hashMethod;
        this->count = 0;
    }

    int getTableSize() { return this->tableSize; }

    void rehash()
    {
        list<pair<string, int> > *temp;
        temp = new list<pair<string, int> >[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            for (auto el : this->hashing[i])
            {
                temp[i].push_back(el);
            }
            this->hashing[i].clear();
        }
        delete[] this->hashing;
        int tempSize = tableSize;
        tableSize = getNextPrime(2 * this->tableSize);
        this->hashing = new list<pair<string, int> >[tableSize];
        for (int i = 0; i < tempSize; i++)
        {
            for (auto hashObj : temp[i])
            {
                int hashVal = myHash(hashObj.first);
                hashing[hashVal].push_back(hashObj);
            }
        }
    }

    int insertData(pair<string, int> hashObj)
    {
        int collision = 0;
        if (findData(hashObj))
        {
            return collision;
        }
        int hashVal = myHash(hashObj.first);
        // int collision = hashing[hashVal].size();
        if (!hashing[hashVal].empty())
        {
            collision++;
        }
        hashing[hashVal].push_back(hashObj);
        count++;
        if (rehashing)
        {
            if ((count * 1.0) / tableSize >= loadFactor)
            {
                rehash();
            }
        }
        return collision;
    }

    void deleteData(pair<string, int> hashObj)
    {
        int hashVal = myHash(hashObj.first);
        for (auto it = hashing[hashVal].begin(); it != hashing[hashVal].end(); it++)
        {
            if ((*it) == hashObj)
            {
                hashing[hashVal].erase(it);
                count--;
                break;
            }
        }
    }

    bool findData(pair<string, int> hashObj)
    {
        int hashVal = myHash(hashObj.first);
        for (auto el : hashing[hashVal])
        {
            if (el.first == hashObj.first)
            {
                return true;
            }
        }
        return false;
    }

    int countProbing(string str)
    {
        int hashVal = myHash(str);
        int i = 1;
        for (auto el : hashing[hashVal])
        {
            if (el.first == str)
            {
                return i;
            }
            i++;
        }
        return i;
    }

    void displayData()
    {
        for (int i = 0; i < tableSize; i++)
        {
            cout << i;
            for (auto el : hashing[i])
            {
                cout << " --> (" << el.first << ", " << el.second << ")";
            }
            cout << "\n";
        }
    }
};

class DoubleHashing
{
    int tableSize;
    int minSize;
    int hashMethod;
    int count;
    pair<string, int> *hashing;

    int doubleHash(string str, int i)
    {
        if (hashMethod == 1)
        {
            return abs(hash1(str) + i * auxHash(str)) % tableSize;
        }
        else
        {
            return abs(hash2(str) + i * auxHash(str)) % tableSize;
        }
    }

public:
    DoubleHashing(int minSize, int hashMethod)
    {
        this->minSize = minSize;
        tableSize = getNextPrime(minSize);
        hashing = new pair<string, int>[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            hashing[i] = make_pair("", -1); // -1 means empty
        }
        this->hashMethod = hashMethod;
        this->count = 0;
    }

    int getTableSize() { return this->tableSize; }

    void rehash()
    {
        pair<string, int> *temp;
        temp = new pair<string, int>[this->tableSize];
        int tempSize = this->tableSize;
        for (int i = 0; i < tempSize; i++)
        {
            temp[i] = make_pair(hashing[i].first, hashing[i].second);
        }
        this->tableSize = getNextPrime(2 * this->tableSize);
        delete[] this->hashing;
        this->hashing = new pair<string, int>[this->tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            this->hashing[i] = make_pair("", -1);
        }
        for (int i = 0; i < tempSize; i++)
        {
            for (int j = 0; j < this->tableSize; j++)
            {
                int hashVal = doubleHash(temp[i].first, j);
                if (this->hashing[hashVal].second < 0)
                {
                    this->hashing[hashVal] = make_pair(temp[i].first, temp[i].second);
                    break;
                }
            }
        }
    }

    int insertData(pair<string, int> hashObj)
    {
        int collision = 0;
        if (findData(hashObj))
        {
            return collision;
        }
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(hashObj.first, i);
            if (hashing[hashVal].second < 0)
            {
                hashing[hashVal] = hashObj;
                count++;
                collision = i;
                break;
            }
        }
        if (rehashing)
        {
            if ((count * 1.0) / tableSize >= loadFactor)
            {
                rehash();
            }
        }
        return collision;
    }

    void deleteData(pair<string, int> hashObj)
    {
        if (!findData(hashObj))
        {
            return;
        }
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(hashObj.first, i);
            if (hashing[hashVal] == hashObj)
            {
                hashing[hashVal] = make_pair("", -2); // -2 means deleted
                count--;
                break;
            }
        }
    }

    bool findData(pair<string, int> hashObj)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(hashObj.first, i);
            if (hashing[hashVal].second == -1)
            {
                return false;
            }
            else if (hashing[hashVal] == hashObj)
            {
                return true;
            }
        }
        return false;
    }

    int countProbing(string str)
    {
        int i = 0;
        for (i = 0; i < tableSize; i++)
        {
            int hashVal = doubleHash(str, i);
            if (hashing[hashVal].second == -1 || hashing[hashVal].first == str)
            {
                return i + 1;
            }
        }
        return i + 1;
    }

    void displayData()
    {
        for (int i = 0; i < tableSize; i++)
        {
            cout << i << ": ";
            if (hashing[i].second >= 0)
            {
                cout << "(" << hashing[i].first << ", " << hashing[i].second << ")";
            }
            cout << "\n";
        }
    }
};

class CustomProbing
{
    int tableSize;
    int minSize;
    int hashMethod;
    int C1;
    int C2;
    int count;
    pair<string, int> *hashing;

    int customHash(string str, int i)
    {
        if (hashMethod == 1)
        {
            return abs(hash1(str) + C1 * i * auxHash(str) + C2 * i * i) % tableSize;
        }
        else
        {
            return abs(hash2(str) + C1 * i * auxHash(str) + C2 * i * i) % tableSize;
        }
    }

public:
    CustomProbing(int minSize, int hashMethod, int c1, int c2)
    {
        this->minSize = minSize;
        tableSize = getNextPrime(minSize);
        hashing = new pair<string, int>[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            hashing[i] = make_pair("", -1);
        }
        this->hashMethod = hashMethod;
        this->C1 = c1;
        this->C2 = c2;
        this->count = 0;
    }

    int getTableSize() { return this->tableSize; }

    void rehash()
    {
        pair<string, int> *temp;
        temp = new pair<string, int>[this->tableSize];
        int tempSize = tableSize;
        for (int i = 0; i < tempSize; i++)
        {
            temp[i] = make_pair(this->hashing[i].first, this->hashing[i].second);
        }
        this->tableSize = getNextPrime(2 * this->tableSize);
        delete[] hashing;
        hashing = new pair<string, int>[this->tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            hashing[i] = make_pair("", -1);
        }
        for (int i = 0; i < tempSize; i++)
        {
            for (int j = 0; j < tableSize; j++)
            {
                int hashVal = customHash(temp[i].first, j);
                if (hashing[hashVal].second < 0)
                {
                    hashing[hashVal] = make_pair(temp[i].first, temp[i].second);
                    break;
                }
            }
        }
    }

    int insertData(pair<string, int> hashObj)
    {
        int collision = 0;
        if (findData(hashObj))
        {
            return collision;
        }
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = customHash(hashObj.first, i);
            if (this->hashing[hashVal].second < 0)
            {
                this->hashing[hashVal] = hashObj;
                count++;
                collision = i;
                break;
            }
        }
        if (rehashing)
        {
            if ((count * 1.0) / tableSize >= loadFactor)
            {
                rehash();
            }
        }
        return collision;
    }

    void deleteData(pair<string, int> hashObj)
    {
        if (!findData(hashObj))
        {
            return;
        }
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = customHash(hashObj.first, i);
            if (hashing[hashVal] == hashObj)
            {
                hashing[hashVal] = make_pair("", -2); // -2 means deleted
                count--;
                break;
            }
        }
    }

    bool findData(pair<string, int> hashObj)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int hashVal = customHash(hashObj.first, i);
            if (hashing[hashVal].second == -1)
            {
                return false;
            }
            else if (hashing[hashVal] == hashObj)
            {
                return true;
            }
        }
        return false;
    }

    int countProbing(string str)
    {
        int i = 0;
        for (i = 0; i < tableSize; i++)
        {
            int hashVal = customHash(str, i);
            if (hashing[hashVal].second == -1 || hashing[hashVal].first == str)
            {
                return i + 1;
            }
        }
        return i + 1;
    }

    void displayData()
    {
        for (int i = 0; i < tableSize; i++)
        {
            cout << i << ": ";
            if (hashing[i].second >= 0)
            {
                cout << "(" << hashing[i].first << ", " << hashing[i].second << ")";
            }
            cout << "\n";
        }
    }
};