#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <climits>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int getNextPrime(int n)
{
    for (int i = n; i < 2 * n; i++)
    {
        if (isPrime(i))
        {
            return i;
        }
    }
    return 0;
}

string getRandomWords()
{
    // srand(time(0));
    int len = 5 + rand() % 6;
    string word = "";
    for (int i = 0; i < len; i++)
    {
        char letter = 'a' + rand() % 26;
        word = word + letter;
    }
    return word;
}

int auxHash(string str)
{
    int hashVal = 0;
    for (auto s : str)
    {
        hashVal += s;
    }
    return abs(hashVal);
}

// Jenkins hash function
int hash1(string str)
{
    int i = 0;
    int hashVal = 0;
    while (i != str.length())
    {
        hashVal += str[i++];
        hashVal += hashVal << 10;
        hashVal ^= hashVal >> 6;
    }
    hashVal += hashVal << 3;
    hashVal ^= hashVal >> 11;
    hashVal += hashVal << 15;
    return abs(hashVal % INT_MAX);
}

// Hornor's Method
int hash2(string str)
{
    int hashVal = 0;
    for (auto s : str)
    {
        hashVal = (((hashVal * 37) % INT_MAX) + s) % INT_MAX;
    }
    return abs(hashVal % INT_MAX);
}