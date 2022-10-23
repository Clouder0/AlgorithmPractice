#include <cstdio>
#include <algorithm>
#include <cctype>
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
const int maxn = 3e5 + 100;
const int maxx = 3e7 + 100;
bool tag[maxx];
int n, L[maxx], R[maxx], val[maxx], pri[maxx], sz[maxx], tot;
long long sum[maxx];
int root[maxn];
inline int newnode(int x = 0) { return val[++tot] = x, sum[tot] = x, pri[tot] = rand(), sz[tot] = 1, tot; }
inline int copy(int t)
{
    int x = ++tot;
    pri[x] = pri[t], L[x] = L[t], R[x] = R[t], val[x] = val[t], sz[x] = sz[t], sum[x] = sum[t], tag[x] = tag[t];
    return x;
}
inline void pushup(int p) { sz[p] = sz[L[p]] + sz[R[p]] + 1, sum[p] = sum[L[p]] + sum[R[p]] + val[p]; }
inline void pushdown(int p)
{
    if(!tag[p]) return;
    if (L[p]) L[p] = copy(L[p]), tag[L[p]] ^= 1;
    if (R[p]) R[p] = copy(R[p]), tag[R[p]] ^= 1;
    std::swap(L[p], R[p]), tag[p] = 0;
}
int merge(int x,int y)
{
    if(!x || !y) return x + y;
    if (pri[x] > pri[y]) return pushdown(x), R[x] = merge(R[x], y), pushup(x), x;
    return pushdown(y), L[y] = merge(x, L[y]), pushup(y), y;
}
void split(int p,int k,int& x,int& y)
{
    if (!p) return (void)(x = y = 0);
    pushdown(p);
    if (k <= sz[L[p]]) y = copy(p), split(L[y], k, x, L[y]), pushup(y);
    else x = copy(p), split(R[x], k - sz[L[p]] - 1, R[x], y), pushup(x);
}
int main()
{
    read(n);
    long long last = 0, p, x, l, r, opt, v;
    for (int i = 1, s, m, b; i <= n; ++i)
    {
        read(v),read(opt);
        if(opt == 1)
        {
            read(p), read(x), p ^= last, x ^= last;
            split(root[v], p, s, b), root[i] = merge(merge(s, newnode(x)), b);
        }
        else if(opt == 2)
        {
            read(p), p ^= last;
            split(root[v], p - 1, s, m), split(m, 1, m, b), root[i] = merge(s, b);
        }
        else if (opt == 3)
        {
            read(l), read(r), l ^= last, r ^= last;
            split(root[v], r, m, b), split(m, l - 1, s, m), tag[m] ^= 1;
            root[i] = merge(s, merge(m, b));
        }
        else if(opt == 4)
        {
            read(l), read(r), l ^= last, r ^= last;
            split(root[v], r, m, b), split(m, l - 1, s, m), printf("%lld\n", last = sum[m]);
            root[i] = merge(s, merge(m, b));
        }
    }
    return 0;
}