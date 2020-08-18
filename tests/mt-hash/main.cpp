#include "hashMap.hpp"
#include <iostream>
using namespace std;

struct Equal {
    bool operator()(const int& a_left, const int& a_right) const {
        return a_left == a_right;
    }
};

struct HashFunc {
    size_t operator()(const int& a_key) const {
        return a_key;
    }
};

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs) {
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m\n";
}

struct Combine {
    int operator()(const int a_left, const int& a_right) const {
        return (a_left + a_right);
    }
};

typedef experis::HashMapMT<int, int, HashFunc, Equal> HashMapMT;

static void TestCreateHashMapMT()
{
    static int testNum = 0;
    HashMapMT hash(2);
    PrintResult("create hashMap", (0 == hash.Find(2)), testNum, ": \t");
}

static void TestUpsert(HashMapMT& a_hash, int a_key, int a_value, int a_valueAfter)
{
    static int testNum = 0;
    try {
        a_hash.Upsert<Combine>(a_key, a_value);
        PrintResult("upsert", (a_valueAfter == *(a_hash.Find(a_key))), testNum, ": \t\t");
    }catch(const exception& exc) {
        cout << exc.what() << '\n';
        PrintResult("upsert", false, testNum, ": \t\t");
    }
}

static void TestFind(HashMapMT& a_hash, int a_key, int a_wantedValue)
{
    static int testNum = 0;
    try {
        PrintResult("find", (a_wantedValue == *(a_hash.Find(a_key))), testNum, ": \t\t");
    }catch(const exception& exc) {
        cout << exc.what() << '\n';
        PrintResult("find", false, testNum, ": \t\t");
    }
}

int main() 
{
    TestCreateHashMapMT();

    HashMapMT hash(2);
    TestUpsert(hash, 2, 5, 5);
    TestUpsert(hash, 2, 3, 8);

    TestFind(hash, 2, 8);

    return 0;
}