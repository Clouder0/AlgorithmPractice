#include <algorithm>
#include <cstdio>
#include <ctype.h>

const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
int n, m, anum, bnum;
long long d;
int a[maxn], b[maxn];
long long asum[maxn], bsum[maxn];
bool cmp(const int& a, const int& b) { return a > b; }
int main()
{
    read(n), read(d), read(m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        if (x <= m) a[++anum] = x;
        else b[++bnum] = x;
    }
    std::sort(a + 1, a + 1 + anum, cmp);
    std::sort(b + 1, b + 1 + bnum, cmp);
    for (int i = 1; i <= n; ++i) asum[i] = asum[i - 1] + a[i];
    for (int i = 1; i <= bnum; ++i) bsum[i] = bsum[i - 1] + b[i];
    long long ans = 0;
    if (bnum == 0) ans = asum[anum];
    for (int i = 1; i <= bnum; ++i)
    {
        long long need = (i - 1) * (d + 1) + 1;
        if (bnum > need + d) continue;
        if (need > n) break;
        ans = std::max(ans, bsum[i] + asum[n - need]);
    }
    printf("%lld\n", ans);
    return 0;
}