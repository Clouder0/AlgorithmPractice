#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc() { static char buf[bufSize], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++; }
template<typename T> 
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 5e3 + 100;
#define int long long
int n,k,x,a[maxn];
int cost[2][maxn],f[2][maxn],q[maxn],qt,qh;
signed main()
{
    read(n), read(k), read(x);
    for (int i = 1; i <= n; ++i) read(a[i]);
    int now = 0, last = 1;
    memset(f[last], ~0x3f, sizeof(f[last]));
    f[last][0] = 0;
    for (int j = 1; j <= x; ++j)  //choose j
    {
        qh = qt = 1, q[1] = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (qt >= qh && i - q[qh] > k) ++qh;
            f[now][i] = f[last][q[qh]] + a[i];
            while (qt >= qh && f[last][q[qt]] <= f[last][i]) --qt;
            q[++qt] = i;
        }
        now ^= 1, last ^= 1;
    }
    int ans = -(1ll << 60);
    for (int i = n - k + 1; i <= n; ++i) ans = max(ans, f[last][i]);
    if (ans >= 0) printf("%lld\n", ans);
    else puts("-1");
    return 0;
}