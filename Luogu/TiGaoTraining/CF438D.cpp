#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using std::max;
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
const int maxn = 1e5 + 100;
int n, m, a[maxn],maxx[maxn << 2];
long long sum[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p)
{
    maxx[p] = max(maxx[ls], maxx[rs]);
    sum[p] = sum[ls] + sum[rs];
}
void build(int l,int r,int p)
{
    if (l == r) return (void)(sum[p] = maxx[p] = a[l]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void modify(int l,int r,int p,int pos,int k)
{
    if(l == r) return (void)(sum[p] = maxx[p] = k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,ls,pos,k);
    else modify(mid + 1,r,rs,pos,k);
    pushup(p);
}
long long ask(int l,int r,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1;
    long long res = 0;
    if(ll <= mid) res = ask(l,mid,ls,ll,rr);
    if(rr > mid) res += ask(mid + 1,r,rs,ll,rr);
    return res;
}
void mod(int l,int r,int p,int ll,int rr,int k)
{
    if (l == r) return (void)(sum[p] %= k, maxx[p] %= k);
    if (l >= ll && r <= rr && maxx[p] < k) return;
    int mid = l + r >> 1;
    if (ll <= mid) mod(l, mid, ls, ll, rr, k);
    if (rr > mid) mod(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1, n, 1);
    for (int i = 1,t,l,r,x,k; i <= m; ++i) 
    {
        read(t);
        if (t == 1) read(l), read(r), printf("%lld\n", ask(1, n, 1, l, r));
        else if (t == 2) read(l), read(r), read(x), mod(1, n, 1, l, r, x);
        else read(k), read(x), modify(1, n, 1, k, x);
    }
    return 0;
}