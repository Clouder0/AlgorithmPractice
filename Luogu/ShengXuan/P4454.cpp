#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
#define ll long long
ll g,P,n,A,B;
struct BetterListHashTable
{
    static const int mod = 100103;
    static const int maxn = 1e6 + 100;
    struct node
    {
        int next, key, val;
    } A[maxn + 10];
    int head[mod + 100], tot;
    void clear() { memset(head, 0, sizeof(head)), tot = 0; }
    int hash(int x)
    {
        int res = x % mod;
        if (res < 0) res += mod;
        return res;
    }
    int& operator[](int key)
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
        for (int p = head[pos]; p; p = A[p].next)
            if (A[p].key == key) return &A[p].val;
        return NULL;
    }
} HT;
ll fastpow(ll x,ll k)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = (res * x) % P;
        x = (x * x) % P;
        k >>= 1;
    }
    return res;
}
int main()
{
    read(g), read(P);
    ll sqrtp = std::ceil(std::sqrt(P));
    ll sq = fastpow(g, sqrtp);
    read(n);
    while (n--)
    {
        HT.clear();
        read(A), read(B);
        ll tmp = A, ansa, ansb;
        for (int i = 0; i <= sqrtp; ++i) HT[tmp] = i, tmp = (tmp * g) % P;
        tmp = sq;
        for (int i = 1; i <= sqrtp; ++i)
        {
            int* ans = HT.find(tmp);
            if(ans != NULL) { ansa = i * sqrtp - *ans; break; }
            tmp = (tmp * sq) % P;
        }
        HT.clear();
        tmp = B;
        for (int i = 0; i <= sqrtp; ++i) HT[tmp] = i, tmp = (tmp * g) % P;
        tmp = sq;
        for (int i = 1; i <= sqrtp; ++i)
        {
            int *ans = HT.find(tmp);
            if (ans != NULL) { ansb = i * sqrtp - *ans; break; }
            tmp = (tmp * sq) % P;
        }
        printf("%lld\n", fastpow(g, (ansa * ansb) % (P - 1)));
    }
    return 0;
}