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
    int operator()(int& a_left, const int& a_right) const {
        return (a_left += a_right);
    }
};

typedef experis::HashMapMT<int, int, HashFunc, Equal> HashMapMT;

static void TestCreateHashMapMT()
{
    static int testNum = 0;
    HashMapMT hash(2);
    int result = 0;
    PrintResult("create hashMap", (!hash.Find(2, result)), testNum, ": \t");
}

static void TestUpsert(HashMapMT& a_hash, int a_key, int a_value, int a_valueAfter)
{
    static int testNum = 0;
    try {
        a_hash.Upsert(a_key, a_value, Combine());
        int result = 0;
        PrintResult("upsert", ((a_hash.Find(a_key, result) && (a_valueAfter == result))), testNum, ": \t\t");

    }catch(const exception& exc) {
        cout << exc.what() << '\n';
        PrintResult("upsert", false, testNum, ": \t\t");
    }
}

static void TestFind(HashMapMT& a_hash, int a_key, int a_wantedValue)
{
    static int testNum = 0;
    try {
        int result = -1;
        PrintResult("find", ((a_hash.Find(a_key, result) && (a_wantedValue == result))), testNum, ": \t\t");

    }catch(const exception& exc) {
        cout << exc.what() << '\n';
        PrintResult("find", false, testNum, ": \t\t");
    }
}

static void TestRemove(HashMapMT& a_hash, int a_key, bool a_wantedResult)
{
    static int testNum = 0;
    try {
        int result = -1;
        PrintResult("remove", (a_wantedResult == a_hash.Remove(a_key, result)), testNum, ": \t\t");
    }catch(const exception& exc) {
        cout << exc.what() << '\n';
        PrintResult("remove", false, testNum, ": \t\t");
    }
}

static void TestSize(HashMapMT& a_hash, size_t a_wantedResult)
{
    static int testNum = 0;
    try {
        PrintResult("size", (a_wantedResult == a_hash.Size()), testNum, ": \t\t");
    }catch(const exception& exc) {
        cout << exc.what() << '\n';
        PrintResult("size", false, testNum, ": \t\t");
    }
}

static void* TestThreadsRemove(void* a_hash)
{
    try {
        for (size_t i = 0 ; i < 10 ; ++i) {
            int result = -1;
            cout << (static_cast<HashMapMT*>(a_hash)->Remove(i, result) ? "removed: " : "no such key to remove");
            if(-1 != result) {
                cout << result;
            }
            cout << '\n';
        }
    }catch(const exception& exc) {
        cout << exc.what() << '\n';
    }

    pthread_exit(NULL);
    return 0;
}

static void* TestThreadsUpsert(void* a_hash)
{
    Combine combine;
    for (size_t i = 0 ; i < 10 ; ++i) {
        static_cast<HashMapMT*>(a_hash)->Upsert(i, i, combine);
        int result = 0;
        static_cast<HashMapMT*>(a_hash)->Find(i, result);
        cout << "value upserted: " << result << '\n';
    }
    
    pthread_exit(NULL);
    return 0;
}

int main() 
{
    TestCreateHashMapMT();

    HashMapMT hash(10);
    TestUpsert(hash, 2, 5, 5);
    TestUpsert(hash, 2, 3, 8);

    TestFind(hash, 2, 8);
    TestRemove(hash, 1, false);
    TestRemove(hash, 2, true);
    TestSize(hash, 0);

    pthread_t threadsRemove[5], threadsUpsert[5];
    for (size_t i = 0 ; i < 5 ; ++i) {
        if(0 < pthread_create(&threadsUpsert[i], NULL, TestThreadsUpsert, (void*)&hash)) {
            cout << "thread create failed!!" << '\n';
            return 1;
        }
        if(0 > pthread_create(&threadsRemove[i], NULL, TestThreadsRemove, (void*)&hash)) {
            cout << "thread create failed!!" << '\n';
            return 1;
        }
    }
    for (size_t i = 0 ; i < 5 ; ++i) {
        if(0 > pthread_join(threadsUpsert[i], NULL)) {
            cout << "thread join failed!!" << '\n';
            return 1;
        }
        if(0 > pthread_join(threadsRemove[i], NULL)) {
            cout << "thread join failed!!" << '\n';
            return 1;
        }
    }

    return 0;
}