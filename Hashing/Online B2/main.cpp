#include <iostream>
#include <iomanip>
#include "Hashing.h"
#include <vector>
#include <string>
#include <time.h>
#include <set>
using namespace std;
int main()
{
    int N = 5;
    DoubleHashing2 *table;
    table = new DoubleHashing2(N);
    table->insertData("bd", "dhaka", 500);
    table->insertData("bd", "ctg", 300);
    table->insertData("uk", "london", 800);
    cout << table->findData("bd", "dhaka") << "\n";
    cout << table->findData("bd", "syl") << "\n";
    if (table->findData("bd"))
    {
        table->findData("bd")->displayData();
    }
    cout << "\n";
    if (table->findData("china"))
    {
        table->findData("china")->displayData();
    }
    cout << "\n";
    return 0;
}
