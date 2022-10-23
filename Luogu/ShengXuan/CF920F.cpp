#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
const int maxn = 3e5 + 100, maxm = 1e6 + 100;
int n, m, a[maxn], d[maxm], g[maxm], primes[maxn], cnt;
bool notprime[maxm];
int maxx[maxn << 2];
long long sum[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p)
{
    sum[p] = sum[ls] + sum[rs];
    maxx[p] = max(maxx[ls], maxx[rs]);
}
void build(int l, int r, int p)
{
    if (l == r) return (void)(sum[p] = maxx[p] = a[l]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void modify(int l, int r, int p, int ll, int rr)
{
    if(maxx[p] <= 2) return;
    if (l == r) return (void)(maxx[p] = sum[p] = d[sum[p]]);
    int mid = l + r >> 1;
    if (ll <= mid) modify(l, mid, ls, ll, rr);
    if (rr > mid) modify(mid + 1, r, rs, ll, rr);
    pushup(p);
}
long long ask(int l, int r, int p, int ll, int rr)
{
    if (l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1;
    long long res = 0;
    if (ll <= mid) res = ask(l, mid, ls, ll, rr);
    if (rr > mid) res += ask(mid + 1, r, rs, ll, rr);
    return res;
}
signed main()
{
    read(n), read(m);
    int maxx = 0;
    for (int i = 1; i <= n; ++i) read(a[i]), maxx = max(maxx, a[i]);
    g[1] = 1, d[1] = 1;
    for (int i = 2; i <= maxx; ++i)
    {
        if (!notprime[i]) d[i] = 2, g[i] = 1, primes[++cnt] = i;
        for (int j = 1; j <= cnt && i * primes[j] <= maxx; ++j)
        {
            notprime[i * primes[j]] = 1;
            if ((i % primes[j]) == 0)
            {
                d[i * primes[j]] = d[i] / (g[i] + 1) * ((g[i * primes[j]] = (g[i] + 1)) + 1);
                break;
            }
            d[i * primes[j]] = d[i] * 2, g[i * primes[j]] = 1;
        }
    }
    build(1, n, 1);
    for (int i = 1, opt, l, r; i <= m; ++i)
    {
        read(opt), read(l), read(r);
        if (opt == 1) modify(1, n, 1, l, r);
        else printf("%lld\n", ask(1, n, 1, l, r));
    }
    return 0;
}