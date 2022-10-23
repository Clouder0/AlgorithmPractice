#include <cstdio>
#include <list>
#include <cstring>
const int maxn = 1e6 + 100;
int n,a[maxn];
struct Bucket
{
    static const int maxval = 1e7;
    int val[maxval];
    Bucket() { memset(val, 0, sizeof(val)); }
    int hash(int x) { return x; }
    int find(int key) { return val[hash(key)]; }
    void set(int key, int value) { val[hash(key)] = value; }
    void add(int key, int value) { val[hash(key)] += value; }
};
struct SingleModHashTable
{
    static const int mod = 10000103;
    int val[mod + 100];
    SingleModHashTable() { memset(val, 0, sizeof(val));}
    int hash(int x) { return ((x % mod) + mod) % mod; }
    int find(int key) { return val[hash(key)]; }
    void set(int key, int value) { val[hash(key)] = value; }
    void add(int key, int value) { val[hash(key)] += value; }
};
struct LinearAttemptHashTable
{
    static const int mod = 10000103;
    int keytable[mod + 100], valtable[mod + 100];
    LinearAttemptHashTable() { memset(keytable, 0, sizeof(keytable)), memset(valtable, 0, sizeof(valtable)); }
    int hash(int x) { return ((x % mod) + mod) % mod; }
    int & operator[](int key)
    {
        int p = hash(key);
        while (keytable[p] && keytable[p] != key) p = (p + 1) % mod;
        keytable[p] = key;
        return valtable[p];
    }
    int* find(int key)
    {
        int p = hash(key);
        while (keytable[p] && keytable[p] != key) p = (p + 1) % mod;
        if(keytable[p] == key) return &valtable[p];
        return NULL;
    }
};
struct AttemptHashTable
{
    static const int mod = 10000103;
    int keytable[mod + 100], valtable[mod + 100];
    AttemptHashTable() { memset(keytable, 0, sizeof(keytable)), memset(valtable, 0, sizeof(valtable)); }
    int hash(int x) 
    { 
        int res = (x + 195781) % mod;
        if(res < 0) res += mod;
        return res;
    }
    int & operator[](int key)
    {
        int p = hash(key);
        while (keytable[p] && keytable[p] != key) p = hash(p);
        keytable[p] = key;
        return valtable[p];
    }
    int* find(int key)
    {
        int p = hash(key);
        while (keytable[p] && keytable[p] != key) p = hash(p);
        if(keytable[p] == key) return &valtable[p];
        return NULL;
    }
};
struct ListHashTable
{
    static const int mod = 100103;
    std::list<std::pair<int, int> > valtable[mod + 100];
    int hash(int x)
    {
        int res = x % mod;
        if (res < 0) res += mod;
        return res;
    }
    int & operator[](int key)
    {
        int p = hash(key);
        for (std::list<std::pair<int, int> >::iterator it = valtable[p].begin(); it != valtable[p].end(); ++it)
            if (it->first == key) return it->second;
        valtable[p].push_front(std::make_pair(key, 0));
        return valtable[p].begin()->second;
    }
    int* find(int key)
    {
        int p = hash(key);
        for (std::list<std::pair<int, int> >::iterator it = valtable[p].begin(); it != valtable[p].end(); ++it)
            if (it->first == key) return &it->second;
        return NULL;
    }
};
struct BetterListHashTable
{
    static const int mod = 1000103;
    static const int maxn = 1e6 + 100;
    struct node
    {
        int next, key, val;
    } A[maxn + 10];
    int head[mod + 100],tot;
    int hash(int x)
    {
        int res = x % mod;
        if (res < 0) res += mod;
        return res;
    }
    int & operator [](int key)
    {
        int pos = hash(key);
        for (int p = head[pos]; p; p = A[p].next)
            if (A[p].key == key) return A[p].val;
        A[++tot].next = head[pos], A[tot].key = key, A[tot].val = 0, head[pos] = tot;
        return A[tot].val;
    }
    int* find(int key)
    {
        int pos = hash(key);
        for(int p = head[pos];p;p=A[p].next)
            if(A[p].key == key) return &A[p].val;
        return NULL;
    }
};
int main()
{

    return 0;
}