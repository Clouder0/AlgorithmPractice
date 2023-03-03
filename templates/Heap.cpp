#include <algorithm>
#include <cstdio>
const int maxn = 5e6 + 10;
// small top
template <typename T>
struct smallheap
{
    T a[maxn];
    int sz;
    void up(int x)
    {
        while (x > 1 && a[x] < a[x >> 1])
        {
            std::swap(a[x], a[x >> 1]);
            x >>= 1;
        }
    }
    void down(int x)
    {
        while ((x << 1) <= sz)
        {
            int to = x << 1;
            if (to + 1 <= sz && a[to + 1] < a[to]) ++to;  // if rs is smaller, swap to rs
            if (a[x] <= a[to]) break;                      // down violates the heap property
            std::swap(a[x], a[to]);
            x = to;
        }
    }
    void push(T x) { a[++sz] = x, up(sz); }
    void pop() { a[1] = a[sz--], down(1); }
    T top() { return a[1]; }
    void build(int n)
    {
        sz = n;
        for (int i = (n >> 1); i; --i) down(i);
    }
    void build(T* b, int n)
    {
        for (int i = 1; i <= n; ++i) a[i] = b[i];
        build(n);
    }
    bool empty() { return !sz; }
    void clear() { sz = 0; }
};

// large top
template <typename T>
struct largeheap
{
    T a[maxn];
    int sz;
    void up(int x)
    {
        while (x > 1 && a[x] > a[x >> 1])
        {
            std::swap(a[x], a[x >> 1]);
            x >>= 1;
        }
    }
    void down(int x)
    {
        while ((x << 1) <= sz)
        {
            int to = x << 1;
            if (to + 1 <= sz && a[to + 1] > a[to]) ++to;  // if rs is larger, swap to rs
            if (a[x] >= a[to]) break;                      // down violates the heap property
            std::swap(a[x], a[to]);
            x = to;
        }
    }
    void push(T x) { a[++sz] = x, up(sz); }
    void pop() { a[1] = a[sz--], down(1); }
    T top() { return a[1]; }
    void build(int n)
    {
        sz = n;
        for (int i = (n >> 1); i; --i) down(i);
    }
    void build(T* b, int n)
    {
        for (int i = 1; i <= n; ++i) a[i] = b[i];
        build(n);
    }
    bool empty() { return !sz; }
    void clear() { sz = 0; }
};

namespace kth
{
// the kth largest element in an array
smallheap<int> S;
largeheap<int> L;
void maintain(int k)
{
    while (S.sz > k)
    {
        L.push(S.top());
        S.pop();
    }
    while (S.sz < k)
    {
        S.push(L.top());
        L.pop();
    }
}
void push(int x, int k)
{
    S.push(x);
    maintain(k);
}
void del(int k)
{
    S.pop();
    maintain(k);
}
}  // namespace kth